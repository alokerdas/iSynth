module test (o, a, b, d, c, e, f, g, h, sl);
  input [3:0] a, b, d, c, e, f, g, h;
  input [2:0] sl;
  output [3:0] o;
  reg [3:0] o;
  always @*
    case (sl)
      'b000: o = a;
      'b001: o = b;
      'b010: o = c;
      'b011: o = d;
      'b100: o = e;
      'b101: o = f;
      'b110: o = g;
      'b111: o = h;
    endcase
endmodule
