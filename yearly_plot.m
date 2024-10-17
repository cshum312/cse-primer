north=csvread('/Users/chenzhiting/Desktop/cse_primer/Wendesday/north_matrix (1).csv')
south=csvread('/Users/chenzhiting/Desktop/cse_primer/Wendesday/south_matrix (1).csv')

N=mean(north,2)
S=mean(south,2)
year=1850:2019
h1=plot(year,N,'r','LineWidth',2)
hold on
h2=plot(year,S,'b','LineWidth',2)
hold off
grid on
title('Sea ice area changing from 1850-2019','FontSize', 20);
xlabel('Year','FontSize', 16);
ylabel('Area (km^2)','FontSize', 16);
saveas(gcf,'/Users/chenzhiting/Desktop/cse_primer/Wendesday/yearly.png')