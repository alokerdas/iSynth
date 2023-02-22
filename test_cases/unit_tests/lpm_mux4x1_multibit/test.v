module test (o, a, b, d, c, sl);
  input [3:0] a, b, d, c;
  input [1:0] sl;
  output [3:0] o;
  reg [3:0] o;
  always @*
    case (sl)
      'b00: o = a;
      'b01: o = b;
      'b10: o = c;
      'b11: o = d;
    endcase
endmodule
