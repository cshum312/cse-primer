l850_path = "./sea_surface_temperature/1850/";
l019_path = "./sea_surface_temperature/2019/";

l850_S = dir(fullfile(l850_path, "*.csv"));
l019_S = dir(fullfile(l019_path, "*.csv"));

% extract data from 1850
% https://de.mathworks.com/matlabcentral/answers/2035849-loading-multiple-csv-files-using-readmatrix
for k = 1:numel(l850_S)
    F = fullfile(l850_path, l850_S(k).name);
    l850_S(k).data = readmatrix(F);
end

% extract data from 2019
for k = 1:numel(l019_S)
    F = fullfile(l019_path, l019_S(k).name);
    l019_S(k).data = readmatrix(F);
end

% calculate spatial means for polar circle data from 1850
l850_polar_mean = [];
for k = 1:12
    polar = [l850_S(k).data(1:24, :); l850_S(k).data(156:180, :)];
    polar = (polar < 1e9).*polar;
    curr_mean = mean(polar, "all");
    l850_polar_mean = [l850_polar_mean, curr_mean];
end

% calculate spatial means for polar circle data from 2019
l019_polar_mean = [];
for k = 1:12
    polar = [l019_S(k).data(1:24, :); l019_S(k).data(156:180, :)];
    polar = (polar < 1e9).*polar;
    curr_mean = mean(polar, "all");
    l019_polar_mean = [l019_polar_mean, curr_mean];
end

% calculate difference in spatial means per month
mean_diff = l019_polar_mean - l850_polar_mean;

% plot
f = figure(1);
f.Position = [100 100 1000 800];
% account for alphabetical order during extraction
x = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
Y = [mean_diff(1), mean_diff(5:12), mean_diff(2:4)];
bar(x, Y);
text(1:length(Y),Y,num2str(Y', 3),'vert','bottom','horiz','center'); 
title("1850 vs 2019 Polar Circle Temperature Difference")
xlabel("Month")
ylabel("Temperature (°C)")


