% Given alpha = 0.02;  epsilon = 0.03 
% Set the number of simulations to run, determined from Normal approximation
N = 1510;   

% Set the mean number of each type of ship per day, these are Poisson-distributed
lambdaBC = 50;  % Bulk Carriers
lambdaCS = 40;  % Container Ships
lambdaOT = 25;  % Oil Tankers

% Initialize a vector to store the total weight for each simulation
TotalWeight=zeros(N,1);

% Run the Monte Carlo simulation
for k=1:N;
    % Generate sample from Poisson distribution for bulk carriers
    U = rand; i = 0;
    F = exp(-lambdaBC);
    while (U>=F);
        i=i+1;
        F = F+exp(-lambdaBC)*lambdaBC^i/gamma(i+1);
    end;
    YBC = i; % YBC is the number of bulk carriers

    % Generate sample from Poisson distribution for container ships
    U = rand; i = 0;
    F = exp(-lambdaCS);
    while (U>=F);
        i=i+1;
        F = F+exp(-lambdaCS)*lambdaCS^i/gamma(i+1);
    end;
    YCS = i; % YCS is the number of container ships

    % Generate sample from Poisson distribution for oil tankers
    U = rand; i = 0;
    F = exp(-lambdaOT);
    while (U>=F);
        i=i+1;
        F = F+exp(-lambdaOT)*lambdaOT^i/gamma(i+1);
    end;
    YOT = i; % YOT is the number of oil tankers

    % Initialize the total weight for this run
    weight = 0;

    % Generate weights for each bulk carrier, container ship, and oil tanker 
    % and add them to the total weight for this run
    for f=1:YBC; % Bulk Carriers
        WBC = sum (-1/0.1 * log(rand(60,1)));
        weight = weight + WBC;    
    end;
    for f=1:YCS; % Container Ships
        WCS = sum (-1/0.05 * log(rand(100,1)));
        weight = weight + WCS;    
    end;
    for f=1:YOT; % Oil Tankers
        WOT = sum (-1/0.02 * log(rand(120,1)));
        weight = weight + WOT;    
    end;

    % Record the total weight for this run
    TotalWeight(k) = weight;
end;

% Calculate and print the estimated probability that total weight exceeds 300 tons
p_est = mean(TotalWeight>300000); 
fprintf('Estimated probability = %f\n',p_est);

% Calculate and print the expected total weight
expectedWeight = mean(TotalWeight);
fprintf('Expected weight = %f\n',expectedWeight);

% Calculate and print the standard deviation of total weight
stdWeight = std(TotalWeight);
fprintf('Standard deviation = %f\n',stdWeight);

%Estimated probability = 0.113245
%Expected weight = 260099.903603
%Standard deviation = 32719.016975