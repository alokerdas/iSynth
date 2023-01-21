module test (s, a, b);
  input [3:0] a, b;
  output [3:0] s;
  assign s = a - b;
endmodule
