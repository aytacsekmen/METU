`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end
	
 
   always @ (posedge clk)  
      case ({B,H})  
         2'b00 :  Q <= ~Q;  
         2'b01 :  Q <= 1;  
         2'b10 :  Q <= 0;  
         2'b11 :  Q <= Q;  
      endcase
	// You can implement your code here
    // ...

endmodule

module ic1337(// Inputs
              input A0,
              input A1,
              input A2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

	// You can implement your code here
    // ...
	 assign B1= (A0^~A1)|A2;
	 assign H1= A0 & ~A2;
	 assign B2= A0 & ~A2;
	 assign H2= ~(~A0 | A1)&A2;
	 
	 
	 bh bh_ff1(B1,H1,clk,Q0);
	 bh bh_ff2(B2,H2,clk,Q1);
	 
	 assign Z=~(Q0^Q1);

	 
				
endmodule