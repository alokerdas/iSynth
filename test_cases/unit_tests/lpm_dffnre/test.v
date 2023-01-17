module test (q, d, ck, rst);
  input d, ck, rst;
  output q;
  reg q;
  always @ (negedge ck or posedge rst) begin
    if (rst)
      q <= 0;
    else
      q <= d;
  end
endmodule
