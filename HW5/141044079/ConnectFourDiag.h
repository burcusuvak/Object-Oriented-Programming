#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace ConnectFourGame{

	class ConnectFourDiag : public ConnectFourAbstract{

	public:
		ConnectFourDiag();
		ConnectFourDiag( int boardHeight, int boardWidth );

		int play( char cellPosition );
	
		void commands( char str[] );


		// Dikey dortlu tarama yapar
		// board daki saga ya da sola dogru caprazlamasina 
		// tum line larda bir dotlu arar ve bulursa return olarak 1 dondurur	
		int diagonal_check() ;					 // Capraz line icin dortlu taramalari
		
		bool theGameEnd();


	};


} // ConnectFourGame

#endif // CONNECTFOURDIAG_H
