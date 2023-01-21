module test (s, c, a, b);
  input a, b;
  output s, c;
  assign {c, s} = a - b;
endmodule
