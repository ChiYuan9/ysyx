module encode_83(
	input [7:0] in,
	input en,
	output reg [2:0] out,
	output pointer
);
always @(en or in) begin
	if(en) begin
		casez(in)
			8'b1??????? : out = 3'b111;
			8'b01?????? : out = 3'b110;
			8'b001????? : out = 3'b101;
			8'b0001???? : out = 3'b100;
			8'b00001??? : out = 3'b011;
			8'b000001?? : out = 3'b010;
			8'b0000001? : out = 3'b001;
			8'b00000001 : out = 3'b000;
			default : out = 3'b000;
		endcase
	end
	else
		out = 0;
end

assign pointer = (in == 8'b0) ? 1'b0 : 1'b1;

endmodule
