module RegisterFile #(ADDR_WIDTH = 32, DATA_WIDTH = 64) (
    input clk,
    input [DATA_WIDTH-1:0] wdata,
    input [4:0] waddr,
    input wen,

    input [4:0] rs1,
    input [4:0] rs2,
    output [DATA_WIDTH-1:0] src1,
    output [DATA_WIDTH-1:0] src2
);
    reg [DATA_WIDTH-1:0] rf[ADDR_WIDTH-1:0];
    always @(posedge clk) begin
        if(wen) rf[waddr] <= wdata;
    end
    assign src1 = rf[rs1];
    assign src2 = rf[rs2];
    /*
    MuxKey #(32, ADDR_WIDTH, DATA_WIDTH) rf_i1(src1, rs1, {
        5'b00000, 64'b0, 5'b00001, rf[1],
        5'b00010, rf[2], 5'b00011, rf[3],
        5'b00100, rf[4], 5'b00101, rf[5],
        5'b00110, rf[6], 5'b00111, rf[7],
        5'b01000, rf[8], 5'b01001, rf[9],
        5'b01010, rf[10], 5'b01011, rf[11],
        5'b01100, rf[12], 5'b01101, rf[13],
        5'b01110, rf[14], 5'b01111, rf[15],
        5'b10000, rf[16], 5'b10001, rf[17],
        5'b10010, rf[18], 5'b10011, rf[19],
        5'b10100, rf[20], 5'b10101, rf[21],
        5'b10110, rf[22], 5'b10111, rf[23],
        5'b11000, rf[24], 5'b11001, rf[25],
        5'b11010, rf[26], 5'b11011, rf[27],
        5'b11100, rf[28], 5'b11101, rf[29],
        5'b11110, rf[30], 5'b11111, rf[31]
    });
    MuxKey #(32, ADDR_WIDTH, DATA_WIDTH) rf_i2(src2, rs2, {
        5'b00000, 64'b0, 5'b00001, rf[1],
        5'b00010, rf[2], 5'b00011, rf[3],
        5'b00100, rf[4], 5'b00101, rf[5],
        5'b00110, rf[6], 5'b00111, rf[7],
        5'b01000, rf[8], 5'b01001, rf[9],
        5'b01010, rf[10], 5'b01011, rf[11],
        5'b01100, rf[12], 5'b01101, rf[13],
        5'b01110, rf[14], 5'b01111, rf[15],
        5'b10000, rf[16], 5'b10001, rf[17],
        5'b10010, rf[18], 5'b10011, rf[19],
        5'b10100, rf[20], 5'b10101, rf[21],
        5'b10110, rf[22], 5'b10111, rf[23],
        5'b11000, rf[24], 5'b11001, rf[25],
        5'b11010, rf[26], 5'b11011, rf[27],
        5'b11100, rf[28], 5'b11101, rf[29],
        5'b11110, rf[30], 5'b11111, rf[31]
    });
    */
endmodule
