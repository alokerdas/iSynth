module test (o, a);
  input a;
  output o;
  assign o = ~& a;
endmodule
