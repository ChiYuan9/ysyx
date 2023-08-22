#include <common.h>

#define MAX_IRINGBUF 30

typedef struct{
    word_t pc;
    uint32_t inst;
} ItraceNode;

ItraceNode iringbuf[MAX_IRINGBUF];
int pos_cur = 0;
bool full = false;

void display_inst() {
    if(!full && !pos_cur) { return; }
    int end = pos_cur - 1;
    int i = full ? pos_cur : 0;
    while(i != end){
        printf("PC: 0x%lx\t INST: 0x%08x\n", iringbuf[i].pc, iringbuf[i].inst);
        i = (i + 1) % MAX_IRINGBUF;
    }
    
}

void trace_inst(word_t pc, uint32_t inst) {
    iringbuf[pos_cur].pc = pc;
    iringbuf[pos_cur].inst = inst;

    pos_cur = (pos_cur + 1) % MAX_IRINGBUF;
    full = full || (pos_cur == MAX_IRINGBUF - 1);
}

