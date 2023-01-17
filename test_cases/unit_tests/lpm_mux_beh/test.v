module test (o, d, c, sl);
  input d, c, sl;
  output o;
  reg o;
  always @*
    if (sl)
      o = c;
    else
      o <= d;
endmodule
