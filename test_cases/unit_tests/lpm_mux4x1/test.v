module test (o, a, b, d, c, sl);
  input a, b, d, c;
  input [1:0] sl;
  output o;
  reg o;
  always @*
    case (sl)
      'b00: o = a;
      'b01: o = b;
      'b10: o = c;
      'b11: o = d;
    endcase
endmodule
