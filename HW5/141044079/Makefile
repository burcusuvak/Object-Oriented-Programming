all:  HW5_141044079_BurcuSuvakOzturk

HW5_141044079_BurcuSuvakOzturk:	HW5_141044079_BurcuSuvakOzturk.o
	g++  -std=c++11 Cell.cpp ConnectFourAbstract.cpp ConnectFourDiag.cpp ConnectFourPlus.cpp ConnectFourPlusUndo.cpp HW5_141044079_BurcuSuvakOzturk.o -o exe

HW5_141044079_BurcuSuvakOzturk.o:	HW5_141044079_BurcuSuvakOzturk.cpp
	g++ -std=c++11 -c HW5_141044079_BurcuSuvakOzturk.cpp
	

clean:
	rm *.o exe

run: 
	./exe
