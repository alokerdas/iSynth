module test (q, d, ck, st);
  input d, ck, st;
  output q;
  reg q;
  always @ (posedge ck or posedge st) begin
    if (st)
      q <= 1;
    else
      q <= d;
  end
endmodule
