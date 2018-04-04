#ifndef CELL_H
#define CELL_H

namespace ConnectFourGame{

	class Cell
	{
	public:		
		void setCell(int col, int row, char value );
		void setValue( char position ) ;
		int getCol()  const { return col; }
		int getRow() const { return row; }
		char getValue() const { return value; }
		char get_chrCol() const {	return chrCol; }

	private:
		int col ;
		int row ;
		char chrCol ;
		char value ;
	};


} // ConnectFourGame

#endif // CELL_H
