D_1910=csvread("/Users/chenzhiting/Desktop/1910/10.csv")
data_fil=(D_1910 < 1e9)*D_1910
imagesc(data_fil)
colorbar
colormap(jet)