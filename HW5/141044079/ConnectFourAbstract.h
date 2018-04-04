#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include "Cell.h"

namespace ConnectFourGame{

	class ConnectFourAbstract{

	public:
		ConnectFourAbstract();
		ConnectFourAbstract( int vectorHeight );
		ConnectFourAbstract( int vectorHeight, int vectorWidth );
		
		// COPY CONSTRUCTOR 
		ConnectFourAbstract( const ConnectFourAbstract& rightSide );

		void Games( const ConnectFourAbstract & theGame, char modChoice );


		void set_choice( char oneChoice );
		char get_choice() const {	return choice;  }
		void set_mod( char gameMod );

		int get_three(){	return three;  }

		int playGame_S();

		int read_file() ;

		int getHeight() const ;
		int getWidth() const;

		char get_mod(){		return mod;    }
		void print_board() const ;
		void initial_board(); // Non Const

		static void set_count_liveCells( int liveCells)
		{
			count_liveCells = liveCells;
		}

		static int get_countLiveCells(){    return count_liveCells;   }

		~ ConnectFourAbstract();

	protected:

		int height ;	 // Board boyu
		int width ;		 // Board eni

		static int count_liveCells ;

		char file[15] ; // file length max 15
		char turn ;
		int NewTotal ;
		char choice ;

		// X , O gibi hucre degerlerini tutar
		// setValue() fonksiyonuna verilir gerektiginde Cell sinifinin 
		// private value degikenine atama yapilirken kullanilir
		char target ;

		char mod ;
		char firstValue ;
		int three=0 ;

		void set_three(int value);

		void set_Height( int gameHeight );
		void set_Width( int gameWidth ) ;

		void set_firstValue( char  first );
		char get_firstValue(){    return firstValue ;    }

		void set_file( char fileName[] );
		char* get_file(){    return file;   }

		void set_turn( char playTurn );
		char get_turn() { return turn; }
		void set_NewTotal();
		int get_NewTotal() { return NewTotal; } 
		
		void set_target( char targetValue );
		char get_target() {		return target;   }

		void test_Height_Width()const;

		// Bu fonksiyon digerinin aksine cell in pozisyonunu alir ve user in oynamasini saglar
		virtual int play( char cellPosition) = 0; 		// Non const


		// user - user (P) oyun tipinde kullanicidan bir string tipinde 
		// bir input alir ve bunun bir char mi (kolon degeri)
		// yoksa bir komutmu oldugunu kontrol eder
		// Eger bir column ise( a,c,d etc. ) bu degeri dondurur
		// LOAD komutu ise '/' karakterini dondurur 
		// SAVE komutu ise fill_file() fonksiyonunn cagirir
		// ve tum verilerin dosyaya kaydedilmesini saglar
		char getUserValue( );

		virtual void commands( char str[] ) = 0;


		int StyleOfPlay( );

		virtual bool theGameEnd() = 0 ;

		// Assignment operator
		ConnectFourAbstract& operator =( const ConnectFourAbstract& rightSide );

		int received( int selection );

		// Cell in musait olup olmadigini return eder
		bool isEmpty( int i, int input) ;

		// Karakteri integer a cevirir
		int  charTo_int(char user ) ;


		// play fonksiyonu parametresiz calisir ve bilgisayarin oynamasini saglar
		int play();

		// Computer a karsi oynanan oyunlarda
		// rastgele input ureten bir fonksiyondur
		char  get_input(int arr_size );

		// get_input fonksiyonunun urettigi ilk degerin kendisi  veya
		// sag ya da sol hucresindeki kolon icin bir rastgele input uretir
		char get_near_input(char first );

		// SAVE komutu alindiğinda  verilen dosyanin icini o anki oyunun 
		// tüm board icerigi, size bilgileri oyun turu, oyun oynama
		// sirasi gibi bilgiler ile doldurur
		void fill_file() ;

		// Dinamic Two-dimensional Cell Array
		Cell ** gameBoard;

	};




} // ConnectFourGame

#endif // CONNECTFOURABSTRACT_H