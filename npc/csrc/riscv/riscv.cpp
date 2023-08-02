#include "VTop.h"
#include "verilated.h"
static TOP_NAME top;

void single_cycle(){
	top->clk = 0; top->eval();
	top->clk = 1; top->eval();
}

void reset(int n){
	top->rst = 1;
	while(n-- > 0) single_cycle();
	top->rst = 0;
}

int pmem_read(int pc){
	if(pc = 0x80000000){return 0x00000093;}
	else if(pc = 0x800000004){return 0x00200113;}
	else if(pc = 0x800000008){return 0x01008193;}
	else if(pc = 0x80000000c){return 0x02010213;}
	else if(pc = 0x800000010){return 0x00f00013;}
}

int main(int argc, char** argv)
{
	verilatedContext* contextp = new VerilatedContext;
	reset(10);
	int i = 0;
	while(i <= 4){
		top->inst = pmem_read(top->pc);
		single_cycle();
	}
	delete top;
	delete contextp;
	return 0;
}
