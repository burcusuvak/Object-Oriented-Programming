#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <sstream>
#define MinSize 4					// board icin alinabilcek min boyut
#define MaxSize 26
#define connect4 4					// oyunda birada bulunmasi gereken tas sayisi ( yatay, dikey vaya capraz olarak )
#define str_length 5				// substringler icin tutulacak array in boyutu
#define diagonal 3
#define str_size 3					// capraz check icin en az 3. indisten baslanabilir
#define MaxSize 26

using namespace std;

#include "ConnectFourPlus.h"

namespace ConnectFourGame{

	ConnectFourPlus::ConnectFourPlus()
						: ConnectFourAbstract()
	{	
		// deliberately empty	
	}			

	ConnectFourPlus::ConnectFourPlus( int boardHeight, int boardWidth )
						: ConnectFourAbstract(boardHeight, boardWidth)
	{	
		// deliberately empty	
	}	

	int ConnectFourPlus::play( char cellPosition )
	{	
		int lastValue = 0 ;
		char GoBack ;
		int RoWsize = getHeight() - 1 ;
		int max_index = getWidth() - 1 ;
		bool control { false };
		bool legal = false;

		while(  control != true )
		{	
			RoWsize= getHeight() - 1 ;

			GoBack = cellPosition ;

			if ( GoBack == '/' ) 		//   '/' karakteri rastgele secilmistir	
				return 1 ;
			else if ( GoBack == '#' )
				return 1;
			else{	

				lastValue= charTo_int( cellPosition );
			}	

			if(  lastValue < 0 || lastValue > max_index || isdigit( cellPosition ) )
			{
				while( lastValue < 0 || lastValue > max_index  )
				{			
					cout<<"INVALID VALUE Please Enter Again:	"<<endl;
					cellPosition = getUserValue();
					lastValue= charTo_int( cellPosition );
				}
			}

			while( legal != true && RoWsize >= 0)
			{	
				legal= isEmpty( RoWsize, lastValue);
				--RoWsize;
			}
			control = legal;
			
			if( legal == true ){
				
				gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
			}
			else
			{	char k = cellPosition ;	
			
				while( k == cellPosition )
				{
					cout<<"INVALID VALUE Please Enter Again:	"<<endl;
					cin>> cellPosition ;
				}

				lastValue = charTo_int( cellPosition );

				legal = false ;
				RoWsize = getWidth() -1;
				while( legal != true && RoWsize >= 0)
				{		
					legal= isEmpty( RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;
				if( legal == true )
					gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
				

			}
		}	
		return 0;
	}

	int ConnectFourPlus::vertical_check(){

		char str_U[] = "XXXX" ;
		char str_C[] = "OOOO" ; 

		char string_temp[str_length];
		int winner=0, k;
		for( int j = 0; j < getWidth() ; ++j )
		{	
			for( int i = getHeight() - 1; i >= 3 ; -- i )
			{	
				k=0;
				while( k < 4 ){
					string_temp[k] =  gameBoard[i][j].getValue() ;
					-- i;
					++k;
				}
				i += 4;
				string_temp[ k ] =  '\0' ;
				
				int temp = i  , last_temp = temp - 4 ;

				if( strcmp( str_U , string_temp ) == 0  )
				{	
					for( int s = temp ; s > last_temp ; --s )
						gameBoard[s][j].setValue('x') ;
					return 1 ;
				}	
				else if(  strcmp( str_C , string_temp ) == 0  )
				{		
					for( int s = temp ; s > last_temp ; --s )
						gameBoard[s][j].setValue('o') ;
					return 2;				
				}	
				else
					winner = 0;
			}											
		}
		return winner;	
	}


	int ConnectFourPlus::horizontal_check(){	
		
		char str_U[]= "XXXX"  ;
		char str_C[] = "OOOO" ; 

		char string_temp[str_length] ;
		int winner = 0 ;
		int k ;
		int flag=0;
		for( int i = getHeight() - 1; i >= 0; --i )
		{
			for( int j = 0 ; j < (getWidth() - 3) ; ++j )
			{	
				k=0;
				while( k<4 ){
					string_temp[k] = gameBoard[i][j].getValue() ;
					++j;
					++k;
				}
				j -= 4;

				string_temp[ k ] =  '\0' ;
			

				int temp = j, last_temp = j + 4 ;
				
				if( strcmp( str_U , string_temp ) == 0  )
				{					
					for( int s = temp ; s < last_temp ; ++s )
						gameBoard[i][s].setValue('x') ;
						
					return 1 ;
				}	
				else if(  strcmp( str_C , string_temp ) == 0  )
				{
					for( int s = temp ; s < last_temp ; ++s )
						gameBoard[i][s].setValue('o') ;
						
					return 2;		
				}	
				else
					winner = 0;			
			}
		}
		return winner;
	}

	void ConnectFourPlus::commands( char str[] ){
				
		if( ! strcmp ( str, "SAVE" ) )				
			fill_file() ;
	}	


	bool ConnectFourPlus::theGameEnd(){

		int win_test, win_test2 ;

		char str_C[]= "OOOO" ;
		char str_U[]= "XXXX" ;

		win_test2 = vertical_check();		// Dikey line da dortlu arar
		win_test = horizontal_check();			// yatayda dortlu arar

		if ( win_test == 1 || win_test2 == 1 )
		{	
			if( get_choice() == 'P' )
				cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
			if( get_choice() == 'C' )
				cout<<"\n	THE PLAYER WON !		\n"<<endl;

			return true;
		}
			
		else if ( win_test == 2 || win_test2 == 2 )
		{	
			if( get_choice() == 'P' )
				cout<<"\n	THE PLAYER 2 WON !		\n"<<endl;
			if( get_choice() == 'C' )
				cout<<"\n	THE COMPUTER WON !		\n"<<endl;

			return true;
		}

		else if ( get_countLiveCells() ==  get_NewTotal() )			
				cout<<"\nGame Over... NO WINNER !!!"<<endl;
		else
			return false;

	}	




}