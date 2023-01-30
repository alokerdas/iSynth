module test (o, a);
  input [7:0] a;
  output o;
  assign o = ~& a;
endmodule
