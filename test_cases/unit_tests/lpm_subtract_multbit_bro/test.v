module test (s, c, a, b);
  input [3:0] a, b;
  output [3:0] s;
  output c;
  assign {c, s} = a - b;
endmodule
