module test (o, d, c, sl);
  input d, c, sl;
  output o;
  assign o = sl ? c : d;
endmodule
