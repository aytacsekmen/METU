`timescale 1ns / 1ps
module lab3_2(
			input[5:0] money,
			input CLK,
			input vm, //0:VM0, 1:VM1
			input [2:0] productID, //000:sandwich, 001:chocolate, 11x: dont care
			input sugar, //0: No sugar, 1: With Sugar
			output reg [5:0] moneyLeft,
			output reg [4:0] itemLeft,
			output reg productUnavailable,//1:show warning, 0:do not show warning
			output reg insufficientFund , //1:full, 0:not full
			output reg notExactFund , //1:full, 0:not full
			output reg invalidProduct, //1: empty, 0:not empty
			output reg sugarUnsuitable, //1: empty, 0:not empty
			output reg productReady	//1:door is open, 0:closed
	);

	// Internal State of the Module
	// (you can change this but you probably need this)
	reg [4:0] numOfSandwiches;
	reg [4:0] numOfChocolate;
	reg [4:0] numOfWaterVM0;
	reg [4:0] numOfWaterVM1;
	reg [4:0] numOfCoffee;
	reg [4:0] numOfTea;
	/*wire [5:0] sandwichPrice;
	wire  [5:0] chocolatePrice;
	wire  [5:0] waterPrice;
	wire  [5:0] coffeePrice;
	wire  [5:0] teaPrice;*/

	initial
	begin
		// You can initialize here
    	// ...
		numOfSandwiches = 5'b01010;
		numOfChocolate = 5'b01010;
		numOfWaterVM0 = 5'b00101;
		numOfWaterVM1 = 5'b01010;
		numOfCoffee = 5'b01010;
		numOfTea = 5'b01010;
		productUnavailable=0;//1:show warning, 0:do not show warning
		insufficientFund=0 ; //1:full, 0:not full
		notExactFund=0; //1:full, 0:not full
		invalidProduct=0; //1: empty, 0:not empty
		sugarUnsuitable=0; //1: empty, 0:not empty
		productReady=0;	//1:door is open, 0:closed
		/*sandwichPrice=6'b010100;
		chocolatePrice=6'b001010;
		waterPrice=6'b000101;
		coffeePrice=6'b001100;
		teaPrice=6'b001000;*/
		
	end
	
	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin
		
		productUnavailable=0;//1:show warning, 0:do not show warning
		insufficientFund=0 ; //1:full, 0:not full
		notExactFund=0; //1:full, 0:not full
		invalidProduct=0; //1: empty, 0:not empty
		sugarUnsuitable=0; //1: empty, 0:not empty
		productReady=0;	//1:door is open, 0:closed
		// You can implement your code here
    	// ...
		/*case ({B,H})  
         2'b00 :  Q <= ~Q;  
         2'b01 :  Q <= 1;  
         2'b10 :  Q <= 0;  
         2'b11 :  Q <= Q;  
      endcase
		*/
		if(vm==0)
		begin
			case (productID)  
         3'b000 :  begin //Sandwiches case for vm0
							if(numOfSandwiches==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money!=6'b010100)
								begin
								notExactFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfSandwiches=numOfSandwiches-5'b00001;
								itemLeft=numOfSandwiches;
								moneyLeft=6'b000000;
								end
							end
							
						 end
         3'b001 :  begin //Chocolate case for vm0
							if(numOfChocolate==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money!=6'b001010)
								begin
								notExactFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfChocolate=numOfChocolate-5'b00001;
								itemLeft=numOfChocolate;
								moneyLeft=6'b000000;
								end
							end
							
						 end  
         3'b010 :  begin //water case for wm0
							if(numOfWaterVM0==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money!=6'b000101)
								begin
								notExactFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfWaterVM0=numOfWaterVM0-5'b00001;
								itemLeft=numOfWaterVM0;
								moneyLeft=6'b000000;
								end
							end
							
						 end  
         3'b011 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end
			3'b100 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end
			3'b101 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end	
			3'b110 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end	
			3'b111 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end				
			
      endcase
		
		end
		else
		begin
		
		case (productID)  
         3'b000 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end
         3'b001 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end
         3'b010 :  begin //water case for wm1
							if(sugar==1)
							begin
								sugarUnsuitable=1;
								moneyLeft=money;
							end
							
							else
							begin
							if(numOfWaterVM1==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money<6'b000101)
								begin
								insufficientFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfWaterVM1=numOfWaterVM1-5'b00001;
								itemLeft=numOfWaterVM1;
								moneyLeft=money-6'b000101;
								end
							end
							end
						 end  
         3'b011 :  begin //coffee case for wm1
							if(numOfCoffee==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money<6'b001100)
								begin
								insufficientFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfCoffee=numOfCoffee-5'b00001;
								itemLeft=numOfCoffee;
								moneyLeft=money-6'b001100;
								end
							end
							
						 end
			3'b100 :  begin //tea case for wm1
							if(numOfTea==5'b00000)
							begin
								productUnavailable=1;
								moneyLeft=money;
							end
							
							else
							begin
								if(money<6'b001000)
								begin
								insufficientFund=1;
								moneyLeft=money;
								end
								else
								begin
								productReady=1;
								numOfTea=numOfTea-5'b00001;
								itemLeft=numOfTea;
								moneyLeft=money-6'b001000;
								end
							end
							
						 end
			3'b101 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end	
			3'b110 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end	
			3'b111 :  begin
							invalidProduct=1;
							moneyLeft=money;
						 end			
			
      endcase
		
		end
	end


endmodule
