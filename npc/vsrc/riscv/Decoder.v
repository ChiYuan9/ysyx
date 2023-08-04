module Decoder (
    input [31:0] inst,
    output [4:0] rs1,
    output [4:0] rs2,
    output [63:0] imm,
    output [4:0] rd,

    output is_addi,
    output is_ebreak
);

wire [6:0] opcode = inst[6:0];
assign rd = inst[11:7];
wire [2:0] funct3 = inst[14:12];
assign rs1 = inst[19:15];
assign rs2 = inst[24:20];
wire [11:0] imm_i = inst[31:20];

assign is_addi = (opcode == 7'b0010011) && (funct3 == 3'b000);
assign is_ebreak = (opcode == 7'b1110011) && (inst[31:20] == 12'h001);

assign imm = {{52{imm_i[11]}}, imm_i};
endmodule
