VSRC = $(wildcard ./vsrc/tmp/top.v)
CSRC = $(wildcard ./csrc/tmp/sim_main.cpp)

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	
	verilator --cc --exe --build -j 0 -Wall --trace $(VSRC) $(CSRC)
	make -C obj_dir -f Vtop.mk Vtop
	./obj_dir/Vtop
include ../Makefile
