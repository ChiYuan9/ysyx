module Decoder (
    input [31:0] inst,
    output [4:0] rs1,
    output [4:0] rs2,
    output [63:0] imm,
    output [4:0] rd,

    output is_addi,
    output is_ebreak,
    output is_jalr,

    output is_sd,

    output is_auipc,
    output is_lui,

    output is_jal
);
wire [6:0] opcode = inst[6:0];
wire [2:0] funct3 = inst[14:12];

// Inst type
// wire type_r = 
wire type_i = is_addi || is_ebreak || is_jalr; 
wire type_s = is_sd;
// wire type_b = 
wire type_u = is_auipc || is_lui;
wire type_j = is_jal;


assign rd = inst[11:7];
assign rs1 = inst[19:15];
assign rs2 = inst[24:20];

// I type
assign is_addi = (opcode == 7'b0010011) && (funct3 == 3'b000);
assign is_ebreak = (opcode == 7'b1110011) && (inst[31:20] == 12'h001);
assign is_jalr = (opcode == 7'b1100111) && (funct3 == 3'b000);
// S type
assign is_sd = (opcode == 7'b0100011) && (funct3 == 3'b011);
// u type
assign is_auipc = (opcode == 7'b0010111);
assign is_lui = (opcode == 7'b0110111);
// J type
assign is_jal = (opcode == 7'b1101111);


wire [63:0] imm_i = {{53{inst[31]}}, inst[30:20]};
wire [63:0] imm_s = {{53{inst[31]}}, inst[30:25], inst[11:7]};
wire [63:0] imm_u = {{33{inst[31]}}, inst[30:12], 12'b0};
wire [63:0] imm_j = {{44{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};
assign imm = type_i ? imm_i :
                type_s ? imm_s :
                type_u ? imm_u : 
                type_j ? imm_j : 64'b0;
endmodule
