#include <stdio.h>
#include <stdlib.h>

#include "VTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
int pmem_read(int pc){
	if(pc == 0x80000000){return 0x00100093;}
	else if(pc == 0x80000004){return 0x00200113;}
	else if(pc == 0x80000008){return 0x01008193;}
	else if(pc == 0x8000000c){return 0x02010213;}
	else if(pc == 0x80000010){return 0x00f00013;}
	else if(pc == 0x80000014){return 0x00100073;}
	else return 0x00f00013;
}

int main(int argc, char** argv)
{
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
