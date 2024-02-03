%a

%datas
mu = 175;
sigma = 7;
n = 1000;
x = normrnd(mu, sigma, n, 1);

%drawing the histogram
figure('Name','Part-a','NumberTitle','off');
histogram(x);


%b

%datas
mu=175;
sigma_6=6;
sigma_7=7;
sigma_8=8;

figure('Name','Part-b','NumberTitle','off');
hold on


%finding the corresponding y-values for possible x-values
x_6 = [175-28:.1:175+28];
y_6 = normpdf(x_6,mu,sigma_6);

x_7 = [175-28:.1:175+28];
y_7 = normpdf(x_7,mu,sigma_7);

x_8 = [175-28:.1:175+28];
y_8 = normpdf(x_8,mu,sigma_8);


%drawing the graphs in single plot using hold on-off calls
plot(x_6,y_6);
plot(x_7,y_7);
plot(x_8,y_8);

legend({'sigma=6','sigma=7','sigma=8'},'Location','southwest')
hold off




%c part

%datas
mu = 175;
sigma = 7;
n = 150;
percentages = [0.45, 0.5, 0.55];

%finding the treshold number for each percentage
thresholds = percentages * n;

%collecting the data for 1000 iterations 
number_exceed = zeros( 1,length(percentages));
for i = 1:1000
    random_variable = normrnd(mu, sigma, n, 1);
    number_in_range = sum(random_variable >= 170 & random_variable <= 180);
    number_exceed = number_exceed + (number_in_range >= thresholds);
end
probability_exceed = number_exceed / 1000;

%printing the results
for i = 1:length(probability_exceed)
    fprintf('Average for %.0f%%: %.3f\n',percentages(i)*100,probability_exceed(i));
end
