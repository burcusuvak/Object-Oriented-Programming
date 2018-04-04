#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <sstream>
#define MinSize 4					// board icin alinabilcek min boyut
#define MaxSize 26
#define connect4 4					// oyunda birada bulunmasi gereken tas sayisi ( yatay, dikey vaya capraz olarak )
#define str_length 5				// substringler icin tutulacak array in boyutu
#define diagonal 3
#define str_size 3					// capraz check icin en az 3. indisten baslanabilir

using namespace std;

class ConnectFour
{

public:
	ConnectFour();
	ConnectFour( int boardHeight );
	ConnectFour( int boardHeight, int boardWidth );

	// File tipi arguman alan Constructor
	// bu constructor read_NewBoard_fromFile() fonksiyonunu cagirir
	ConnectFour( const char* file_name );
	
	// COPY CONSTRUCTOR 
	ConnectFour( const ConnectFour& rightSide );

	// terminalden ./exe <r1 gibi bir komut girildiginde bu dosyanin icindeki 
	// ornegin board.txt dosyasindaki board u okur 
	// set_Height() ve set_Width() fonksiyonlari ile maksimum satir 
	// ve sutun sayisina gore bir dikdortge  ** Cell gameBoard array i 
	// icin gerekli yerleri alir 
	int read_NewBoard_fromFile( const char* file_name );

	void set_choice( char oneChoice );
	char get_choice() const {	return choice;  }
	void set_mod( char gameMod );

	int get_three(){	return three;  }

	int playGame();

	int read_file() ;

	int getHeight() const ;
	int getWidth() const;

	char get_mod(){		return mod;    }
	void print_board() const ;
	void initial_board(); // Non Const

	// Assignment operator
	ConnectFour& operator =( const ConnectFour& rightSide );

	bool operator == ( const ConnectFour & other ) const;
	bool operator != ( const ConnectFour & other ) const;



	static void set_count_liveCells( int liveCells)
	{
		count_liveCells = liveCells;
	}

	static int get_countLiveCells(){    return count_liveCells;   }

	// DESTRUCTOR
	~ConnectFour();

private:

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
	void set_Height_Width(); // Non Const

	// Bu fonksiyon digerinin aksine cell in pozisyonunu alir ve user in oynamasini saglar
	int play( char cellPosition); 		// Non const
	
	// play fonksiyonu parametresiz calisir ve bilgisayarin oynamasini saglar
	int play();

	// user - user (P) oyun tipinde kullanicidan bir string tipinde 
	// bir input alir ve bunun bir char mi (kolon degeri)
	// yoksa bir komutmu oldugunu kontrol eder
	// Eger bir column ise( a,c,d etc. ) bu degeri dondurur
	// LOAD komutu ise '/' karakterini dondurur 
	// SAVE komutu ise fill_file() fonksiyonunn cagirir
	// ve tum verilerin dosyaya kaydedilmesini saglar
	char getUserValue( );
	int StyleOfPlay( );
	int received( int selection );

	// Cell in musait olup olmadigini return eder
	bool isEmpty( int i, int input) ;	

	// Karakteri integer a cevirir ve bu degeri return eder
	int  charTo_int(char user ) ;		

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

	// board un dikey line larında bir dortlu arar
	// ve bulursa 1 return eder aksi halde 0 return eder
	int vertical_check( const char* str_C , int quadruple ) ;	 
	
	// Board un tum yatay line larini tarar ve bir dortlu arar , 
	// eger bulursa 1 return eder aksi halde 0 return eder
	int horizontal_check( const char* str_C ) ;	

	// Dikey dortlu tarama yapar
	// board daki saga ya da sola dogru caprazlamasina 
	// tum line larda bir dotlu arar ve bulursa return olarak 1 dondurur	
	int diagonal_check( const char* str_C ) ;	

	// Horizontan vertical ya da diagonal fonksiyonlarindan
	// biri tarafından return edilen degerlerin kontrolunu
	// yapar ve kazanan varsa true dondurur 		 
	//  ayrica yasayan objelerin sayisi board un max hucre sayisina esitse
	// yani kazanan yoksa true dondurur yani oyunun bitisini soyler
	// Aksi hallerde false return eder
	bool theGameEnd(int winner_1, int winner_2, int winner_3);


	// Cell sinifi
	class Cell
	{

	public:		
		//  == operator overloading for two Cell
		bool operator == ( const Cell& other ) const;

		// != operator overloading for two Cell
		bool operator != ( const Cell& other ) const;
		// Prefix increment
		ConnectFour::Cell operator ++(); 	// Prefix increment
		
		// Postfix increment
		//Cell operator ++(int i);	// Prefix increment


		// stream insertion operator overloading
		// and inline implementation
		friend ostream& operator <<( ostream& outputStream, const Cell& theCell ){

			outputStream << theCell.row ;
			outputStream << theCell.col ;
			outputStream << theCell.value ;

			return outputStream ;

		}

		// stream extraction operator overloading
		friend istream& operator >>( istream& inputStream, Cell& theCell );

		void setCell( int cell_row, int cell_col, char cell_value );
		void setValue( char position ) ;
		int getCol()  const { return col; }
		int getRow() const { return row; }
		char get_chrCol() const {	return chrCol; }
		char getValue() const { return value; }		

		enum class CellState
		{
			A, B, C, D
				
		};

	private:

		int col ;
		int row ;
		char chrCol ;
		char value ;
		CellState state ;
	};

	// Dinamic Two-dimensional Cell array i
	Cell ** gameBoard;
	
	

};

int ConnectFour::count_liveCells = 0 ;


int main()
{	
	int boardHeight , boardWidth ;
	char modChoice ;
	char theFile[15] ;

	srand(time(NULL));	

	cout<< "  ...  WELCOME TO CONNECT4 ...   "<<endl<<endl ;

	cout << "S : Only one game \n"
		 << "M : More than one game \n"
		 << "Please enter a choice: " ;
	cin	 >>	 modChoice;

	if( modChoice == 'S' || modChoice == 's' )
	{	
		int result = 0 ;

		cin >> theFile ;

		ConnectFour game( theFile );
		game.set_mod( modChoice );

		char gameChoice;
		do{
			cout<<"\nPlayer | Computer : ";
			cin>>gameChoice;
			cout<< "gameChoice: "<<gameChoice<<endl;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );

		game.set_choice( gameChoice ) ;

		game.print_board();

		result = game.playGame();

		while( result == 1 )
		{	
			game.read_file();
			result =  game.playGame();
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
		/*cout<<"Enter Height: ";
		cin >>h;
		cout<<"Enter Width: ";
		cin >> w;
		ConnectFour game1( h,w );
		*/
		cin >> theFile;
		ConnectFour game1( theFile );
		game1.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );

		game1.set_choice( gameChoice ) ;

		// game2 icin gerekli bilgiler alinir ve game12objesi olusturulur		
		cin >> theFile;
		ConnectFour game2( theFile );
		game2.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game2.set_choice( gameChoice ) ;
		cout<<endl;		

		// game3 icin gerekli bilgiler alinir ve game3 objesi olusturulur
		cout<<"\nGame 3:"<<endl;
		cin >> theFile;
		ConnectFour game3( theFile );
		game3.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game3.set_choice( gameChoice ) ;
		cout<<endl;

		// game4 icin gerekli bilgiler alinir ve game4 objesi olusturulur
		cin >> theFile;
		ConnectFour game4( theFile );
		game4.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game4.set_choice( gameChoice ) ;
		cout<<endl;
		
		// game5 icin gerekli bilgiler alinir ve game5 objesi olusturulur
		cin >> theFile;
		ConnectFour game5( theFile );
		game5.set_mod( modChoice );

		do{
			cout<<"Player | Computer : ";
			cin>>gameChoice;
			gameChoice=toupper( gameChoice );
		}while( gameChoice != 'P' && gameChoice != 'C' );
		game5.set_choice( gameChoice ) ;
		cout<<endl;

		int result1 = -1, result2 = -1 , result3 = -1, result4 = -1, result5 = -1 ;

		while( result1 != 0 || result2 != 0 || result3 != 0 || result4 != 0 || result5 != 0 )
		{	
			cout <<"\nPlease Enter a Game Number:  ";
			cin >> num;

			if ( isalpha(num) ){
				cout<<"b!\n";
				cin >> num;
			}
			
			if( num == 0 )
				exit(1);
			switch(num)
			{
				case 1:	
					if( result1 == 0 )
						cout<<" Game 1 Over !!!\n";
					else
						result1 = game1.playGame();
					break;
				case 2:	
					if( result2 == 0 )
						cout<<" Game 2 Over !!!\n";
					else
						result2 = game2.playGame();
					break;
				case 3:	
					if( result3 == 0 )
						cout<<" Game 3 Over !!!\n";
					else
						result3 = game3.playGame();
					break;	
				case 4:	
					if( result4 == 0 )
						cout<<" Game 4 Over !!!\n";
					else
						result4 = game4.playGame();
					break;	
				case 5:	
					if( result5 == 0 )
						cout<<" Game 5 Over !!!\n";
					else
						result5 = game5.playGame();
					break;	
				
				default:
					cout<<"Invalid Game Number !!! "<<endl;	
			}	
			
			cout << endl ;
			cout << " Game1 == Game2 ?" << endl ;
			if ( game1 == game2 )
				cout << "YES" << endl ;
			else
				cout << "NO" << endl ;
			
			cout << endl ;
			cout << " Game1 != Game2 ?" << endl ;
			if ( game1 != game2 )
				cout << "YES" << endl ;
			else
				cout << "NO" << endl ;

		}
	}
	return 0;
}

ConnectFour::ConnectFour( const char* file_name ){

	cout << "fıle constructor \n";

	read_NewBoard_fromFile( file_name );

}

ConnectFour::ConnectFour( const ConnectFour& rightSide )
				: height( rightSide.height), width( rightSide.width )
{

	cout << "copy constructor \n";

	gameBoard = new Cell* [height];

	for (int i = 0; i < height; ++i)
	{
		gameBoard[i] = new Cell[width];

	}

}

int  ConnectFour::playGame()
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

bool ConnectFour::operator == ( const ConnectFour & other ) const{

	if ( height == other.height && width == other.width && choice == other.choice )
		return true;
	else
		return false;
}

bool ConnectFour::operator != ( const ConnectFour & other ) const{

	return !( *this == other );

}

int ConnectFour::read_NewBoard_fromFile( const char* file_name ){

	ifstream fin ;

	fin.open( file_name );
	if ( fin.fail( ) )
	{
		cerr<< "The file opening failed.\n" ;
		fin.clear();
		exit( 1 ) ;
	}

	const char White_Space(32) ;

	int rowCount = 0;
	int colCount = 0;
	int d=0;
	int max[30];
	fin.seekg( 0,ios::beg );

	if(fin){		
		string C;
	
		while( getline(fin,C) ){

			d = C.length();
			max[rowCount] = d;
			++rowCount;

			for( int i= 0; i < C.length() ; ++i ){
				
				if ( C[i] == White_Space )
					++colCount ;				
			}	
		}	

	}

	int maxValue = max[0] ;
	for (int i = 0; i < rowCount; ++i){
				
		if ( maxValue < max[i] )
			maxValue = max[i];
	}	

	set_Height(rowCount) ;
	set_Width( maxValue );

	test_Height_Width();
	initial_board();

	fin.clear();
	fin.seekg( 0,ios::beg );

	int line = 0;

	if(fin){		
		string C;

		while( getline(fin,C) ){
			
			for ( int j = 0; j < width; ++j ){
					
					if ( C[j] == White_Space )
						gameBoard[line][j].setValue( ' ' ) ;
					if( C[j] == '*' )
						gameBoard[line][j].setValue( '.' ) ;	
					if( j >= C.length() )
						gameBoard[line][j].setValue( ' ' );															
			}
			
			++line;	
		}		

	}

	fin.close();

 	return 0;
}
ConnectFour::~ConnectFour(){

	for (int i = 0; i < height; ++i)
	{
		delete [] gameBoard[i];
	}

	delete [] gameBoard;

	gameBoard = nullptr;

}

ConnectFour& ConnectFour::operator =( const ConnectFour& rightSide ){

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


bool ConnectFour::Cell::operator == ( const Cell & other ) const{

	if ( col == other.col && row == other.row && value == other.value )
		return true;
	else
		return false;
}

bool ConnectFour::Cell::operator != ( const Cell & other ) const{

	return !( *this == other );

}

bool ConnectFour::theGameEnd(int winner_1, int winner_2, int winner_3){
	
	if ( winner_1 == 1 || winner_2 == 1 || winner_3 == 1 ){	
		cout<<"\n	THE PLAYER 1 WON !		\n"<<endl;
		return true;
	}
	else if( winner_1 == 2 || winner_2 == 2 || winner_3 == 2 ){
		cout<<"\n	THE PLAYER 2 WON !		\n"<<endl;
		return true;
	}
	else if( get_countLiveCells() ==  get_NewTotal() ){
		cout<<"\nGame Over... NO WINNER !!!"<<endl;
		return false;
	}
	else if( (get_choice() == 'c' || get_choice() == 'C') && ( winner_1 == 1 || winner_2 == 1 || winner_3 == 1 ) ){
		cout<<"\n	THE PLAYER WON !		\n"<<endl;
		return true;
	}
	else if( (get_choice() == 'c' || get_choice() == 'C') && ( winner_1 == 2 || winner_2 == 2 || winner_3 == 2 ) ){
		cout<<"\n	THE COMPUTER WON !		\n"<<endl;
		return true;
	}	
	else
		return false;
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
		else
			lastValue = charTo_int( cellPosition );


		if(  lastValue < 0 || lastValue > max_index || isdigit( cellPosition ) )
		{
			while( lastValue < 0 || lastValue > max_index  )
			{	
				cout<<"INVALID VALUE Please Enter Again:	"<<endl;
				cellPosition = getUserValue();
				lastValue = charTo_int( cellPosition );
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
		{	char k = cellPosition ;	
		
			while( k == cellPosition )
			{	
				cout<<"INVALID VALUE Please Enter Again:	"<<endl;
				cellPosition  = getUserValue();
			}

			lastValue = charTo_int( cellPosition );
			legal = false ;
			RoWsize = getHeight() -1;

			while( legal != true && RoWsize >= 0)
			{	
				legal= isEmpty( RoWsize, lastValue);
				--RoWsize;
			}
			control = legal;
			if( legal == true ){

				gameBoard[RoWsize + 1][lastValue].setValue( get_target() ) ;
			}
			

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
{	cout<<"readfile\n";
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
		else if( str.length() > 1 )
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

			if( ! strcmp ( nextStr, "SAVE" ) ){
				cout<<"save"<<endl;
				fill_file() ;
			}	
			if( ! strcmp ( nextStr, "LOAD" ) )
			{	
				return '/' ;

			}	
				
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
				if( theGameEnd( win_test, win_test2, win_test3 ) )
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
				win_test2 = vertical_check( str_C, four );	
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
				turn = '2' ;	
			
				if( theGameEnd( win_test, win_test2, win_test3 ) )
				{
					cout<<endl;		
					print_board();		
					complete = 1 ;	
					return 0;
				}
				set_turn ('1') ;
			}	

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

				cout << endl ;
				print_board();

				win_test2 = vertical_check( str_C , four );		// Dikey line da dortlu arar
				win_test = horizontal_check( str_C );			// yatayda dortlu arar
				win_test3 = diagonal_check( str_C );		// capraz dortluleri arar

				if ( theGameEnd( win_test, win_test2, win_test3 ) )
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
				win_test2 = vertical_check( str_C , four );
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
			
				if ( theGameEnd( win_test, win_test2, win_test3 ) )
				{
					print_board();
					complete = 1 ;
					return 0;					
				}

				set_turn ('1') ;
			}				
					
		}	
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

				if( theGameEnd( win_test, win_test2, win_test3 ) )
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
			
				if( theGameEnd( win_test, win_test2, win_test3 ) )
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
		if( theGameEnd( win_test, win_test2, win_test3 ) )
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

				if ( theGameEnd( win_test, win_test2, win_test3 ) )
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
				++ twoMove ;

				cout<<"\ncount_liveCells:  "<<count_liveCells<<endl<<endl;

				cout<<endl;
				print_board();
				win_test2 = vertical_check( str_C , four );
				win_test = horizontal_check( str_C );
				win_test3 = diagonal_check( str_C );
			
				if ( theGameEnd( win_test, win_test2, win_test3 ) )
				{
					print_board();
					complete = 1 ;
					return 0;					
				}
				set_turn ('1') ;
			}		
		
					
		}	
		
		if(  twoMove == 2 )
			return 2;

	}	
	

	return 0;

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
				: height(5), width(5)
{

	cout << "default constructor \n";

 }

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

void ConnectFour::initial_board(){

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

void ConnectFour::print_board() const {

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

	if( cell_value == 'X' )
		state = CellState::A;

	else if ( cell_value = 'O' )
		state = CellState::B;

	else if( cell_value == '.')
		state = CellState::D;

	else
		state = CellState::C;

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
				string_temp[k] = gameBoard[i][j].getValue() ;
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

////////////////////////////////////////			

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
				string_temp[k] =  gameBoard[i][j].getValue() ;
				-- i;
				++k;
			}
			i += quadruple;
			string_temp[ k ] =  '\0' ;
			
			int temp = i  , last_temp = temp - quadruple ;

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