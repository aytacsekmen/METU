`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);


	always @*
	begin
	// write your ROM code here
	case (addr)  
         3'b000 :  begin 
							 dataOut=8'b00000000;

						 end
         3'b001 :  begin 
							 dataOut=8'b01010101;

						 end  
         3'b010 :  begin 
							 dataOut=8'b10101010;

						 end  
         3'b011 :  begin 
							 dataOut=8'b00110011;

						 end
			3'b100 :  begin 
							 dataOut=8'b11001100;

						 end
			3'b101 :  begin 
							 dataOut=8'b00001111;

						 end	
			3'b110 :  begin 
							 dataOut=8'b11110000;

						 end	
			3'b111 :  begin 
							dataOut=8'b11111111;
							
						 end				
			
      endcase

end
endmodule

module Difference_RAM (
input mode,
input [2:0] addr,
input [7:0] dataIn,
input [7:0] mask,
input CLK,
output reg [7:0] dataOut);

reg [7:0] ram[7:0];

initial
	begin

		dataOut=8'b00000000;
		ram[0]=8'b00000000;
		ram[1]=8'b00000000;
		ram[2]=8'b00000000;
		ram[3]=8'b00000000;
		ram[4]=8'b00000000;
		ram[5]=8'b00000000;
		ram[6]=8'b00000000;
		ram[7]=8'b00000000;
		
		
	end

	// write your XOR_RAM code here
always @(posedge CLK)
	begin
	if (mode==0)
	begin
	case (addr)  
         3'b000 :  begin 
							if (dataIn> mask) begin
								ram[0]=dataIn-mask;
							end
							else begin
								ram[0]=mask- dataIn;
							end
							 

						 end
         3'b001 :  begin 
							 if (dataIn> mask) begin
								ram[1]=dataIn-mask;
							end
							else begin
								ram[1]=mask- dataIn;
							end

						 end  
         3'b010 :  begin 
							 if (dataIn> mask) begin
								ram[2]=dataIn-mask;
							end
							else begin
								ram[2]=mask- dataIn;
							end

						 end  
         3'b011 :  begin 
							 if (dataIn> mask) begin
								ram[3]=dataIn-mask;
							end
							else begin
								ram[3]=mask- dataIn;
							end

						 end
			3'b100 :  begin 
							 if (dataIn> mask) begin
								ram[4]=dataIn-mask;
							end
							else begin
								ram[4]=mask- dataIn;
							end

						 end
			3'b101 :  begin 
							 if (dataIn> mask) begin
								ram[5]=dataIn-mask;
							end
							else begin
								ram[5]=mask- dataIn;
							end

						 end	
			3'b110 :  begin 
							 if (dataIn> mask) begin
								ram[6]=dataIn-mask;
							end
							else begin
								ram[6]=mask- dataIn;
							end

						 end	
			3'b111 :  begin 
							if (dataIn> mask) begin
								ram[7]=dataIn-mask;
							end
							else begin
								ram[7]=mask- dataIn;
							end
							
						 end				
			
      endcase
	
	end
	
	end


always @(mode or addr)
	begin
	if (mode==1)
	begin
case (addr)  
         3'b000 :  begin 
							 dataOut=ram[0];

						 end
         3'b001 :  begin 
							 dataOut=ram[1];

						 end  
         3'b010 :  begin 
							 dataOut=ram[2];

						 end  
         3'b011 :  begin 
							 dataOut=ram[3];

						 end
			3'b100 :  begin 
							 dataOut=ram[4];

						 end
			3'b101 :  begin 
							 dataOut=ram[5];

						 end	
			3'b110 :  begin 
							 dataOut=ram[6];

						 end	
			3'b111 :  begin 
							 dataOut=ram[7];
							
						 end				
			
      endcase
	end
	
	end
	
	
	
	
	
	

endmodule


module EncodedMemory (
input mode,
input [2:0] index,
input [7:0] number,
input CLK,
output [7:0] result);

	wire [7:0] mask;

	ROM R(index, mask);
	Difference_RAM DR(mode, index, number, mask, CLK, result);

endmodule


