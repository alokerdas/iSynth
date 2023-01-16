module test (a, ctrl, o);
  input a, ctrl;
  output o;
  bufif1 (o, a, ctrl);
endmodule
