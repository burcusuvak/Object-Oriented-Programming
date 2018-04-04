#include <iostream>

#include "ConnectFourAbstract.h"

#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;

using ConnectFourGame::ConnectFourPlus;
using ConnectFourGame::ConnectFourDiag;
using ConnectFourGame::ConnectFourPlusUndo;
using ConnectFourGame::ConnectFourAbstract;

int ConnectFourAbstract::count_liveCells = 0 ;


int main(){
	
	int boardHeight , boardWidth ;
	int result = 0 ;

	char modChoice ;
	srand(time(NULL));

	cout<< "  ...  WELCOME TO CONNECT4 ...   "<<endl<<endl ;

	cout << "P : Mod for VERTICAL and HORIZONTAL Checks \n"
		 << "D : Mod for only DIAGONAL Check \n"
		 << "U : Mod for UNDO \n"
		 << "Please enter your choice: " ;
	cin	 >>	 modChoice;

	cout<<"Enter Height: ";
	cin>> boardHeight ;

	cout<<"Enter Width: ";
	cin>> boardWidth ;

	char gameChoice;
	do{
		cout<<"\nPlayer | Computer : ";
		cin>>gameChoice;
		gameChoice=toupper( gameChoice );

	}while( gameChoice != 'P' && gameChoice != 'C' );
	
	ConnectFourAbstract * game;

	if( modChoice == 'P' || modChoice == 'p' ){

		ConnectFourPlus plusModGame( boardHeight, boardWidth );
		plusModGame.set_mod( modChoice );

		plusModGame.set_choice( gameChoice ) ;
		plusModGame.initial_board();

		result = plusModGame.playGame_S();

		while( result == 1 )
		{	
			plusModGame.read_file();
			result =  plusModGame.playGame_S();
		}


	}	
	if( modChoice == 'D' || modChoice == 'd' ){

		ConnectFourDiag diagModGame( boardHeight, boardWidth );
		diagModGame.set_mod( modChoice );

		diagModGame.set_choice( gameChoice ) ;
		diagModGame.initial_board();

		result = diagModGame.playGame_S();

		while( result == 1 )
		{	
			diagModGame.read_file();
			result =  diagModGame.playGame_S();
		}

	}

	if( modChoice == 'U' || modChoice == 'u' ){

		ConnectFourPlusUndo undoModGame( boardHeight, boardWidth );
		undoModGame.set_mod( modChoice );

		undoModGame.set_choice( gameChoice ) ;
		undoModGame.initial_board();

		result = undoModGame.playGame_S();

		while( result == 1 )
		{	
			undoModGame.read_file();
			result =  undoModGame.playGame_S();
		}

	}


	return 0;
}