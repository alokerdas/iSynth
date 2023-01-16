module test (a, ctrl, o);
  input a, ctrl;
  output o;
  rcmos (o, a, ctrl, ctrl);
endmodule
