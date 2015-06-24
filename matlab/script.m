arg = argv;
V0 = str2num(arg{1});
angle = str2num(arg{2});
G = 9.8;
t = 2*(V0/G)*sind(angle);
t = linspace(0,t,t*100);
x = [];
y = [];

for i = 1:columns(t)
	x(end+1) = V0*cosd(angle)*t(i);
	y(end+1) = V0*sind(angle)*t(i) - (G/2)*t(i)^2;
endfor

disp("Y max:");
disp(max(y));
plot(x,y);
axis("image");
pause();
