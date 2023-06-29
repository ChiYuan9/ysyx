module addsub_4(
	input [3:0] a,
	input [3:0] b,
	input is_add,
	output [3:0] out,
	output cout,
	output overflow
);

wire [3:0] b_input = is_add ? b : (~b + 1);

assign {cout, out} = a + b_input;
assign overflow = (a[3] == b_input[3]) && (out[3] != a[3]);

endmodule
