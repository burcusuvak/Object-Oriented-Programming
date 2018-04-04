#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"

namespace ConnectFourGame{


	class ConnectFourPlusUndo : public ConnectFourPlus
	{
	public:
		ConnectFourPlusUndo();

		ConnectFourPlusUndo( int boardHeight, int boardWidth );

		ConnectFourPlusUndo( const ConnectFourPlusUndo& rightSide );

		ConnectFourPlusUndo& operator =( const ConnectFourPlusUndo& rightSide );

		int play( char cellPosition );

		void commands( char str[] );

		void fillArray_Row_Col( int _rowVal, int _colVal );

		void removeTheCell();

		void backupArray_Row_Col( );

		~ConnectFourPlusUndo();

	private:
		int used;
		int capacity;
		int * rowArr;
		int * colArr;

		
	};

}


#endif 