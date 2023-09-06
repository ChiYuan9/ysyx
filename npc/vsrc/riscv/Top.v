module Top (
    input clk,
    input rst,

    input wire [31:0] inst,
    output reg [63:0] pc,

    output wire is_ebreak,
    output wire is_sd,
    output wire [63:0] src2

);

    // PC update
    reg [63:0] snpc;
    assign snpc = is_jal ? (pc + imm) :
                    is_jalr ? (src1 + imm) & 64'hfffffffe : pc + 4;
    Reg #(64, 64'h80000000) pc_i (clk, rst, snpc, pc, 1'b1);


    // IDU
    wire [4:0] rs1, rs2, rd;
    wire [63:0] imm;
    wire is_addi;
    wire is_jalr;

    // wire is_sd;

    wire is_auipc;
    wire is_lui;

    wire is_jal;

    Decoder dec_i(inst, rs1, rs2, imm, rd, is_addi, is_ebreak, is_jalr, is_sd, is_auipc, is_lui, is_jal);


    // RegisterFile
    wire [63:0] src1, wdata;
    wire wen;
    assign wen = is_addi || is_auipc || is_lui || is_jal || is_jalr;
    RegisterFile regfile_i(clk, wdata, rd, wen, rs1, rs2, src1, src2);

    
    // EXU
    wire [63:0] addend_a, addend_b;
    assign addend_a = is_addi ? src1 :
                        (is_auipc || is_jal || is_jalr) ? pc : 
                        is_lui ? 64'b0 : 64'b0;
    assign addend_b = (is_addi || is_auipc|| is_lui) ? imm :
                        (is_jal || is_jalr) ? 64'b100 : 64'b0;
    Adder add_i(addend_a, addend_b, wdata);
endmodule
