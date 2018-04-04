#include <iostream>
#include <cstdlib>

#include "Cell.h"

using std::endl;
using std::cerr;

namespace ConnectFourGame{

	void Cell::setCell(int cell_row, int cell_col, char cell_value ){

		col = cell_col;
		row = cell_row ;
		chrCol = char(col + 'a') ;

		if ( cell_value == 'O' || cell_value == 'X' || cell_value == '.' )
		{
			value = cell_value;
		}
		else
		{
			cerr<<"Invalid character value"<<endl;
			exit(1);

		}	

	}

	void Cell::setValue( char position )
	{	
		value = position ;	
	}

}	