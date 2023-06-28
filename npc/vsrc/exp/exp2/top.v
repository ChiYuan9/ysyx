module top(
	input [7:0] in,
	output [7:0] seg0_pointer,
	output [7:0] seg1_encode0,
	output [7:0] seg2_encode1,
	output [7:0] seg3_encode2,
	output [7:0] seg4_decode
);

wire [2:0] out_encode;
wire out_pointer;
encode_83 ins_encode(in, 1'b1, out_encode, out_pointer);

wire [3:0] in_seg0, in_seg1, in_seg2, in_seg3;
assign in_seg0 = out_pointer ? 4'b0001 : 4'b0000;
assign in_seg1 = out_encode[0] ? 4'b0001 : 4'b0000;
assign in_seg2 = out_encode[1] ? 4'b0001 : 4'b0000;
assign in_seg3 = out_encode[2] ? 4'b0001 : 4'b0000;

bcd7seg ins_seg0(in_seg0, seg0_pointer);
bcd7seg ins_seg1(in_seg1, seg1_encode0);
bcd7seg ins_seg2(in_seg2, seg2_encode1);
bcd7seg ins_seg3(in_seg3, seg3_encode2);

wire [7:0] out_decode;
decode_38 ins_decode(out_encode, out_decode);

bcd7seg ins_seg4({1'b0, out_encode}, seg4_decode);

endmodule
