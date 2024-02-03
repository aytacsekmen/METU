`timescale 1ns / 1ps

module testbench_grader(
    );

			reg[5:0] money;
			reg CLK;
			reg vm;
			reg [2:0] productID;
			reg sugar;
			wire [5:0] moneyLeft;
			wire [4:0] itemLeft;
			wire productUnavailable;
			wire insufficientFund;
			wire notExactFund;
			wire invalidProduct;

			wire sugarUnsuitable;
			wire productReady;
			integer grade,i, gradeLocal;
            reg caseFailed;

			lab3_2 INSTANCE(money, CLK,  vm,  productID, sugar, moneyLeft,
					itemLeft, productUnavailable,  insufficientFund, notExactFund,
					invalidProduct, sugarUnsuitable,  productReady);


	initial CLK = 1;
	always #5 CLK = ~CLK;


	initial begin
		$display("Starting Testbench");
		grade=0;
        caseFailed = 1;

		//Case 1: succesfully buy item 000 from VM 0
		#1;
        caseFailed = 0;
		money = 6'b010100;
		vm = 1'b0;
		productID = 3'b000;
		#10;
        gradeLocal = 0;
		if (moneyLeft == 0) gradeLocal = gradeLocal+1;        else caseFailed = 1;
		if (itemLeft == 9) gradeLocal = gradeLocal+1;         else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1; else caseFailed = 1;
		if (notExactFund==0) gradeLocal = gradeLocal+1;       else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (productReady==1) gradeLocal = gradeLocal+1;       else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 1"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 2: succesfully buy item 001 from VM 0
        #1;
        caseFailed = 0;
		money = 10;
		vm = 1'b0;
		productID = 3'b001;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (itemLeft == 9) gradeLocal = gradeLocal+1;             else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (notExactFund==0) gradeLocal = gradeLocal+1;           else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (productReady==1) gradeLocal = gradeLocal+1;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 2"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 3: succesfully buy item 010 from VM 1
		#1;
        caseFailed = 0;
		money = 10;
		vm = 1'b1;
		productID = 3'b010;
		sugar =0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 5) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (itemLeft == 9) gradeLocal = gradeLocal+1;             else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (insufficientFund==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (sugarUnsuitable==0) gradeLocal = gradeLocal+1;        else caseFailed = 1;
		if (productReady==1) gradeLocal = gradeLocal+1;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 3"); grade = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 4: succesfully buy item 100 from VM 1
		#1;
        caseFailed = 0;
		money = 12;
		vm = 1'b1;
		productID = 3'b100;
		sugar = 0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 4) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (itemLeft == 9) gradeLocal = gradeLocal+1;             else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (insufficientFund==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (sugarUnsuitable==0) gradeLocal = gradeLocal+1;        else caseFailed = 1;
		if (productReady==1) gradeLocal = gradeLocal+1;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 4"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 4.5: succesfully buy item 010 from VM 0
		// Check copy paste error, water should be 4 now instead of 9
		#1;
        caseFailed = 0;
		money = 5;
		vm = 1'b0;
		productID = 3'b010;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (itemLeft == 4) gradeLocal = gradeLocal+1;             else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (notExactFund==0) gradeLocal = gradeLocal+1;           else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (productReady==1) gradeLocal = gradeLocal+1;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 4.5"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 5:  buy item 111 from VM 1 - invalidProduct
		#1;
        caseFailed = 0;
		money = 10;
		vm = 1'b1;
		productID = 3'b111;
		sugar = 0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 10) gradeLocal = gradeLocal+2;           else caseFailed = 1;
		if (invalidProduct==1) gradeLocal = gradeLocal+2;         else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+3;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 5"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 6:  buy item 111 from VM 0 - invalidProduct
		#1;
        caseFailed = 0;
		money = 0;
		vm = 1'b0;
		productID = 3'b111;
		sugar = 0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 0) gradeLocal = gradeLocal+2;        else caseFailed = 1;
		if (invalidProduct==1) gradeLocal = gradeLocal+2;     else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+3;       else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 6"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 7:  buy item 010 from VM 1 - insufficientFund
		#1;
        caseFailed = 0;
		money = 1;
		vm = 1'b1;
		productID = 3'b010;
		sugar = 0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 1) gradeLocal = gradeLocal+2;            else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (insufficientFund==1) gradeLocal = gradeLocal+4;         else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+2;         else caseFailed = 1;
		if (sugarUnsuitable==0) gradeLocal = gradeLocal+2;        else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+2;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 7"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 8:  buy item 000 from VM 0 - notExactFund
		#1;
        caseFailed = 0;
		money = 22;
		vm = 1'b0;
		productID = 3'b000;
		sugar = 0;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 22) gradeLocal = gradeLocal+2;           else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+2;         else caseFailed = 1;
		if (notExactFund==1) gradeLocal = gradeLocal+4;           else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+2;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 8"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 9: buy item 010 from VM 1 - sugarUnsuitable
		#1;
        caseFailed = 0;
		money = 20;
		vm = 1'b1;
		productID = 3'b010;
		sugar = 1;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 20) gradeLocal = gradeLocal+2;           else caseFailed = 1;
        if (productUnavailable==0) gradeLocal = gradeLocal+2;     else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+2;         else caseFailed = 1;
		if (sugarUnsuitable==1) gradeLocal = gradeLocal+4;        else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+2;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 9"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//========================//
		//   DEPLETING PRODUCTS   //
		//========================//
		for (i=1;i<=9;i=i+1)begin //Finishing sandwiches
		    #1;
    		money = 20;
	    	vm = 1'b0;
	    	productID = 3'b000;
	    	#9;
			$display("Sandwich Left VM0 %d", itemLeft);
		end

		for (i=1;i<=4;i=i+1)begin //Finishing water from VM0
	    	#1;
    		money = 5;
	    	vm = 1'b0;
	    	productID = 3'b010;
	    	#9;
		    $display("Water Left VM0 %d", itemLeft);
		end

		for (i=1;i<=9;i=i+1)begin //Finishing water from VM1
    		#1;
    		money = 5;
	    	vm = 1'b1;
	    	productID = 3'b010;
	    	sugar = 0;
	    	#9;
    		$display("Water Left VM1 %d", itemLeft);
		end


		//Case 10:  buy item 000 from VM 0 - productUnavailable
		#1;
        caseFailed = 0;
		money = 5;
		vm = 1'b0;
		productID = 3'b000;
		#10;
        gradeLocal = 0;
		if (moneyLeft == 5) gradeLocal = gradeLocal+2;        else caseFailed = 1;
        if (productUnavailable==1) gradeLocal = gradeLocal+4; else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;     else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+2;       else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 10"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 11:  buy item 010 from VM 1 - productUnavailable
		#1;
        caseFailed = 0;
		money = 2;
		vm = 1'b1;
		productID = 3'b010;
		sugar =1;
		#9;
        gradeLocal = 0;
		if (moneyLeft == 2) gradeLocal = gradeLocal+2;            else caseFailed = 1;
        if (productUnavailable==1) gradeLocal = gradeLocal+4;     else caseFailed = 1;
		if (invalidProduct==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;
		if (productReady==0) gradeLocal = gradeLocal+2;           else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 11"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		$display("Result is:%d",grade);
		$finish;
	end
endmodule
