all:	Connect4_2

Connect4_2:	Connect4_2.o
	g++  -std=c++11 Connect4_2.o -o exe

Connect4_2.o:	Connect4_2.cpp
	g++ -std=c++11 -c Connect4_2.cpp

clean:
	rm *.o exe

run: 
	./exe
