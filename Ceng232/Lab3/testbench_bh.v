`timescale 1ns / 1ps

module testbench_bh;
    // Inputs
	reg B;
	reg H;
	reg clk;
	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	bh uut (
		.B(B),
		.H(H),
		.clk(clk),
		.Q(Q)
	);

    integer grade = 0;

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
    initial clk = 0;
	always #5 clk = ~clk;
	initial begin
		// Set monitor for inputs and outputs.
        $monitor("Time=%.2d | B=%b H=%b| Q=%b", $time, B, H, Q);

        //==========================//
        //       INITIAL VAL        //
        //==========================//
        // Assume initial value of Q is Zero
		#1; //(1ns)Check Initial Q value
		if (Q != 1'b1) $display("Initial value of Q is wrong");
		else grade = grade + 1;

        //==========================//
        //        SETO TO 1         //
        //==========================//
		#1; //(2ns) Set BH=01, (set to one)
		B = 1'b0; H = 1'b1;
		#5; //(7ns) Wait for clock edge
		if (Q != 1'b1) $display("Value of Q after Qprev=0 B=0 H=0 is wrong");
		else grade = grade + 2;

        //==========================//
        //       COMPLEMENT         //
        //==========================//
        #1; //(8ns) Set BH=00, complement
		B = 1'b0; H = 1'b0;
		#8; //(16ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=1 B=1 H=1 is wrong");
		else grade = grade + 2;
        #10; //(26ns) Check the other cycle value
		if (Q != 1'b1) $display("Value of Q after Qprev=0 B=1 B=1 is wrong");
		else grade = grade + 1;

        //==========================//
        //       SET TO ZERO        //
        //==========================//
		#1; //(27ns) Set BH=10, set to zero
		B = 1'b1; H = 1'b0;
		#9; //(36ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=1 B=1 H=0 is wrong");
		else grade = grade + 1;

        //==========================//
        //       NO CHANGE          //
        //==========================//
		#1; //(37ns) Set BH=11, no change
		B = 1'b1; H = 1'b1;
		#9; //(46ns) Wait for clock edge
		if (Q != 1'b0) $display("Value of Q after Qprev=0 B=0 H=0 is wrong");
		else grade = grade + 2;
		#10; //(56ns) Wait for clock edge again
		if (Q != 1'b0) $display("Value of Q after Qprev=1 B=1 H=0 is wrong");
		else grade = grade + 1;
		#5;
		$display("Result is:%d", grade);
		$finish;
	end

endmodule

