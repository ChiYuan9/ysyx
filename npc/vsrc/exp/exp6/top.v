module top(
	input clk,
	input rst,
	output reg [7:0] randNum,
	output [7:0] seg0,
	output [7:0] seg1
);
reg [7:0] randNum_tmp;
always @(posedge clk) begin
	if(rst)
		randNum_tmp <= 8'b00000001;
	else begin
		randNum_tmp[7] <= randNum[3] ^ randNum[2] ^ randNum[1] ^ randNum[0];
		randNum_tmp[6:0] <= randNum[7:1];
	end
end

assign randNum = randNum_tmp;

bcd7seg ins_seg0(randNum[3:0], seg0);
bcd7seg ins_seg1(randNum[7:4], seg1);

endmodule
