`timescale 1ns / 1ps


module testbench_ballot(
    );

	reg [1:0] mode;
	reg [5:0] userID;
	reg [1:0] candidate; // 00:Air 01:Fire, 10:Earth, 11: Water
	reg clk;
	wire [1:0] ballotBoxId;
	wire [5:0] numberOfRegisteredVoters;
	wire [5:0] numberOfVotesWinner; // number of votes of winner
	wire [1:0] WinnerId;
	wire AlreadyRegistered;
	wire AlreadyVoted;
	wire NotRegistered;
	wire VotingHasNotStarted;
	wire RegistrationHasEnded;
	integer grade,i, gradeLocal;
    reg caseFailed;

    reg [15:0] accum;

	// Instantiate the Unit Under Test (UUT)
   SelectionOfAvatar uut(
		mode,
		userID,
		candidate,
		clk,
		ballotBoxId,
        numberOfRegisteredVoters,
        numberOfVotesWinner,
        WinnerId,
        AlreadyRegistered,
        AlreadyVoted,
        NotRegistered,
        VotingHasNotStarted,
        RegistrationHasEnded
	);

    // At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
    initial clk = 0;
	always #2 clk = ~clk;

    always@(posedge clk) accum = accum + 1;

	initial begin

        accum = 0;
        $display("Starting Testbench");


		grade=0;
        caseFailed = 1;

		//Case 1: User 010101 succesfully registers
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b010101;
		#2;
        gradeLocal = 0;

		if (ballotBoxId == 2'b01) gradeLocal = gradeLocal+2;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 1) gradeLocal = gradeLocal+2;   else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 1"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 2: User 110101 succesfully registers
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b110101;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+2;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 2) gradeLocal = gradeLocal+1;   else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 2"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 3: User 100100 succesfully registers
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b100100;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b10) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 3) gradeLocal = gradeLocal+1;   else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 3"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 4: User 100100 tries to register again
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b100100;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b10) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 3) gradeLocal = gradeLocal+1;   else caseFailed = 1;
        if (AlreadyRegistered==1) gradeLocal = gradeLocal+2;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 4"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 5: User 100100 tries to VOTE
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b100100;
		candidate = 2'b00;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b10) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 3) gradeLocal = gradeLocal+1;   else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==1) gradeLocal = gradeLocal+2;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 5"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 6: non-Registered User 111100 tries to VOTE
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b111100;
		candidate = 2'b01;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 3) gradeLocal = gradeLocal+1;   else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		//if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==1) gradeLocal = gradeLocal+2;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 6"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;



		//========================//
		//  Register Some Users   //
		//========================//

		for (i=1;i<=60;i=i+1)begin
            #1;
    		mode=0;
			userID=i;
	    	#3;

		end
		for (i=1;i<=38;i=i+1)begin
            #1;
    		mode=0;
			userID=i;
	    	#3;
		end

		//Case 7: User 110100 tries to VOTE
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b110100;
		candidate = 2'b01;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;  else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 7"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 8: User 010100 tries to VOTE
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b010100;
		candidate = 2'b11;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b01) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;  else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 8"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 9: non-registered User 111101 tries to register
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b111101;
		//candidate = 2'b11;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;  else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==1) gradeLocal = gradeLocal+2;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 9"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 10: Registered User 000101 tries to register
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b000101;
		//candidate = 2'b11;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b00) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;      else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                     else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                    else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;              else caseFailed = 1;
		if (RegistrationHasEnded==1) gradeLocal = gradeLocal+2;             else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 10"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 11: Registered User 110100 tries to vote again
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b110100;
		candidate = 2'b00;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;  else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==1) gradeLocal = gradeLocal+2;                 else caseFailed = 1;
		if (NotRegistered==0) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 11"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//Case 12: non-Registered User 111101 tries to vote
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b111101;
		candidate = 2'b11;
		#3;
        gradeLocal = 0;

		if (ballotBoxId == 2'b11) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;  else caseFailed = 1;
        if (AlreadyRegistered==0) gradeLocal = gradeLocal+1;            else caseFailed = 1;
		if (AlreadyVoted==0) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (NotRegistered==1) gradeLocal = gradeLocal+1;                else caseFailed = 1;
		if (VotingHasNotStarted==0) gradeLocal = gradeLocal+1;          else caseFailed = 1;
		if (RegistrationHasEnded==0) gradeLocal = gradeLocal+1;         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 12"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		//========================//
		//  Some Users Vote       //
		//========================//

		for (i=1;i<=10;i=i+1)begin
            #1;
    		mode=1;
			userID=i;
			candidate = 2'b00;
	    	#3;

		end
		for (i=10;i<=40;i=i+1)begin
            #1;
    		mode=1;
			userID=i;
			candidate = 2'b01;
	    	#3;
		end
		for (i=41;i<=45;i=i+1)begin
            #1;
    		mode=1;
			userID=i;
			candidate = 2'b10;
	    	#3;
		end

		for (i=46;i<=60;i=i+1)begin
            #1;
    		mode=1;
			userID=i;
			candidate = 2'b11;
	    	#3;
		end
		#240;


		//Case 13: after 200 cycles
		#1;
        caseFailed = 0;
		mode=1;
		userID=6'b111101;
		candidate = 2'b11;
		#3;
        gradeLocal = 0;


		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+2;          else caseFailed = 1;
        if (numberOfVotesWinner==30) gradeLocal = gradeLocal+2;                 else caseFailed = 1;
		if (WinnerId==2'b01) gradeLocal = gradeLocal+1;                         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 13"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;


		//Case 14: after 200 cycles
		#1;
        caseFailed = 0;
		mode=0;
		userID=6'b111111;
		candidate = 2'b00;
		#3;
        gradeLocal = 0;


		if (numberOfRegisteredVoters == 60) gradeLocal = gradeLocal+1;          else caseFailed = 1;
        if (numberOfVotesWinner==30) gradeLocal = gradeLocal+1;                 else caseFailed = 1;
		if (WinnerId==2'b01) gradeLocal = gradeLocal+1;                         else caseFailed = 1;

        if(caseFailed) begin $display("Failed Case 14"); gradeLocal = gradeLocal >> 2; end
        grade = grade + gradeLocal;

		$display("Result %d",grade);
		$finish;

	end

endmodule