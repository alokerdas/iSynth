module test (a, ctrl, o);
  input a, ctrl;
  output o;
  cmos (o, a, ctrl, ctrl);
endmodule
