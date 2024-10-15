D_1910=csvread("./sea_surface_temperature/1910/10.csv")
data_fil=(D_1910 < 1e9).*D_1910
imagesc(data_fil)
colorbar
colormap(jet)