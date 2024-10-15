aug_path = "./sea_surface_temperature/";

% extract all yearly folder names for iteration
files = dir(aug_path);
idx = [files.isdir];
get_dir = {files(idx).name};

% extract all august data
for k = 3:length(get_dir)
    F = fullfile(aug_path, get_dir(k), "8.csv");
    aug_S(k).data = readmatrix(F);
end

% calculate all august spatial means for polar circle
polar_mean = [];
for k = 3:length(get_dir)
    polar = [aug_S(k).data(1:24, :); aug_S(k).data(156:180, :)];
    polar = (polar < 1e9).*polar;
    curr_mean = mean(polar, "all");
    polar_mean = [polar_mean, curr_mean];
end

% plot
f = figure(1);
f.Position = [100 100 1000 800];
x = 1850:1:2019;
Y = polar_mean;
plot(x, Y);
title("Evolution of Polar Circle Temperatures in August")
xlabel("Year")
ylabel("Temperature (°C)")
