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

#include "ConnectFourPlusUndo.h"

namespace ConnectFourGame{

	ConnectFourPlusUndo::ConnectFourPlusUndo()
					: ConnectFourPlus(), capacity(0), used(0)
	{	
		// deliberately empty	
	}							
	ConnectFourPlusUndo::ConnectFourPlusUndo( int boardHeight, int boardWidth )
					: ConnectFourPlus(boardHeight, boardWidth), capacity(100), used(0)
	{	
		rowArr = new int[ capacity ];
		colArr = new int[ capacity ];	
	}	

	ConnectFourPlusUndo::ConnectFourPlusUndo( const ConnectFourPlusUndo& rightSide )
							: used(rightSide.used), capacity(rightSide.capacity)
	{
		rowArr = new int[capacity];
		colArr = new int[capacity];
	}

	ConnectFourPlusUndo& ConnectFourPlusUndo::operator =( const ConnectFourPlusUndo& rightSide ){

		if ( this == &rightSide ){
			return *this;
		}
		else{

			used = rightSide.used;
			capacity = rightSide.capacity;

			delete [] rowArr;
			delete [] colArr;

			rowArr = new int[rightSide.capacity];
			colArr = new int[rightSide.capacity];

			for (int i = 0; i < rightSide.used; ++i)
			{
				rowArr[i] = rightSide.rowArr[i];
				colArr[i] = rightSide.colArr[i];
			}

		}

	}	


	void ConnectFourPlusUndo::fillArray_Row_Col( int _rowVal, int _colVal ){

		used = get_countLiveCells();
		rowArr[ used ] = _rowVal;
		colArr[ used ] = _colVal;
				
	}

	void ConnectFourPlusUndo::removeTheCell(){

		if( used >= 0 ){
			gameBoard[ rowArr[used] ][ colArr[used] ].setValue('.');
			if( count_liveCells > 0 )
				--count_liveCells;
			if( used != 0 )
				--used;
		}
	}

	/*void ConnectFourPlusUndo::backupArray_Row_Col( ){

		backRow = new int[ get_countLiveCells() ];
		backCol = new int[ get_countLiveCells() ];

		for (int i = 0; i < used; ++i)
		{
			backRow[used] = rowArr[used];
			backCol[used] = colArr[used];

		}

		for (int i = 0; i < used; ++i)
		{
			rowArr[used] = backRow[used];
			colArr[used] = backCol[used];

		}

	}
*/
	void ConnectFourPlusUndo::commands( char str[] ){

		if( ! strcmp ( str, "SAVE" ) )				
			fill_file() ;	
		if( ! strcmp ( str, "UNDO" ) ){
			removeTheCell();
			cout << "\n  GERI ALMA ISLEMI TAMAMLANDI ..." << endl;
			//backupArray_Row_Col();
			print_board();
		}
	}

	int ConnectFourPlusUndo::play( char cellPosition )
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
					//cout<<"INVALID VALUE Please Enter Again:	"<<endl;
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
				fillArray_Row_Col( RoWsize+1, lastValue );
			}
			else
			{	char k = cellPosition ;	
			
				while( k == cellPosition )
				{
					//cout<<"INVALID VALUE Please Enter Again:	"<<endl;
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
				if( legal == true ){
					gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
					fillArray_Row_Col( RoWsize+1, lastValue );

				}
				

			}
		}	
		return 0;
	}

	ConnectFourPlusUndo::~ConnectFourPlusUndo(){

		delete [] rowArr;
		delete [] colArr;

		rowArr = nullptr;
		colArr = nullptr;

	}


}	