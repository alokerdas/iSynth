module test (a, o);
  input a;
  output o;
  assign o = a; // iverilog infers bufz instead of buf
endmodule
