#include <iostream>
#include <vector>
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

	int vertical_check( const char* str_C , int quadruple ) ;	 // Dikey dotlu tarama yapar
	int horizontal_check( const char* str_C ) ;					 // Yatay dortlu tarama yapar
	int diagonal_check( const char* str_C ) ;					 // Capraz line icin dortlu taramalari

	// Cell sinifi
	class Cell
	{
	public:		
		void setCell(int col, int row, char value );
		void setValue( char position ) ;
		int getCol()  const { return col; }
		int getRow() const { return row; }
		char getValue() const { return value; }
	private:
		int col ;
		int row ;
		char chrCol ;
		char value ;
	};

	vector < vector<Cell> > gameCells ;

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

	if ( modChoice == 'M' || modChoice == 'm' )
	{	
		int result = 0 ;
		int num;
		int h, w;
		char gameChoice;
		cout<<"\nGame 1:"<<endl;
		// game1 icin gerekli bilgiler alinir ve game1 objesi olusturulur
		cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game1( h,w );
		game1.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game1.set_choice( gameChoice ) ;
		game1.initial_board();

		// game2 icin gerekli bilgiler alinir ve game1 objesi olusturulur		
		cout<<"\nGame 2:"<<endl;
		cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game2( h,w );
		game2.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game2.set_choice( gameChoice ) ;
		game2.initial_board();
		cout<<endl;		

		// game3 icin gerekli bilgiler alinir ve game1 objesi olusturulur
		/*cout<<"\nGame 3:"<<endl;
		cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game3( h,w );
		game3.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game3.set_choice( gameChoice ) ;
		game3.initial_board();
		cout<<endl;

		// game4 icin gerekli bilgiler alinir ve game1 objesi olusturulur
		cout<<"\nGame 4:"<<endl;		
		cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game4( h,w );
		game4.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game4.set_choice( gameChoice ) ;
		game4.initial_board();
		cout<<endl;
		
		// game5 icin gerekli bilgiler alinir ve game1 objesi olusturulur
		cout<<"\nGame 5:"<<endl;		
		cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game5( h,w );
		game5.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game5.set_choice( gameChoice ) ;
		game5.initial_board();
		cout<<endl;
*/
		int result1 = -1, result2 = -1 , result3 = -1, result4 = -1, result5 = -1 ;

		while( result1 != 0 || result2 != 0 )
		{	
			cout<<"Please Enter a Game Number:  ";
			cin >>num;
			switch(num)
			{
				case 1:	
					if( result1 == 0 )
						cout<<" Game 1 Over !!!\n";
					else
						result1 = game1.playGame_S();
					break;
				case 2:	
					if( result2 == 0 )
						cout<<" Game 2 Over !!!\n";
					else
						result2 = game2.playGame_S();
					break;
				/*case 3:	
					if( result3 == 0 )
						cout<<" Game 3 Over !!!\n";
					else
						result3 = game3.playGame_S();
					break;	
				case 4:	
					if( result4 == 0 )
						cout<<" Game 4 Over !!!\n";
					else
						result4 = game4.playGame_S();
					break;	
				case 5:	
					if( result5 == 0 )
						cout<<" Game 5 Over !!!\n";
					else
						result5 = game5.playGame_S();
					break;	
				*/
				default:
					cout<<"Invalid Game Number !!! "<<endl;	
			}		
		}
	}
	return 0;
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
			
			gameCells[RoWsize + 1][lastValue].setValue( get_target() ) ;
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
				gameCells[RoWsize + 1][lastValue].setValue( get_target() ) ;
			

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
				gameCells[RoWsize + 1][lastValue].setValue( get_target() ) ;
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
					gameCells[RoWsize + 1][lastValue].setValue( get_target() ) ;
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
	ifstream fin ;
	string str, str0, str1, str2, str3 ,str4, str_ALPHBT ;
	char gameKind;
	char new_chr;
	int h, w , gTotal, gCount;
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
	fin >> gCount ;
	set_count_liveCells(gCount);

	fin >> str4 ;
	fin >> gTotal ;
	set_NewTotal();


	fin >> str_ALPHBT ;
	gameCells.clear();

	initial_board();

	for ( unsigned int i = 0; i < gameCells.size() ; ++i )
	{
		for ( unsigned int j = 0; j <  gameCells[i].size() ; ++j )
		{
			fin >> new_chr ;
			gameCells[i][j].setValue( new_chr ) ;
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
	
	for ( unsigned int i = 0; i < gameCells.size() ; ++i )
	{
		for ( unsigned int j = 0; j <  gameCells[i].size() ; ++j )
		{
			fout << gameCells[i][j].getValue();
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

			if( ! strcmp ( nextStr, "SAVE" ) )				
				fill_file() ;		

			if( ! strcmp ( nextStr, "LOAD" ) )			
				return '/' ;
				
				
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
	char str_C[]= "OOOO" ;
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

		while( win_test != 1 && win_test !=2 && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && count_liveCells != total )
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
				win_test2 = vertical_check( str_C, four ) ;		// Dikey line da dortlu arar
				win_test = horizontal_check( str_C ) ;		// yatayda dortlu arar
				win_test3 = diagonal_check( str_C ) ;		// capraz dortluleri arar
				turn = '1' ;
				if( win_test==1 || win_test2 == 1 || win_test3 == 1)
				{
					cout<<"	THE PLAYER  WON !		"<<endl;
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
				win_test2 = vertical_check( str_C, four );	
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
				turn = '2' ;	
			
				if( win_test == 2 || win_test2 == 2 || win_test3 == 2)
				{
					cout<<"\n	THE COMPUTER WON !		\n"<<endl;
					cout<<endl;		

					print_board();		
					complete = 1 ;	
					return 0;
				}
				set_turn ('1') ;
			}	

			if( count_liveCells == get_NewTotal() )
				cout<<"\nGame Over... NO WINNER !!!"<<endl;	

		}
		
	}


	if ( get_choice() == 'P' &&  ( get_mod() == 's' || get_mod() == 'S' ) )
	{	
		while( win_test != 1 && win_test !=2  && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && get_countLiveCells() != total )
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

				win_test2 = vertical_check( str_C , four );		// Dikey line da dortlu arar
				win_test = horizontal_check( str_C );			// yatayda dortlu arar
				win_test3 = diagonal_check( str_C );		// capraz dortluleri arar

				if ( win_test == 1 || win_test2 == 1 || win_test3 == 1 )
				{
					cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
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
				win_test2 = vertical_check( str_C , four );
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
			
				if ( win_test == 2 || win_test2 == 2 || win_test3 == 2 )
				{
					cout<<"	\nTHE PLAYER 2 WON !		\n"<<endl;
					print_board();
					complete = 1 ;
					return 0;					
				}
				set_turn ('1') ;
			}		
		
					
		}	
		if ( get_countLiveCells() ==  get_NewTotal() )			
			cout<<"\nGame Over... NO WINNER !!!"<<endl;
	}

	if( get_choice() == 'C' &&  ( get_mod() == 'm' || get_mod() == 'M' ) )
	{
		int twoMove = 0;
		while( twoMove != 2 && win_test != 1 && win_test !=2  && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && get_countLiveCells() != total )
		{
			if (  complete != 1  && get_turn() == '1'  )
			{
				set_target('X');
				cout << "PLAYER : ";
				GoBack = received( 2 );
				if ( GoBack ==  1 )
					return GoBack ;
			
				
				++ count_liveCells ;
				++ twoMove ;

				cout<<"count_liveCells:  "<<count_liveCells<<endl;

				print_board() ;
				win_test2 = vertical_check( str_C, four ) ;		// Dikey line da dortlu arar
				win_test = horizontal_check( str_C ) ;		// yatayda dortlu arar
				win_test3 = diagonal_check( str_C ) ;		// capraz dortluleri arar
				turn = '1' ;
				if( win_test==1 || win_test2 == 1 || win_test3 == 1)
				{
					cout<<"	THE PLAYER  WON !		"<<endl;
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
				++ twoMove ;
				cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

				cout<<endl;		

				print_board();
				win_test2 = vertical_check( str_C, four );	
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
				turn = '2' ;	
			
				if( win_test == 2 || win_test2 == 2 || win_test3 == 2)
				{
					cout<<"\n	THE COMPUTER WON !		\n"<<endl;
					cout<<endl;		

					print_board();		
					complete = 1 ;	
					return 0;
				}
				set_turn ('1') ;
			}		
		}	
		if( count_liveCells == get_NewTotal() )
				cout<<"\nGame Over... NO WINNER !!!"<<endl;
		if(  twoMove == 2 )
			return 2;	
	}
	
	if ( get_choice() == 'P' &&  ( get_mod() == 'm' || get_mod() == 'M' ) )
	{

		int twoMove = 0;

		while( twoMove != 2 && win_test != 1 && win_test !=2  && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && get_countLiveCells() != total )
		{	
			if (  complete != 1  && get_turn() == '1'  )
			{	
				set_target('X');
				cout << "\nPLAYER 1: ";				
				GoBack = received( 2 );

				if ( GoBack == 1 )
					return GoBack ;				
				
				++ count_liveCells ;
				++ twoMove ;
				cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

				print_board();

				win_test2 = vertical_check( str_C , four );		// Dikey line da dortlu arar
				win_test = horizontal_check( str_C );			// yatayda dortlu arar
				win_test3 = diagonal_check( str_C );		// capraz dortluleri arar

				if ( win_test == 1 || win_test2 == 1 || win_test3 == 1 )
				{
					cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
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
				++ twoMove ;

				cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

				cout<<endl;
				print_board();
				win_test2 = vertical_check( str_C , four );
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
			
				if ( win_test == 2 || win_test2 == 2 || win_test3 == 2 )
				{
					cout<<"	\nTHE PLAYER 2 WON !		\n"<<endl;
					print_board();
					complete = 1 ;
					return 0;					
				}
				set_turn ('1') ;
			}		
		
					
		}	
		if ( get_countLiveCells() ==  get_NewTotal() )			
			cout<<"\nGame Over... NO WINNER !!!"<<endl;
		if(  twoMove == 2 )
			return 2;

	}	
	

	return 0;

}

bool ConnectFour::isEmpty( int i, int input){
	bool empty;

	if( gameCells[i][input].getValue() == '.' )
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

ConnectFour::ConnectFour( int vectorHeight )
				: width(8)
{
	if(	vectorHeight < 4 )
		exit(1);

}

ConnectFour::ConnectFour(int vectorHeight, int vectorWidth )					
										: 	height(vectorHeight), width(vectorWidth)
{
	test_Height_Width();

}

void ConnectFour::initial_board()
{	

	Cell temp;

	for ( int line = 0 ; line < getHeight() ; ++line )
	{	
		vector<Cell> horizontalCells;

		for( int column = 0 ; column < getWidth() ; ++column )			
		{	
			temp.setCell( line, column, '.');
			horizontalCells.push_back( temp );
		}

		gameCells.push_back( horizontalCells );
	}

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
	// Board un alfabetik kısmının ekrana basılması
	char chr= 'a' ;
	
	cout<<"\t";
	for( int i = 0, j = 0; i < getWidth(); ++i, ++j )
		cout << char(chr+j) << " " ;
	cout<<endl;

	// Current Board un ekrana basılması...
	for ( unsigned int i = 0; i < gameCells.size() ; ++i )
	{
		cout<<"\t";
		for ( unsigned int j = 0; j <  gameCells[i].size() ; ++j )
		{
			cout << gameCells[i][j].getValue() << " " ;
		}

		cout<<endl;
	}
}

void ConnectFour::Cell::setCell(int cell_col, int cell_row, char cell_value )
{
	col = cell_col;
	row = cell_row ;
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


int ConnectFour::horizontal_check( const char* str_C ){	
	char str_U[]= "XXXX"  ;

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
				string_temp[k] = gameCells[i][j].getValue() ;
				++j;
				++k;
			}
			j -= 4;

			string_temp[ k ] =  '\0' ;
/////////////////////////////////////////////
			int value_O = 0, value_X = 0 ;
			for (int i = 0; i < 4; ++i)
			{
				if(string_temp[i] == 'O')			
					++value_O;
				if(string_temp[i] == 'X')
					value_X = 1;
				if( value_X ==0 && value_O == 3 )		
					set_three(1);
				else if( value_X ==1 && value_O == 3 )
					set_three(0);
				
			}
			cout<<"yes: "<<get_three()<<endl;


////////////////////////////////////////			

			int temp = j, last_temp = j + 4 ;
			
			if( strcmp( str_U , string_temp ) == 0  )
			{					
				for( int s = temp ; s < last_temp ; ++s )
					gameCells[i][s].setValue('x') ;
					
				return 1 ;
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{
				for( int s = temp ; s < last_temp ; ++s )
					gameCells[i][s].setValue('o') ;
					
				return 2;		
			}	
			else
				winner = 0;			
		}
	}
	return winner;
}

int ConnectFour::vertical_check( const char* str_C , int quadruple ){

	char str_U[]= "XXXX" ;

	char string_temp[str_length];
	int winner=0, k;
	for( int j = 0; j < getWidth() ; ++j )
	{	
		for( int i = getHeight() - 1; i >= 3 ; -- i )
		{	
			k=0;
			while( k < quadruple ){
				string_temp[k] =  gameCells[i][j].getValue() ;
				-- i;
				++k;
			}
			i += quadruple;
			string_temp[ k ] =  '\0' ;
			
			int temp = i  , last_temp = temp - quadruple ;

			if( strcmp( str_U , string_temp ) == 0  )
			{	
				for( int s = temp ; s > last_temp ; --s )
					gameCells[s][j].setValue('x') ;
				return 1 ;
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{		
				for( int s = temp ; s > last_temp ; --s )
					gameCells[s][j].setValue('o') ;
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

int ConnectFour::diagonal_check( const char* str_C ){
	
	char str_U[]= "XXXX" ;

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
				str_line += gameCells[i][k+j].getValue();
			}	
			std::size_t pos = str_line.find("XXXX");
			std::size_t found = str_line.find("OOOO");

			if( pos != std::string::npos ){	
				/*for( int i = pos; i < pos + 4; ++i , ++j )
					gameCells[i][j+1].setValue('x');
				*/	
				return 1;
			}	

			else if ( found != std::string::npos  )
			{
				/*for( int i = found ; i < found + 4; ++i , ++j )
					gameCells[i][j].setValue('o');
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
				str_line += gameCells[i][k+j].getValue();
			
			std::size_t pos = str_line.find("XXXX");
			std::size_t found = str_line.find("OOOO");

			if( pos != std::string::npos ){	
				/*for( int i = pos; i < pos + 4; ++i , ++j )
					gameCells[i][j+1].setValue('x');
				*/	
				return 1;
			}	

			else if ( found != std::string::npos  )
			{
				/*for( int i = found ; i < found + 4; ++i , ++j )
					gameCells[i][j].setValue('o');
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
					string_temp[k] = gameCells[ i + sayac ][ j + sayac].getValue() ;
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
						gameCells[ r ][ c ].setValue('x');
					
					return 1 ;				
				}	
				else if(  strcmp( str_C , string_temp ) == 0  )
				{					
					for( int r = temp_row, c = temp_col ; r < last_row , c < last_col ; ++  r , ++c )
						gameCells[ r ][ c ].setValue('o') ;
						
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
					string_temp[k] = gameCells[ i + sayac ][ j + sayac].getValue() ;
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
						gameCells[ r ][ c ].setValue('x') ;
					return 1 ;
					
				}
				else if(  strcmp( str_C , string_temp ) == 0  )
				{
					temp_row= i + sayac -1 ;
					last_row = temp_row + 4 ;
					temp_col = j + sayac -1;
					last_col= temp_col + 4 ;
					
					for( int r = temp_row, c = temp_col;  r < last_row, c < last_col; ++ r, ++ c )
						gameCells[ r ][ c ].setValue('o') ;
					
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
					string_temp[k] = gameCells[ i - sayac ][ j + sayac].getValue() ;
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
						gameCells[ r ][ c ].setValue('x') ;
					return 1 ;
					
				}	
				else if(  strcmp( str_C , string_temp ) == 0  )
				{	
					temp_row= i - sayac + 1;
					last_row = temp_row - 4 ;
					temp_col = j + sayac - 1 ;
					last_col= temp_col + 4 ;
					
					for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
						gameCells[ r ][ c ].setValue('o') ;
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
					string_temp[k] = gameCells[ i - sayac ][ j + sayac].getValue();
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
						gameCells[ r ][ c ].setValue('x') ;
					return 1 ;
				}	
				else if(  strcmp( str_C , string_temp ) == 0  )
				{
					temp_row= i - sayac  + 1;
					last_row = temp_row - 4 ;
					temp_col = j + sayac - 1 ;
					last_col= temp_col + 4 ;
					for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
						gameCells[ r ][ c ].setValue('o') ;
					
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