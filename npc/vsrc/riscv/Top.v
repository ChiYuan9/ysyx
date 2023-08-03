module Top (
    input clk,
    input rst,

    input [31:0] inst,
    output reg [31:0] pc,
    output [63:0] wdata,
    output [63:0] tmp
);

    // PC update
    reg [31:0] snpc;
    assign snpc = pc + 4;
    Reg #(32, 32'h80000000) pc_i (clk, rst, snpc, pc, 1'b1);
    // IDU
    wire [4:0] rs1, rs2, rd;
    wire [63:0] imm;
    wire is_addi;
    Decoder dec_i(inst, rs1, rs2, imm, rd, is_addi);
    // RegisterFile
    wire [63:0] src1, src2;
    RegisterFile regfile_i(clk, wdata, rd, is_addi, rs1, rs2, src1, src2);
    // EXU
    assign wdata = src1 + imm;
    assign tmp = src2;
endmodule
