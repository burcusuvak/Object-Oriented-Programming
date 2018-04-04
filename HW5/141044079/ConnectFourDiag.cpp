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

#include "ConnectFourDiag.h"

namespace ConnectFourGame{

	ConnectFourDiag::ConnectFourDiag()
						: ConnectFourAbstract()
	{	
		// deliberately empty	
	}			

	ConnectFourDiag::ConnectFourDiag( int boardHeight, int boardWidth )
						: ConnectFourAbstract(boardHeight, boardWidth)
	{	
		// deliberately empty	
	}	

	int ConnectFourDiag::play( char cellPosition )
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

			//cellPosition = getUserValue( );	
			GoBack = cellPosition ;

			if ( GoBack == '/' ) 		//   '/' karakteri rastgele secilmistir	
				return 1 ;
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

	void ConnectFourDiag::commands( char str[] ){
				
		if( ! strcmp ( str, "SAVE" ) )				
			fill_file() ;
	}	

	int ConnectFourDiag::diagonal_check(){
		
		char str_U[]= "XXXX" ;
		char str_C[]= "OOOO"  ;

		char string_temp[str_length];
		int winner=0;
		int temp_row = 0, last_row = 0, temp_col = 0, last_col = 0 ;

		if( getHeight() < getWidth() )
		{
			string str_line;
			for (int j = 0; j <= getWidth() -7 ; ++j )
			{
				for( int i = 0, k = 0; i < getHeight() ; ++i, ++k )	
				{
					str_line += gameBoard[i][k+j].getValue();
				}	
				std::size_t pos = str_line.find("XXXX");
				std::size_t found = str_line.find("OOOO");

				if( pos != std::string::npos ){	
					/*for( int i = pos; i < pos + 4; ++i , ++j )
						gameBoard[i][j+1].setValue('x');
					*/	
					return 1;
				}	

				else if ( found != std::string::npos  )
				{
					/*for( int i = found ; i < found + 4; ++i , ++j )
						gameBoard[i][j].setValue('o');
					*/	
					return 2;			
				}

				else
				{	
					str_line.erase(str_line.begin(),str_line.end());
					winner = 0;
				}
			}
				
			for( int j = 0; j <= getWidth()-7; ++j )	
			{
				for( int i = getHeight()-1, k = 0; i >=0 ; --i, ++k )				
					str_line += gameBoard[i][k+j].getValue();
				
				std::size_t pos = str_line.find("XXXX");
				std::size_t found = str_line.find("OOOO");

				if( pos != std::string::npos ){	
					/*for( int i = pos; i < pos + 4; ++i , ++j )
						gameBoard[i][j+1].setValue('x');
					*/	
					return 1;
				}	

				else if ( found != std::string::npos  )
				{
					/*for( int i = found ; i < found + 4; ++i , ++j )
						gameBoard[i][j].setValue('o');
					*/	
					return 2;			
				}

				else
				{	
					str_line.erase(str_line.begin(),str_line.end());
					winner = 0;
				}			
			}
		}

		else
		{	
			for( int j= getWidth() - 4, count=0; j > 0 && count < getWidth() - 3; -- j, ++count )
			{	
				int i=0, temp=0, sayac = 0 ;
				while( sayac <= count )
				{
					for( int  k=0; k<4 ; ++k )
					{	
						string_temp[k] = gameBoard[ i + sayac ][ j + sayac].getValue() ;
						++i;
						++j;
						temp=k;			
					}
					i -= 4;
					j -= 4;
					++sayac;
					string_temp[ temp+1 ] =  '\0' ;
					// dortlunun harflerini kucultmek icin									
					temp_row= i + sayac - 1 ;
					last_row = temp_row + 4 ;
					temp_col = j + sayac - 1 ;
					last_col= temp_col + 4 ;
					
					if( strcmp( str_U , string_temp ) == 0  )
					{		
						for( int r = temp_row, c = temp_col ; r < last_row , c < last_col ; ++  r , ++c )
							gameBoard[ r ][ c ].setValue('x');
						
						return 1 ;				
					}	
					else if(  strcmp( str_C , string_temp ) == 0  )
					{					
						for( int r = temp_row, c = temp_col ; r < last_row , c < last_col ; ++  r , ++c )
							gameBoard[ r ][ c ].setValue('o') ;
							
						return 2;
					}	
					else
						winner = 0;
				}		
			}
			
			for( int i = getHeight() - 4, count=0; i >=0 && count <= getHeight() - 3; --i, ++count )
			{
				int j=0 ,temp=0 , sayac = 0;
				while( sayac <= count )
				{
					for( int  k=0; k<4 ; ++k )
					{
						string_temp[k] = gameBoard[ i + sayac ][ j + sayac].getValue() ;
						++i;
						++j;
						temp=k;			
					}
					i -= 4;
					j -= 4;
					++sayac;
					string_temp[ temp+1 ] =  '\0' ;

					if( strcmp( str_U , string_temp ) == 0  )
					{	
						temp_row= i + sayac -1 ;
						last_row = temp_row + 4 ;
						temp_col = j + sayac -1;
						last_col= temp_col + 4 ;
						
						for( int r = temp_row, c = temp_col;  r < last_row, c < last_col; ++ r, ++ c )
							gameBoard[ r ][ c ].setValue('x') ;
						return 1 ;
						
					}
					else if(  strcmp( str_C , string_temp ) == 0  )
					{
						temp_row= i + sayac -1 ;
						last_row = temp_row + 4 ;
						temp_col = j + sayac -1;
						last_col= temp_col + 4 ;
						
						for( int r = temp_row, c = temp_col;  r < last_row, c < last_col; ++ r, ++ c )
							gameBoard[ r ][ c ].setValue('o') ;
						
						return 2;
						
					}	
					else
						winner = 0;
				}	
			}
				
			for( int j = getWidth() - 4 , count = 0 ; j > 0 && count < getWidth() - 3 ; -- j , ++count )
			{
				int i = getHeight() - 1 , temp=0, sayac = 0;
				while( sayac <= count )
				{
					for( int  k=0; k<4 ; ++k )
					{	
						string_temp[k] = gameBoard[ i - sayac ][ j + sayac].getValue() ;
							-- i;
							++j;
							temp=k;
					}			
					i +=4;
					j  -=4;
					++sayac;
					string_temp[ temp+1 ] =  '\0' ;
					

					if( strcmp( str_U , string_temp ) == 0  )
					{	
						temp_row= i - sayac + 1;
						last_row = temp_row - 4 ;
						temp_col = j + sayac - 1 ;
						last_col= temp_col + 4 ;
						
						for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
							gameBoard[ r ][ c ].setValue('x') ;
						return 1 ;
						
					}	
					else if(  strcmp( str_C , string_temp ) == 0  )
					{	
						temp_row= i - sayac + 1;
						last_row = temp_row - 4 ;
						temp_col = j + sayac - 1 ;
						last_col= temp_col + 4 ;
						
						for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
							gameBoard[ r ][ c ].setValue('o') ;
						return 2;
						
					}	
					else
						winner = 0;
				}	
			}
			
			for( int i = diagonal, count=0; i < getHeight() && count <= getHeight() - 3 ; ++i, ++count )
			{	
				int j=0, temp=0, sayac=0;
				while( sayac <= count )
				{	
					for( int  k=0; k<4 ; ++k )
					{	
						string_temp[k] = gameBoard[ i - sayac ][ j + sayac].getValue();
						-- i;
						++ j;
						temp=k;
					}			
					i+=4;
					j -=4;
					++sayac;
					string_temp[ temp+1 ] =  '\0' ;

					if( strcmp( str_U , string_temp ) == 0  )
					{	
						temp_row= i - sayac + 1;
						last_row = temp_row - 4 ;
						temp_col = j + sayac - 1 ;
						last_col= temp_col + 4 ;
						
						for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
							gameBoard[ r ][ c ].setValue('x') ;
						return 1 ;
					}	
					else if(  strcmp( str_C , string_temp ) == 0  )
					{
						temp_row= i - sayac  + 1;
						last_row = temp_row - 4 ;
						temp_col = j + sayac - 1 ;
						last_col= temp_col + 4 ;
						for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
							gameBoard[ r ][ c ].setValue('o') ;
						
						return 2;
						
					}	
					else
						winner = 0;		
				}
			}
		}
		return winner;	
	}


	bool ConnectFourDiag::theGameEnd(){

		int win_test3 ;

		char str_C[]= "OOOO" ;
		char str_U[]= "XXXX" ;

		win_test3 = diagonal_check();		// capraz dortluleri arar

		if ( win_test3 == 1 )
		{	
			if( get_choice() == 'P' )
				cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
			if( get_choice() == 'C' )
				cout<<"\n	THE PLAYER WON !		\n"<<endl;

			return true;
		}
			
		else if ( win_test3 == 2 )
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