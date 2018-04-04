#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace ConnectFourGame{

	class ConnectFourPlus : public ConnectFourAbstract{

	public:
		ConnectFourPlus();
		ConnectFourPlus( int boardHeight, int boardWidth );

		int play( char cellPosition );

		// board un dikey line larında bir dortlu arar
		// ve bulursa 1 return eder aksi halde 0 return eder
		int vertical_check() ;	 		// Dikey dotlu tarama yapar	

		// Board un tum yatay line larini tarar ve bir dortlu arar , 
		// eger bulursa 1 return eder aksi halde 0 return eder
		int horizontal_check() ;		// Yatay dortlu tarama yapar
		
		void commands( char str[] );

		// Horizontan vertical ya da diagonal fonksiyonlarindan
		// biri tarafından return edilen degerlerin kontrolunu
		// yapar ve kazanan varsa true dondurur 		 
		//  ayrica yasayan objelerin sayisi board un max hucre sayisina esitse
		// yani kazanan yoksa true dondurur yani oyunun bitisini soyler
		// Aksi hallerde false return eder
		bool theGameEnd();

	};


} // ConnectFourGame

#endif // CONNECTFOURPLUS_H
