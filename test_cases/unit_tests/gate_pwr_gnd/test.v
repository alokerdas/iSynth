module test (a, o);
  output a;
  output o;
  supply1 _vdd;
  supply0 _vss;
  assign o = _vdd;
  assign a = _vss;
endmodule
