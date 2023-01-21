module test (o, a, b);
  input a, b;
  output [1:0] o;
  assign o = {b, a};
endmodule
