all:	Connect4

Connect4:	Connect4.o
	g++ Connect4.o -o exe

Connect4.o:	Connect4.cpp
	g++ -c Connect4.cpp

clean:
	rm *.o exe

run: 
	./exe
