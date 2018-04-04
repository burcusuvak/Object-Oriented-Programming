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

#include "ConnectFourAbstract.h"

namespace ConnectFourGame{

	ConnectFourAbstract::ConnectFourAbstract()
				: height(4), width(4)
	{ }

	ConnectFourAbstract::ConnectFourAbstract( int boardHeight )
					: width(8)
	{
		if(	boardHeight < 4 )
			exit(1);

	}

	ConnectFourAbstract::ConnectFourAbstract(int boardHeight, int boardWidth )					
											: 	height(boardHeight), width(boardWidth)
	{

		test_Height_Width();

	}

	ConnectFourAbstract::ConnectFourAbstract( const ConnectFourAbstract& rightSide )
					: height( rightSide.height), width( rightSide.width )
	{
		gameBoard = new Cell* [height];

		for (int i = 0; i < height; ++i)
		{
			gameBoard[i] = new Cell[width];

		}

	}

	void ConnectFourAbstract::set_choice( char oneChoice ){
		choice = oneChoice ;
	}


	int  ConnectFourAbstract::playGame_S(){	
	
		int total = getHeight() * getWidth() ;
		set_turn('1');
		int result = 0;
		
		print_board();

		result = StyleOfPlay( );

		if ( result == 1 )
		{
			return 1;
		}
		else if( result == 2 )
			return 2;
	 	else
	 		return 0;
	}

	int ConnectFourAbstract::read_file()
	{	
		ifstream fin ;
		string str, str0, str1, str2, str3 ,str4, str_ALPHBT ;
		char gameKind;
		char new_chr;
		int h, w , gameTotal, gameCount;
		char turnGame;

		fin.open( get_file() );

		if ( fin.fail( ) )
		{
			cerr<< "The file opening failed.\n" ;
			fin.clear();
			exit( 1 ) ;
		}

		fin >>str;
		fin >> h;
		set_Height(h);

		fin >>str0 ;
		fin >>w;
		set_Width(w);

		fin >> str1 ;
		fin >> turnGame ;
		set_turn(turnGame);

		fin >> str2 ;
		fin >> gameKind ;
		set_choice(gameKind);
		
		fin >> str3 ;
		fin >> gameCount ;
		set_count_liveCells(gameCount);

		fin >> str4 ;
		fin >> gameTotal ;
		set_NewTotal();


		fin >> str_ALPHBT ;

		initial_board();

		for ( int i = 0; i < height ; ++i )
		{
			for ( int j = 0; j <  width ; ++j )
			{
				fin >> new_chr ;
				
				gameBoard[i][j].setValue( new_chr ) ;
			}
		}

		fin.close() ;
		
		return 0 ;

	}

	int ConnectFourAbstract::getHeight() const {
		return height;
	}

	int ConnectFourAbstract::getWidth() const {
	 	return width;
	}

	void ConnectFourAbstract::print_board( )const
	{	
		cout << endl ;

		for (int i = 0; i < 1; ++i)
			for (int j = 0; j < width; ++j)
				 cout << gameBoard[i][j].get_chrCol() << " ";
		
		cout << endl ;	

		for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j)
				 cout << gameBoard[i][j].getValue() << " ";
			cout << endl ;	
		}

	}

	void ConnectFourAbstract::initial_board()
	{	

		gameBoard = new Cell*[height] ;

		for (int i = 0; i < height; ++i)
			gameBoard[i] = new Cell[width] ;

		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				gameBoard[i][j].setCell(i,j,'.');

	}

	void ConnectFourAbstract::set_three(int value){
		three = value;	
	}	

	void ConnectFourAbstract::set_Height( int gameHeight )
	{
		height = gameHeight ;
	}

	void ConnectFourAbstract::set_Width( int gameWidth )
	{
		width = gameWidth ;
	}
	void ConnectFourAbstract::set_firstValue( char  first )
	{
		firstValue = first ;
	}

	void ConnectFourAbstract::set_file( char fileName[]  )
	{
		strcpy( file, fileName );

	}

	void ConnectFourAbstract::set_turn( char playTurn )
	{
		if ( playTurn == '1' || playTurn == '2')
		{
			turn = playTurn ;

		}
		else
			exit(1);

	}

	void ConnectFourAbstract::set_NewTotal()
	{
		NewTotal = getHeight() *getWidth() ;

	}

	void ConnectFourAbstract::set_target( char targetValue )
	{
		target = targetValue ;
	}

	void ConnectFourAbstract::test_Height_Width()const
	{
		if ( height < 4 )
		{
			cerr<<"Invalid height value"<<endl;
			exit(1);
		}

		if ( width < 4 || width > MaxSize )
		{
			cerr<<"Invalid width value"<<endl;
			exit(1);
		}
		
	}


	char ConnectFourAbstract::getUserValue( )
	{	
		char value ;	
		string str ;
		char nextStr[10] ;
		char nextStr2[10] ;
		int control = 0 ;
		int size = 0 ;
		while(control != 1 )
		{	
			getline(cin, str );

			if ( cin.eof() )
				exit(1);

			int temp=0;

			if( str.length() == 1 ){
				control = 1 ;
				value=str[0];
				if( isupper( value ) )
					return tolower( value );

				return value;
			}
			if( str.length() > 1 )
			{	int x=0;
				for( int i=0 ; str[ i ] != ' ' && x < 4 ; ++i, ++x ){
					nextStr[i]=str[i];
					temp=i;
				}

				nextStr[temp+1]='\0';

				if(  strcmp ( nextStr, "UNDO" ) != 0 ){	
					int d=temp+2;
					int j=0;
					temp=0;
					for( int i=d ; str[ i ] != '\0'; ++i ){
						temp=0;
						nextStr2[j]=str[i];
						++j;
						temp = j ;
					
					}
					nextStr2[temp]='\0';
					set_file( nextStr2 ) ;
				}			

				commands( nextStr );

				if( !strcmp ( nextStr, "UNDO" ) )
					return '#';

				if( ! strcmp ( nextStr, "LOAD" ) )			
					return '/' ;
				
					
			}
		}
	}

	int ConnectFourAbstract::StyleOfPlay( )
	{	
		int win_test = 0, win_test2=0, win_test3=0 ;
		int row=0, count=0;
		int four = 4;
		int total = getHeight() * getWidth() ;
		const int max_index = getHeight() - 1;
		int  GoBack = 1  ;
		int complete = 0 ;

		set_NewTotal();

		if( get_choice() == 'C' )
		{
			char  value;
			char oneValue = get_input( max_index + 1 );
			set_firstValue( oneValue ) ;

			while( theGameEnd() != 1 )
			{
				if (  complete != 1  && get_turn() == '1'  )
				{
					set_target('X');
					cout << "PLAYER : ";
					GoBack = received( 2 );
					if ( GoBack ==  1 )
						return GoBack ;
				
					
					++ count_liveCells ;
					cout<<"count_liveCells:  "<<count_liveCells<<endl;

					print_board() ;

					turn = '1' ;

					if( theGameEnd() )
					{
						cout<<endl;		
						print_board() ;		
						complete = 1 ;		
						return 0;
					}
				}
				set_turn ('2');			
				
				if ( complete != 1  && get_turn() == '2'  )
				{		
					set_target('O');
					GoBack = received( 1 );
					if ( GoBack ==  1 )
						return GoBack ;
						
					++ count_liveCells ;
					cout<<endl;		

					print_board();
					
					turn = '2' ;	
				
					if( theGameEnd() )
					{
						cout<<endl;		
						print_board();		
						complete = 1 ;	
						return 0;
					}
					set_turn ('1') ;
				}	

				if ( theGameEnd() )			
					complete = 1 ;	

			}
			
		}


		if ( get_choice() == 'P' )
		{	
			while( theGameEnd() != 1 )
			{	
				if (  complete != 1  && get_turn() == '1'  )
				{	
					set_target('X');
					cout << "\nPLAYER 1: ";				
					GoBack = received( 2 );

					if ( GoBack == 1 )
						return GoBack ;				
					
					++ count_liveCells ;

					cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

					print_board();
			
					if ( theGameEnd() )
					{
						print_board();
						complete = 1 ;
						return 0;	
					}

				}	
				set_turn('2') ;	
				if ( complete != 1  && get_turn() == '2'  )
				{	
					set_target('O');
					cout << "\nPLAYER 2: ";
					GoBack = received( 2 );

					if ( GoBack == 1 )
						return GoBack ;
				
					++count_liveCells ;

					cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

					cout<<endl;
					print_board();
					
					if ( theGameEnd() )
					{
						print_board();
						complete = 1 ;
						return 0;					
					}
					set_turn ('1') ;
				}		
			
						
			}	
			if ( theGameEnd() )			
				complete = 1 ;
		}

		return 0;

	}

	
	int ConnectFourAbstract::received( int selection )
	{	
		bool legal= false;
		char GoBack ;
		char value;
		char nearValue;
		int RoWsize = getHeight() - 1 ;
		bool control { false };

		if( selection == 1 )
			play() ;

		if( selection ==2 )
		{
			value = getUserValue();	
			GoBack = play( value ) ;
			if ( GoBack ==  1 )
				return GoBack ;

		}	
	}

	bool ConnectFourAbstract::isEmpty( int i, int input){
		bool empty;

		if( gameBoard[i][input].getValue() == '.' )
			empty= true ;
		else
			empty= false;

		return empty;
	}	

	int ConnectFourAbstract::charTo_int(char user ){
		
		int int_val;		
		int_val = int(user) - 'a';		// char in integer a donusturulmus degeri
		return int_val;
	}	

	int ConnectFourAbstract::play()
	{	
		int row;
		int lastValue ;
		char value;
		char nearValue;

		char GoBack ;
		int RoWsize = getHeight() - 1 ;
		int max_index = getWidth() - 1 ;
		bool control { false };
		bool legal = false;

		while(  control != true )
		{	
			RoWsize = getHeight() - 1 ;
			if( row == 0 )
			{	
				lastValue = charTo_int( get_firstValue() );
				++ row;
			}
			if( row != 0 )
			{	
				nearValue = get_near_input( lastValue );
				lastValue = charTo_int( nearValue );
			
				if(  lastValue < 0 || lastValue > max_index || isdigit( nearValue )  )
				{
					while( lastValue < 0 || lastValue > max_index  )
					{			
						nearValue = get_near_input( nearValue );
						lastValue= charTo_int( nearValue );
					}
				}

				while( legal != true && RoWsize >= 0)
				{	
					legal= isEmpty( RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;

				if( legal == true )
					gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
				else
				{	char k= nearValue;	
					while( k== nearValue || lastValue < 0 || lastValue > max_index )
					{
						nearValue = get_near_input( nearValue );
						lastValue= charTo_int( nearValue );

					}

					legal = false ;
					RoWsize = getHeight() -1;

					while( legal != true && RoWsize >= 0)
					{	
						legal= isEmpty( RoWsize, lastValue );
						--RoWsize;
					}
					control = legal;

					if( legal == true )
						gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
				}
			}
		}

		return 0 ;
	}

	char  ConnectFourAbstract::get_input(int arr_size ){
		char value;
		int c_input=0;
		c_input= 1+ rand() % ( arr_size - 2 );

		value = char(c_input+ 'a' );
		return value;

	}

	char ConnectFourAbstract::get_near_input(char first ){
		char str[ str_size ];
		int get=0;

		str[0] = first - 1;
		str[1] = first;
		str[2] = first + 1;
		get = rand() % 3;
		
		return  str[get];
	}	

	void ConnectFourAbstract::fill_file()
	{
		ofstream fout;

		fout.open( get_file() , ios :: out | ios :: in | ios :: trunc );

		if ( fout.fail( ) )
		{
			cerr<< "The file opening failed.\n" ;
			fout.clear();
			exit( 1 ) ;
		}

		fout << "BOY " << getHeight()  << endl ;
		fout << "EN "  << getWidth()   << endl ;
		fout << "OYUN_SIRA "  << get_turn()           << endl ;
		fout << "OYUN_SEKLI " << get_choice()         << endl ;
		fout << "COUNT "      << get_countLiveCells() << endl ;
		fout << "TOTAL "      << get_NewTotal()       << endl ;
		
		char chr= 'a' ;
		
		for(int i=0, j=0; i < getWidth() ; ++i, ++j)
			fout<<char(chr+j) ;

		fout<<endl;
		
		for ( int i = 0; i < height ; ++i )
		{
			for ( int j = 0; j <  width ; ++j )
			{
				fout << gameBoard[i][j].getValue();
			}

			fout<<endl;
		}

		fout.clear();
		fout.close() ;

	}

	void ConnectFourAbstract::set_mod( char gameMod )
	{	mod = gameMod;	}

	void ConnectFourAbstract::Games( const ConnectFourAbstract & theGame , char modChoice ){

		int result = 0 ;
		cout<<"burcu\n";

		set_mod( modChoice);
		char gameChoice;
		do{
			cout<<"\nPlayer | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );

		initial_board();
		set_choice( gameChoice ) ;

		initial_board();

		result = playGame_S();

		while( result == 1 )
		{	
			read_file();
			result = playGame_S();
		}
	}

	ConnectFourAbstract& ConnectFourAbstract::operator =( const ConnectFourAbstract& rightSide ){

		if ( this == &rightSide ){
			return *this;
		}
		else{

			set_Height( rightSide.height );
			set_Width( rightSide.width );
			turn = rightSide.turn;
			choice = rightSide.choice;
			strcpy(file,rightSide.file);
			count_liveCells = rightSide.count_liveCells;
			target = rightSide.target;
			mod = rightSide.mod;
			firstValue = rightSide.firstValue;
			three = rightSide.three;
			NewTotal = rightSide.NewTotal;

			for (int i = 0; i < height; ++i)
			{
				delete [] gameBoard[i];
			}

			delete [] gameBoard;

			gameBoard = new Cell*[height];

			for (int i = 0; i < height; ++i)
			{
				gameBoard[i] = new Cell[width];
			}

			for (int i = 0; i < height; ++i)		
				for (int j = 0; j < width; ++j)
					gameBoard[i][j] = rightSide.gameBoard[i][j];

			return *this;
		}

	}



	ConnectFourAbstract::~ConnectFourAbstract(){

		for( int i=0; i < height; ++i )
			delete [] gameBoard[i];

		delete [] gameBoard;

		gameBoard = nullptr;


	}

}


	