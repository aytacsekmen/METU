`timescale 1ns / 1ps
module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, // 00:Air 01:Fire, 10:Earth, 11: Water
	input CLK,
	output reg [1:0] ballotBoxId,
	output reg [5:0] numberOfRegisteredVoters,
	output reg [5:0] numberOfVotesWinner, // number of votes of winner
	output reg [1:0] WinnerId,
	output reg AlreadyRegistered,
	output reg AlreadyVoted,
	output reg NotRegistered,
	output reg VotingHasNotStarted,
	output reg RegistrationHasEnded
	);
	integer number_clock;
	reg [1:0] members [63:0];
	reg [5:0] candidates_vote_number [3:0];
	integer loop;
	integer loop2;
	integer loop3;
	reg [1:0] temp_winnerID;
	reg [5:0] temp_winner_vote;
	
	
	
	
	
	initial begin
		// ...
		number_clock=0;
		numberOfRegisteredVoters=6'b00000;
		numberOfVotesWinner=6'b00000;
		AlreadyRegistered=0;
		AlreadyVoted=0;
		NotRegistered=0;
		WinnerId=0;
		VotingHasNotStarted=0;
		RegistrationHasEnded=0;
		temp_winnerID=2'b00;
		temp_winner_vote=6'b000000;
		loop3=0;
		loop=0;
	   loop2=0;
		
		for (loop = 0; loop < 64; loop = loop + 1) begin
			members[loop] = 2'b00;
		end
		
		for (loop2 = 0; loop2 < 4; loop2 = loop2 + 1) begin
			candidates_vote_number[loop2] = 6'b000000;
		end
	
	end

	always @(posedge CLK)
	begin
		AlreadyRegistered=0;
		AlreadyVoted=0;
		WinnerId=0;
		NotRegistered=0;
		VotingHasNotStarted=0;
		RegistrationHasEnded=0;
		// ...
		number_clock=number_clock+1;
		if(number_clock<=100)//registration process
		begin
			if(mode==0)//correct mode
			begin
				if(members[userID][0]==0)//not registered yet
				begin
					members[userID][0]=1;
					numberOfRegisteredVoters=numberOfRegisteredVoters+1;
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
				end
				else if(members[userID][0]==1)//already registered
				begin
					AlreadyRegistered=1;
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
				end
				
			end
			else if(mode==1)//wrong mode
			begin
				
					VotingHasNotStarted=1;
					
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
			end
		end
		else if(number_clock<=200 && number_clock>100)//vote process
		begin
			if(mode==0)//wrong mode
			begin
				RegistrationHasEnded=1;
				if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
			end
			else if(mode==1)//correct mode
			begin
			if(members[userID][1]==0)//not voted yet
				begin
				if(members[userID][0]==1)
				begin
					members[userID][1]=1;
					candidates_vote_number[candidate]=candidates_vote_number[candidate]+6'b000001;
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
				end
				else
				begin
					NotRegistered=1;
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
				end
			end
				else if(members[userID][1]==1)//already voted
				begin
					AlreadyVoted=1;
					if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
				end
			end
		end
		else if(number_clock>200)//result process
		begin
			//[1:0] temp_winnerID;
			//[5:0] temp_winner_vote;
			
			for (loop3 = 0; loop3 < 4; loop3 = loop3 + 1) begin
				if (candidates_vote_number[loop3]>temp_winner_vote)
				begin
				temp_winnerID=loop3;
				temp_winner_vote=candidates_vote_number[loop3];
				end
			end
			
			// [5:0] numberOfVotesWinner, // number of votes of winner
			// [1:0] WinnerId,
			
			WinnerId=temp_winnerID;
			numberOfVotesWinner=temp_winner_vote;
			

			
			if(userID>=48)
					begin
					ballotBoxId=2'b11;
					end
					else if(userID<=47 && userID>=32)
					begin
					ballotBoxId=2'b10;
					end
					else if(userID<=31 && userID>=16)
					begin
					ballotBoxId=2'b01;
					end
					else if(userID<=15 && userID >=0)
					begin
					ballotBoxId=2'b00;
					end
		end
	end

endmodule
