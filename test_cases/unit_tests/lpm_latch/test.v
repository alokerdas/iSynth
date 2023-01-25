module test (q, d, ck);
  input d, ck;
  output q;
  reg q;
  always @* begin
    if (ck)
     q = d;
  end
endmodule
