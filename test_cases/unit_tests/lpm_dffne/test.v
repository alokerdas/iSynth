module test (q, d, ck);
  input d, ck;
  output q;
  reg q;
  always @ (negedge ck) begin
    q <= d;
  end
endmodule
