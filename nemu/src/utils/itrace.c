#include <common.h>
#include <elf.h>
#define MAX_IRINGBUF 30
#define MAX_SYMTAB_FTRACE 300

typedef struct{
    word_t pc;
    uint32_t inst;
} ItraceNode;

ItraceNode iringbuf[MAX_IRINGBUF];
int pos_cur = 0;
bool full = false;

void trace_inst(word_t pc, uint32_t inst) {
    iringbuf[pos_cur].pc = pc;
    iringbuf[pos_cur].inst = inst;

    pos_cur = (pos_cur + 1) % MAX_IRINGBUF;
    full = full || (pos_cur == MAX_IRINGBUF - 1);
}

void display_inst() {
    if(!full && !pos_cur) { return; }
    int end = pos_cur - 1;
    int i = full ? pos_cur : 0;

    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    char buf[128]; // 128 should be enough!
    char *p;

    do {
        p = buf;
        p += sprintf(buf, "%s" FMT_WORD ": %08x ", (i+1)%MAX_IRINGBUF==end?" --> ":"     ", iringbuf[i].pc, iringbuf[i].inst);
        disassemble(p, buf+sizeof(buf)-p, iringbuf[i].pc, (uint8_t *)&iringbuf[i].inst, 4);
        if (i == end) printf(ANSI_FG_RED);
        puts(buf);

        // printf("PC: 0x%lx\t INST: 0x%08x\n", iringbuf[i].pc, iringbuf[i].inst);
        i = (i + 1) % MAX_IRINGBUF;
    } while( i != end + 1);
    
}

void display_mread(paddr_t addr, int len, word_t data){
    printf("Read From Memory - Address: 0x%x\t length: %d\t Data: 0x%lx\n", addr, len, data);
}

void display_mwrite(paddr_t addr, int len, word_t data){
    printf("Write to Memory - Address: 0x%x\t length: %d\t Data: 0x%lx\n", addr, len, data);
}

typedef struct{
    char name[50];
    paddr_t value;
    int size;
    bool type;
}SymbolTable;

SymbolTable symtab_ftrace[MAX_SYMTAB_FTRACE];
int symtab_length = 0;

void parse_elf(char* elf_file){
    FILE *file = fopen(elf_file, "rb");
    if(file == NULL){
        printf("Error opening file");
    }
    
    Elf64_Ehdr elfHeader;
    size_t __attribute__((unused)) bytes_read = fread(&elfHeader, sizeof(Elf64_Ehdr), 1, file);

    if (elfHeader.e_ident[EI_MAG0] != ELFMAG0 ||
        elfHeader.e_ident[EI_MAG1] != ELFMAG1 ||
        elfHeader.e_ident[EI_MAG2] != ELFMAG2 ||
        elfHeader.e_ident[EI_MAG3] != ELFMAG3) {
        printf("Not an ELF file.\n");
        fclose(file);
        return;
    }

    // Get the section name string table header
    Elf64_Shdr shstrtabHeader;
    fseek(file, elfHeader.e_shoff + elfHeader.e_shentsize * elfHeader.e_shstrndx, SEEK_SET);
    bytes_read = fread(&shstrtabHeader, sizeof(Elf64_Shdr), 1, file);

    // Read the section name string table
    char *shstrtab = malloc(shstrtabHeader.sh_size);
    fseek(file, shstrtabHeader.sh_offset, SEEK_SET);
    bytes_read = fread(shstrtab, shstrtabHeader.sh_size, 1, file);

    // Find the symbol table section header
    Elf64_Shdr symtabHeader, strtabHeader;
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        fseek(file, elfHeader.e_shoff + elfHeader.e_shentsize * i, SEEK_SET);
        Elf64_Shdr sectionHeader;
        bytes_read = fread(&sectionHeader, sizeof(Elf64_Shdr), 1, file);

        const char *sectionName = shstrtab + sectionHeader.sh_name;
        if (sectionHeader.sh_type == SHT_SYMTAB) {
            symtabHeader = sectionHeader;
        } else if (sectionHeader.sh_type == SHT_STRTAB && strcmp(sectionName, ".strtab") == 0) {
            strtabHeader = sectionHeader;
        }
    }

    if (symtabHeader.sh_size == 0 || strtabHeader.sh_size == 0) {
        printf("Symbol table or string table not found.\n");
        fclose(file);
        free(shstrtab);
        return;
    }

    // Read the symbol table
    fseek(file, symtabHeader.sh_offset, SEEK_SET);
    Elf64_Sym *symtab = malloc(symtabHeader.sh_size);
    bytes_read = fread(symtab, symtabHeader.sh_size, 1, file);

    // Read the string table
    char *strtab = malloc(strtabHeader.sh_size);
    fseek(file, strtabHeader.sh_offset, SEEK_SET);
    bytes_read = fread(strtab, strtabHeader.sh_size, 1, file);

    // Save symbol information
    for (int i = 0; i < symtabHeader.sh_size / sizeof(Elf64_Sym); i++) {
        strcpy(symtab_ftrace[i].name, strtab + symtab[i].st_name);    // Name
        symtab_ftrace[i].value = symtab[i].st_value;    // Value
        symtab_ftrace[i].size = symtab[i].st_size;  // Size
        symtab_ftrace[i].type = ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC ? 1 : 0;   // Type
    }
    symtab_length = symtabHeader.sh_size / sizeof(Elf64_Sym);

    fclose(file);
    free(shstrtab);
    free(symtab);
    free(strtab);
}

void trace_func_call(paddr_t pc, paddr_t target) {
    for(int i = 0; i < symtab_length; i++){
        if(target == symtab_ftrace[i].value && symtab_ftrace[i].type){
            printf("0x%x: call[%s@0x%x]\n", pc, symtab_ftrace[i].name, target);
        }
    }
}

void trace_func_return(paddr_t pc, paddr_t target) {
    for(int i = 0; i < symtab_length; i++){
        if(target >= symtab_ftrace[i].value && (target < symtab_ftrace[i].value + symtab_ftrace[i].size) && symtab_ftrace[i].type){
            printf("0x%x: ret[%s@0x%x]\n", pc, symtab_ftrace[i].name, target);
        }
    }
}