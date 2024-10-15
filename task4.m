temp_avg=zeros(1,12)
for (k=1:12)
    route_1950=sprintf("/Users/chenzhiting/Desktop/1850/%d.csv",k)
    route_2019=sprintf("/Users/chenzhiting/Desktop/2019/%d.csv",k)

    Data_1950_1=csvread(route_1950)
    Data_2019_1=csvread(route_2019)
    Data_1950_1=(Data_1950_1 < 1e4).*Data_1950_1
    Data_2019_1=(Data_2019_1 < 1e4).*Data_2019_1
    polar_1950_1=Data_1950_1([1:25,156:180],:)
    avg_polar_1950_1=mean(polar_1950_1(:))
    polar_2019_1=Data_2019_1([1:25,156:180],:)
    avg_polar_2019_1=mean(polar_2019_1(:))
    diff=abs(avg_polar_1950_1-avg_polar_2019_1)
    temp_avg(1,k)=diff
end

plot(temp_avg)
