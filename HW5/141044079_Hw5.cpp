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

class ConnectFour
{
public:
	ConnectFour();
	ConnectFour( int vectorHeight );
	ConnectFour( int vectorHeight, int vectorWidth );
	
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


private:

	int height ;	 // Board boyu
	int width ;		 // Board eni

	static int count_liveCells ;

	char file[15] ; // file length max 15
	char turn ;
	int NewTotal ;
	char choice ;
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
	void set_Height_Width(); // Non Const

	// Bu fonksiyon digerinin aksine cell in pozisyonunu alir ve user in oynamasini saglar
	int play( char cellPosition); 		// Non const

	char getUserValue( );
	int StyleOfPlay( );
	int received( int selection );
	bool isEmpty( int i, int input) ;	// Cell in musait olup olmadigini return eder
	int  charTo_int(char user ) ;		// Karakteri integer a cevirir


	// play fonksiyonu parametresiz calisir ve bilgisayarin oynamasini saglar
	int play();
	char  get_input(int arr_size );
	char get_near_input(char first );

	void fill_file() ;

	int vertical_check() ;	 				 // Dikey dotlu tarama yapar
	int horizontal_check() ;				 // Yatay dortlu tarama yapar
	int diagonal_check() ;					 // Capraz line icin dortlu taramalari
	
	bool theGameEnd();

	// Cell sinifi
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

	Cell ** gameBoard;

};

int ConnectFour::count_liveCells = 0 ;


int main()
{	
	int vectorHeight , vectorWidth ;
	char modChoice ;
	srand(time(NULL));	

	cout<< "  ...  WELCOME TO CONNECT4 ...   "<<endl<<endl ;

	cout << "S : Only one game \n"
		 << "M : More than one game \n"
		 << "Please enter a choice: " ;
	cin	 >>	 modChoice;

	if( modChoice == 'S' || modChoice == 's' )
	{	
		int result = 0 ;

		cout<<"Enter Height: ";
		cin>> vectorHeight ;

		cout<<"Enter Width: ";
		cin>> vectorWidth ;

		ConnectFour game( vectorHeight, vectorWidth );
		game.set_mod( modChoice );

		char gameChoice;
		do{
			cout<<"\nPlayer | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );

		game.set_choice( gameChoice ) ;

		game.initial_board();

		result = game.playGame_S();

		while( result == 1 )
		{	
			game.read_file();
			result =  game.playGame_S();
		}
	
	}

	return 0;
}

	char ConnectFour::commands( char str[] ){
				

		if( ! strcmp ( str, "LOAD" ) )			
			return '/' ;
	}	


int  ConnectFour::playGame_S()
{	
	int total = getHeight() * getWidth() ;
	set_turn('1');
	int result = 0;
	

	//initial_board();
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

int ConnectFour::play( char cellPosition )
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

int ConnectFour::play()
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

void ConnectFour::set_Height( int gameHeight )
{
	height = gameHeight ;
}

void ConnectFour::set_Width( int gameWidth )
{
	width = gameWidth ;
}

int ConnectFour::read_file()
{	
	cout<<"readfile\n";
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
	print_board();

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

void ConnectFour::fill_file()
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


char  ConnectFour::get_input(int arr_size ){
	char value;
	int c_input=0;
	c_input= 1+ rand() % ( arr_size - 2 );

	value = char(c_input+ 'a' );
	return value;

}

void ConnectFour::set_mod( char gameMod )
{	mod = gameMod;	}

char ConnectFour::get_near_input(char first ){
	char str[ str_size ];
	int get=0;

	str[0] = first - 1;
	str[1] = first;
	str[2] = first + 1;
	get = rand() % 3;
	
	return  str[get];
}

char ConnectFour::getUserValue( )
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

		int temp=0;

		if( str.length() == 1 ){
			control = 1 ;
			value=str[0];
			if( isupper( value ) )
				return tolower( value );

			return value;
		}
		if( str.length() > 1 )
		{	
			for( int i=0 ; str[ i ] != ' '; ++i ){
				nextStr[i]=str[i];
				temp=i;
			}

			nextStr[temp+1]='\0';

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

			if( ! strcmp ( str, "SAVE" ) )				
				fill_file() ;

			commands(nextStr);
				
				
		}
	}
}

void ConnectFour::set_file( char fileName[]  )
{
	strcpy( file, fileName );

}
void ConnectFour::set_turn( char playTurn )
{
	if ( playTurn == '1' || playTurn == '2')
	{
		turn = playTurn ;

	}
	else
		exit(1);

}
void ConnectFour::set_NewTotal()
{
	NewTotal = getHeight() *getWidth() ;

}

int ConnectFour::StyleOfPlay( )
{
	int win_test = 0, win_test2=0, win_test3=0 ;
	int row=0, count=0;
	int four = 4;
	int total = getHeight() * getWidth() ;
	const int max_index = getHeight() - 1;
	int  GoBack = 1  ;
	int complete = 0 ;

	set_NewTotal();

	if( get_choice() == 'C' &&  ( get_mod() == 's' || get_mod() == 'S' ) )
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


	if ( get_choice() == 'P' &&  ( get_mod() == 's' || get_mod() == 'S' ) )
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

bool ConnectFour::theGameEnd(){

	int win_test, win_test2, win_test3 ;

	char str_C[]= "OOOO" ;
	char str_U[]= "XXXX" ;

	win_test2 = vertical_check();		// Dikey line da dortlu arar
	win_test = horizontal_check();			// yatayda dortlu arar
	win_test3 = diagonal_check();		// capraz dortluleri arar

	cout << "choice: " << get_choice() <<endl;

	if ( win_test == 1 || win_test2 == 1 || win_test3 == 1 )
	{	
		if( get_choice() == 'P' )
			cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
		if( get_choice() == 'C' )
			cout<<"\n	THE PLAYER WON !		\n"<<endl;

		return true;
	}
		
	else if ( win_test == 2 || win_test2 == 2 || win_test3 == 2 )
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

bool ConnectFour::isEmpty( int i, int input){
	bool empty;

	if( gameBoard[i][input].getValue() == '.' )
		empty= true ;
	else
		empty= false;

	return empty;
}

int ConnectFour::charTo_int(char user ){
	
	int int_val;		
	int_val = int(user) - 'a';		// char in integer a donusturulmus degeri
	return int_val;
}

void ConnectFour::set_choice( char oneChoice )
{
	choice = oneChoice ;
}

int ConnectFour::received( int selection )
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
ConnectFour::ConnectFour()
				: height(4), width(4)
{ }

ConnectFour::ConnectFour( int boardHeight )
				: width(8)
{
	if(	boardHeight < 4 )
		exit(1);

}


ConnectFour::ConnectFour(int boardHeight, int boardWidth )					
										: 	height(boardHeight), width(boardWidth)
{
	cout << "full constructor \n";

	test_Height_Width();

}

void ConnectFour::initial_board()
{	

	gameBoard = new Cell*[height] ;

	for (int i = 0; i < height; ++i)
		gameBoard[i] = new Cell[width] ;

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			gameBoard[i][j].setCell(i,j,'.');

}

int ConnectFour::getHeight() const {
	return height;
}
int ConnectFour::getWidth() const {
 	return width;
}


void ConnectFour::test_Height_Width()const
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

void ConnectFour::print_board( )const
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

void ConnectFour::Cell::setCell(int cell_row, int cell_col, char cell_value ){

	col = cell_col;
	row = cell_row ;
	chrCol = char(col + 'a') ;

	if ( cell_value == 'O' || cell_value == 'X' || cell_value == '.' )
	{
		value = cell_value;
	}
	else
	{
		cerr<<"invalid character value"<<endl;
		exit(1);

	}	

}

void ConnectFour::Cell::setValue( char position )
{	
	value = position ;	
}

void ConnectFour::set_firstValue( char  first )
{
	firstValue = first ;
}


int ConnectFour::horizontal_check(){	
	char str_U[]= "XXXX"  ;
	char str_C[]= "OOOO"  ;

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

int ConnectFour::vertical_check( ){

	char str_U[]= "XXXX" ;
	char str_C[]= "OOOO" ;

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

void ConnectFour::set_target( char targetValue )
{
	target = targetValue ;
}

int ConnectFour::diagonal_check(){
	
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

void ConnectFour::set_three(int value)
{	three = value;	}