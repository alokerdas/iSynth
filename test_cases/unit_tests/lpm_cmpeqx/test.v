module test (o, a, b);
  input [1:0] a, b;
  output [1:0] o;
  reg [1:0] o;
  always @* begin
    casez (a)
      2'b1?: o = b;
      2'b0?: o = 2'b11;
    endcase
  end
endmodule
