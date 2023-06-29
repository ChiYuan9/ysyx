module bcd7seg(
	input [3:0] num,
	output reg [7:0] display
);

always @(*) begin
	case(num)
		4'b0000 : display = 8'b00000011;
		4'b0001 : display = 8'b10011111;
		4'b0010 : display = 8'b00100101;
		4'b0011 : display = 8'b00001101;
		4'b0100 : display = 8'b10011001;
		4'b0101 : display = 8'b01001001;
		4'b0110 : display = 8'b01000001;
		4'b0111 : display = 8'b00011111;
		4'b1000 : display = 8'b00000001;
		4'b1001 : display = 8'b00001001;
		4'b1010 : display = 8'b00010001;
		4'b1011 : display = 8'b11000001;
		4'b1100 : display = 8'b01100011;
		4'b1101 : display = 8'b10000101;
		4'b1110 : display = 8'b01100001;
		4'b1111 : display = 8'b01110001;
	endcase
end

endmodule
