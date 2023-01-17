module test (q, d, ck, st);
  input d, ck, st;
  output q;
  reg q;
  always @ (negedge ck or posedge st) begin
    if (st)
      q <= 1;
    else
      q <= d;
  end
endmodule
