make: main.o string.o
	g++ main.o string.o -o hw01string

main.o: main.cc
	g++ -c main.cc -o main.o

string.o: string.cc
	g++ -c string.cc -o string.o

clean:
	rm *.o
