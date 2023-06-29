module top(
	input [3:0] a,
	input [3:0] b,
	input [2:0] func,
	output [3:0] out,
	output cout,
	output overflow
);

wire cout_addsub, overflow_addsub;
wire [3:0] out_addsub;
wire is_add = func[2:0] == 3'b000 ? 1'b1 : 1'b0;
addsub_4 ins_addsub1(a, b, is_add, out_addsub, cout_addsub, overflow_addsub);

wire [3:0] out_not = ~a;

wire [3:0] out_and = a & b;

wire [3:0] out_or = a | b;

wire [3:0] out_xor = a ^ b;

wire [3:0] out_small = out_addsub[3] ? 4'b1111 : 4'b0000;

wire [3:0] out_equ = a==b ? 4'b1111 : 4'b0000;

assign out = func[2:1] == 2'b00 ? out_addsub :
	func[2:0] == 3'b010 ? out_not :
	func[2:0] == 3'b011 ? out_and :
	func[2:0] == 3'b100 ? out_or :
	func[2:0] == 3'b101 ? out_xor :
	func[2:0] == 3'b110 ? out_small :
	out_equ;

assign cout = func[2:1] == 2'b00 ? cout_addsub : 1'b0;

assign overflow = func[2:1] == 2'b00 ? overflow_addsub : 1'b0;

endmodule
