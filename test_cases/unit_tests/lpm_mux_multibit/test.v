module test (o, d, c, sl);
  input [3:0] d, c;
  input sl;
  output [3:0] o;
  assign o = sl ? c : d;
endmodule
