#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>


#include "VTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#ifndef BIN_FILE_PATH
#define BIN_FILE_PATH "/home/yuan/Documents/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-riscv64-npc.bin"
#endif

const int MEM_SIZE = 10000;
std::vector<uint32_t> pmem;

int pmem_read(uint32_t pc){
	return pmem[pc-0x80000000];
	/*
	if(pc == 0x80000000){return 0x00100093;}
	else if(pc == 0x80000004){return 0x00200113;}
	else if(pc == 0x80000008){return 0x01008193;}
	else if(pc == 0x8000000c){return 0x02010213;}
	else if(pc == 0x80000010){return 0x00f00013;}
	else if(pc == 0x80000014){return 0x00100073;}
	else return 0x00f00013;
	*/
}

void pmem_set(){
	
	std::ifstream file(std::string(BIN_FILE_PATH), std::ios::binary);
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

    // Store data in 4-byte integers
    pmem.clear();
    for (size_t i = 0; i + 3 < buffer.size(); i += 4) {
        uint32_t data = (buffer[i]) | (buffer[i + 1] << 8) | (buffer[i + 2] << 16) | (buffer[i + 3] << 24);
        pmem.push_back(data);
    }
	
	// print pmem
	
    std::cout << "Array elements (hex): ";
    for (size_t i = 0; i < pmem.size(); ++i) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << pmem[i] << " ";
    }
    std::cout << std::endl;
	
	
}

int main(int argc, char** argv)
{
	pmem_set();
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
		if(top->is_ebreak == 1){break;}
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
