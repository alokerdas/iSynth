module test (a, ctrl, o);
  input a, ctrl;
  output o;
  bufif0 (o, a, ctrl);
endmodule
