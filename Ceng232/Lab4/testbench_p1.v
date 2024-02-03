`timescale 1ns / 1ps

module testbench_p1;
	// Inputs and outputs
	reg CLK; real result=0;
	/*for ROM */ reg [2:0] MaskIndex; wire [7:0] MaskResult;
	/*for Difference_RAM*/ reg EncodingMode; reg [2:0] EncodingIndex; reg [7:0] EncodingNumber; reg [7:0] EncodingMask; wire [7:0] EncodingResult;
	/*for EncodedMemory*/ reg Mode; reg [2:0] Index; reg [7:0] Number; wire [7:0] Result;

	//instances
	ROM INSTANCE_ROM(MaskIndex, MaskResult);
	Difference_RAM INSTANCE_Difference_RAM(EncodingMode, EncodingIndex, EncodingNumber, EncodingMask, CLK, EncodingResult);
	EncodedMemory INSTANCE_EncodedMemory(Mode, Index, Number, CLK, Result);

	//Set initial values
	initial CLK = 0;
	always #5 CLK = ~CLK;

	initial begin
	//initialize all inputs to zero
	EncodingMode=1'b0; EncodingIndex=3'b000; EncodingNumber=8'b00000000; EncodingMask=8'b00000000;
	Mode=1'b0;Index =3'b000;Number=8'b00000000;
	//start testbench on ROM
	$display("Starting Testbench");
		#1//1
		MaskIndex=3'b000;
		#1//2
		if(MaskResult==8'b00000000) result=result+1; else $display("Timescale:%3d,Error in case 1",$time); /*case 1*/
		#1//3
		MaskIndex=3'b001;
		#1//4
		if(MaskResult==8'b01010101) result=result+1; else $display("Timescale:%3d,Error in case 2",$time);/*case 2*/
		#1//5
		MaskIndex=3'b010;
		#1//6
		if(MaskResult==8'b10101010) result=result+1; else $display("Timescale:%3d,Error in case 3",$time);/*case 3*/
		#1//7
		MaskIndex=3'b011;
		#1//8
		if(MaskResult==8'b00110011) result=result+1; else $display("Timescale:%3d,Error in case 4",$time);/*case 4*/
		#1//9
		MaskIndex=3'b100;
		#1//10
		if(MaskResult==8'b11001100) result=result+1; else $display("Timescale:%3d,Error in case 5",$time);/*case 5*/
		#1//11
		MaskIndex=3'b101;
		#1//12
		if(MaskResult==8'b00001111) result=result+1; else $display("Timescale:%3d,Error in case 6",$time);/*case 6*/
		#1//13
		MaskIndex=3'b110;
		#1//14
		if(MaskResult==8'b11110000) result=result+1; else $display("Timescale:%3d,Error in case 7",$time);/*case 7*/
		#1//15
		MaskIndex=3'b111;
		#1//16
		if(MaskResult==8'b11111111) result=result+1; else $display("Timescale:%3d,Error in case 8",$time);/*case 8*/

		//start testbench on Difference_RAM
		#6//22
		EncodingMode=1'b0;//write mode
		EncodingIndex=3'b000;
		EncodingNumber=8'b11001100;
		EncodingMask=  8'b10101010;
		#1//23
		//Result of previous write operation should not be changed before positive edge
		EncodingMode=1'b1;//read mode
		#1//24
		if (EncodingResult==8'b00000000) result=result+1; else $display("Timescale:%3d,Error in case 9",$time);/*case 9*/
		#3//27
		EncodingMode=1'b0;//write mode
		#9//36
		EncodingMode=1'b1;//read mode
		#1//37
		//Result should change after positive edge CLK.
		if (EncodingResult==8'b00100010) result=result+1;else $display("Timescale:%3d,Error in case 10",$time); /*case 10*/

		//start testbench on memory
		Mode=1'b0; //write mode
		Index =3'b000;
		Number=8'b11110000;
		#4 //41
		//Result of previous write operation should not be changed before positive edge
		Mode=1'b1;//read mode
		#1//42
		if (Result==8'b00000000) result=result+1; else $display("Timescale:%3d,Error in case 11",$time);/*case 11*/
		#1//43
		Mode=1'b0;//write mode
		#5//48
		Mode=1'b1;//read mode
		#1//49
		//Result should change after positive edge CLK.
		if (Result==8'b11110000) result=result+1; else $display("Timescale:%3d,Error in case 12",$time);/*case 12*/

		Mode=1'b0;//write mode
		Index=3'b111;
		Number=8'b10101010;


		while($time<=119)
		begin
			#10
			Index=Index+1;

		end
		//129
		Mode=1'b1;//read mode
		Index=3'b111;
		while($time<=144)
		begin
			#1
			Index=Index+1;
			#1
			case(Index)
			3'b000:if (Result==8'b10101010)  result=result+1; else $display("Timescale:%3d,Error in case 13",$time);/*case 13*/
			3'b001:if (Result==8'b01010101)  result=result+1; else $display("Timescale:%3d,Error in case 14",$time);/*case 14*/
			3'b010:if (Result==8'b00000000)  result=result+1; else $display("Timescale:%3d,Error in case 15",$time);/*case 15*/
			3'b011:if (Result==8'b01110111)  result=result+1; else $display("Timescale:%3d,Error in case 16",$time);/*case 16*/
			3'b100:if (Result==8'b00100010)  result=result+1; else $display("Timescale:%3d,Error in case 17",$time);/*case 17*/
			3'b101:if (Result==8'b10011011)  result=result+1; else $display("Timescale:%3d,Error in case 18",$time);/*case 18*/
			3'b110:if (Result==8'b01000110)  result=result+1; else $display("Timescale:%3d,Error in case 19",$time);/*case 19*/
			3'b111:if (Result==8'b01010101)  result=result+1; else $display("Timescale:%3d,Error in case 20",$time);/*case 20*/
			endcase
		end
		#20
		$display("Result is:%2.2f",result); //max 20
		$finish;
	end

endmodule

