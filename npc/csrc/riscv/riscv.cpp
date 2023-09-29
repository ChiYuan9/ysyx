#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>
#include <cstdlib>


#include "VTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "verilated_dpi.h"

#include "/home/yuan/Documents/ysyx-workbench/nemu/src/utils/disasm.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */



const int MEM_SIZE = 10000;
uint64_t *cpu_gpr = NULL;
char buf_assembly[128];

extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}

// std::vector<uint8_t> pmem;
uint8_t pmem[100000];
std::string sdbInput, command;
std::vector<std::string> arguments;

std::vector<std::string> get_command(const std::string& input, std::string& command);
void dump_gpr();

int pmem_read(uint64_t pc){
	uint32_t inst = pmem[pc-0x80000000] | (pmem[pc+1-0x80000000] << 8) | (pmem[pc+2-0x80000000] << 16) | (pmem[pc+3-0x80000000] << 24);
	return inst;
}

void pmem_set(){
	const char* filePath = FILE_PATH;
    std::cout << "File path: " << filePath << std::endl;
	std::ifstream file(std::string(FILE_PATH), std::ios::binary);
	if (!file.is_open()) {
    	std::cerr << "Failed to open the file." << std::endl;
    	return;
	}


	file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

	// Read the entire file into a vector
    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    file.close();

    // pmem.clear();
    for (size_t i = 0; i + 3 < buffer.size(); i += 4) {
		uint8_t data = buffer[i];
		// pmem.push_back(data);
		// data = buffer[i+1];
		// pmem.push_back(data);
		// data = buffer[i+2];
		// pmem.push_back(data);
		// data = buffer[i+3];
		// pmem.push_back(data);
		pmem[i] = data;
		data = buffer[i+1];
		pmem[i + 1] = data;
		data = buffer[i+2];
		pmem[i + 2] = data;
		data = buffer[i+3];
		pmem[i + 3] = data;

    }
}

int main(int argc, char** argv)
{
	pmem_set();
	int i = 0;
	bool continue_sdb = false;
	int siCount_sdb = 0;

	VerilatedContext* contextp = new VerilatedContext;
  	contextp->commandArgs(argc, argv);
  	VTop* top = new VTop{contextp};

	VerilatedVcdC* tfp = new VerilatedVcdC;
	contextp->traceEverOn(true);
  	top->trace(tfp, 0);
  	tfp->open("wave.vcd");
	// reset
	top->rst = 1;
	top->clk = 0; top->eval();
	top->clk = 1; top->eval();
	top->rst = 0;
	while(true){
		if(continue_sdb == false && siCount_sdb == 0){

			std::cout << "(sdb): ";
			std::getline(std::cin, sdbInput);
			// std::cout << sdbInput << std::endl;
			arguments = get_command(sdbInput, command);

			if(command == "c"){
				continue_sdb = true;
				arguments.clear();
			} else if(command == "si"){
				if(arguments.empty()){
					printf("Need a argument\n");
					continue;
				}
				siCount_sdb = std::stoi(arguments[0]);
				arguments.clear();
				continue;
			} else if(command == "info"){
				printf("PC: 0x%lx\n", top->pc);
				dump_gpr();
				arguments.clear();
				continue;
			} else if(command == "x"){
				if(arguments.empty()){
					printf("Need two arguments\n");
					continue;
				}
				int num = std::stoi(arguments[0]);
				uint64_t addr_start = std::stoull(arguments[1], nullptr, 16);
				for(int i = 0; i < num; i++){
					printf("0x%lx: 0x%x\n", addr_start+4*i, pmem_read(addr_start+4*i));
				}
				arguments.clear();
				continue;
			} else{
				continue;
			}

		}
		if(siCount_sdb > 0){ siCount_sdb--;}

		// Trace
		printf("0x%x\n", pmem_read(top->pc));
		void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
		char disasm_buf[128];
		char *disasm_p;
		disassemble(disasm_p, 100, top->pc, pmem, 4);

		// Realize HIT GOOD/BAD TRAP
		if(top->is_ebreak == 1){
			std::cout << GREEN << "HIT GOOD TRAP" << RESET << std::endl;
			break;
		}
		i++;
		if(i==10000){
			std::cout << RED << "HIT BAD TRAP" << RESET << std::endl;
			break;
		}
		
		top->inst = pmem_read(top->pc);
		top->clk = 0; top->eval();
		tfp->dump(contextp->time());
		contextp->timeInc(1);
		top->clk = 1; top->eval();
		top->inst = pmem_read(top->pc); top->eval();
		
		tfp->dump(contextp->time());
		contextp->timeInc(1);
	}
	delete top;
	tfp->close();
	delete contextp;
	return 0;
}


std::vector<std::string> get_command(const std::string& input, std::string& command) {
    std::istringstream iss(input);
    
    iss >> command;
    
    std::vector<std::string> arguments;
    std::string arg;
    
    while (iss >> arg) {
        arguments.push_back(arg);
    }

    return arguments;
}

void dump_gpr() {
  int i;
  for (i = 0; i < 32; i++) {
    printf("gpr[%d] = 0x%lx\t", i, cpu_gpr[i]);
  }
  printf("\n");
}
