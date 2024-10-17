north=csvread('/Users/chenzhiting/Desktop/cse_primer/Wendesday/north_matrix (1).csv')
south=csvread('/Users/chenzhiting/Desktop/cse_primer/Wendesday/south_matrix (1).csv')

v=VideoWriter('/Users/chenzhiting/Desktop/cse_primer/Wendesday/yearly_change')
v.FrameRate=5
open(v)
for (k=1:170)
    clf
    first=north(k,:)
    second=south(k,:)

    month=1:12
    h1=plot(month,first,'r', 'LineWidth',2)
    hold on 
    h2=plot(month,second, 'b','LineWidth',2)
    hold off
    legend('North', 'South', 'FontSize', 12)
    text_handle = text(8, 5*10^7, ['Year: ', num2str(k+1849)], 'FontSize', 20, 'Color', 'black', 'FontWeight', 'bold');
    axis([0 12 1*10^7 8*10^7])
    title('Sea ice area changing from 1850-2019','FontSize', 20);
    xlabel('Month','FontSize', 16);
    ylabel('Area (km^2)','FontSize', 16);
    grid on
    frame=getframe(gcf)
    writeVideo(v,frame)
    pause(0.08)
end
close(v)