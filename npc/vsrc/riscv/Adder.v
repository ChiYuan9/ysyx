module Adder #(parameter DATA_LEN = 64)(
    input wire [DATA_LEN-1:0] addend_a,
    input wire [DATA_LEN-1:0] addend_b,
    output reg [DATA_LEN-1:0] sum
);
reg [DATA_LEN:0] carry; // Extend carry to DATA_LEN+1 bits to handle the initial carry

always @(*) begin
    carry[0] = 1'b0; // Initial carry is 0
    for (int n = 0; n < DATA_LEN; n = n + 1) begin
        // Calculate sum and carry-out for each bit position
        {carry[n+1], sum[n]} = addend_a[n] + addend_b[n] + carry[n];
    end
end

endmodule
