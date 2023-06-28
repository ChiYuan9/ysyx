#include "Vmux41_2.h"
#include <nvboard.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(Vmux41_2* top);


int main(int argc, char** argv)
{
	nvboard_bind_all_pins(&dut);
	nvboard_init();

	while(1){
		nvboard_update();
		dut.eval();
	}

	nvboard_quit();
	return 0;
}
