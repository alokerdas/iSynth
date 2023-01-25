module test (o, a, b);
  input [1:0] a, b;
  output o;
  assign o = a !=? b;
endmodule
