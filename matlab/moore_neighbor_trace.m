#Example for Moore-Neighbor Tracing in octave
#Source: http://www.imageprocessingplace.com/downloads_V3/root_downloads/tutorials/contour_tracing_Abeer_George_Ghuneim/moore.html

#  columns
# r1111111
# o1111111
# w1111111
# s1111111

# Make matrices
a = zeros(16,10);
b = ones(8,8);

# Determine diference in size
sx = (columns(a)-columns(b))/2;
sy = (rows(a)-rows(b))/2;

# Insert b into center of a
for y = 1:rows(b)
	for x = 1:columns(b)
		a(round(y+sy),round(x+sx)) = b(y,x);
	endfor
endfor

# Display starting image
disp("Staring image:");
disp(a);

# Look for starting point
flag = 1;
start_x = 0;
start_y = 0;
for x = 1:columns(a)
	if(flag)
		for y = rows(a):-1:1
			if (a(y,x) == 1)
				a(y,x) = 3;
				start_x = x;
				start_y = y;
				flag = 0;
				break;
			endif
		endfor
	endif
endfor

# Display starting image with starting point
disp("Staring image with starting point (3):");
disp(a);

current_x = start_x;
current_y = start_y;

# Defie positions of neighbors, 1 - x, 2 - y
p1 = [-1,-1];
p2 = [ 0,-1];
p3 = [+1,-1];
p4 = [+1, 0];
p5 = [+1,+1];
p6 = [ 0,+1];
p7 = [-1,+1];
p8 = [-1, 0];
p = [p1,p2,p3,p4,p5,p6,p7,p8,p1,p2,p3,p4,p5,p6,p7,p8];
last = 6;

# Tracing image
while(1)
	for i = 1:8
		pos_x = p((last+i)*2-1);
		pos_y = p((last+i)*2);
		switch a(current_y+pos_y,current_x+pos_x)
			case 1
				current_y = current_y+pos_y;
				current_x = current_x+pos_x;
				a(current_y,current_x) = 2;
				last = mod(last+i+4,9)+1;
				break;
			case 3
				a(current_y+pos_y,current_x+pos_x) = 2;
				disp("Finished trace (2):");
				disp(a);
				return;
		endswitch
	endfor
endwhile

