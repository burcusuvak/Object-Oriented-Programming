// INVALUED VALUE ENTER AGAIN durumlari icin SAVE ve LOAD
// komutlari girisi yapmadim
// Sadece PLAYER:  PLAYER 1:   ve PLAYER 2: durumlarinda
// SAVE ve LOAD komutu giriyorum.



#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <sstream>
#define MinSize 4											// board icin alinabilcek min boyut
#define MaxSize 20											// board icin alinabilcek max boyut
#define connect4 4											// oyunda birada bulunmasi gereken tas sayisi ( yatay, dikey vaya capraz olarak )
#define str_length 5											// substringler icin tutulacak array in boyutu
#define diagonal 3
#define str_size 3											// capraz check icin en az 3. indisten baslanabilir
void initial_board(char board[][MaxSize], int size);			// board icin tutulan arrayi initialize eder
void print_board(char board[][MaxSize], int size);			// board un son halini ekrana basar
bool isEmpty(char board[][MaxSize], int i, int input);			// gidilmek istenen yerin bos olup olmadigini kontrol eder

char get_input(int size );
char get_near_input(char first );

//	Bu 3 fonksiyonda CONST REFERENCE kullanilmistir
int horizontal_check( char board[][MaxSize], int size , const char* str_C );		// her satir icin yatay dortlu arar
int vertical_check( char board[][MaxSize], const int size, const char* str_C , int quadruple = 4 );  // DEFAULT ARGUMENT kullanimi burada yapildi
int diagonal_check( char board[][MaxSize], const int size , const char* str_C );

int charTo_int( char user );
int getSize();	// Bu fonksiyonun implentation kisminda AUTO TYPE kullanilmistir
char get_choice();

char getUserValue( char game_board[][MaxSize], int board_size ,char* file_name, char& turn, char& kind ,  int& newCount , int& NewTotal );
// getUserValue fonksiyonunda CALL BY REFERENCE yapilmistir

int received(char game_board[][MaxSize],const int max_index,int board_size,int& lastValue,int& row,int selection,char target,char* file_name,char& turn,char& choice,int& NewCount,int& NewTotal);

void fill_file( char file_name[], char game_board[][MaxSize], int board_size ,char& turn, char& kind ,  int& newCount , int& NewTotal ) ;

int  read_file( char file_name[], char  game_board[][MaxSize], int& board_size, char& turn, char& kind ,  int& newCount , int& NewTotal ) ;
// kind oyunun turunu saklar user-user veya user-comp
// turn ise sıranın kimde oldugunu saklar

int StyleOfPlay( char game_board[][MaxSize], int board_size, char choice , char* file_name, char& turn , int& newCount , int& NewTotal );
// Bu fonksiyonda DECLTYPE kullanilmistir

using namespace std;
using std :: ifstream ;
using std :: ofstream ;
using std::string;
using std :: ios;
using std :: cout;

int main()
{
	char game_board[MaxSize][MaxSize] ;					 // oyun tahtasi icin bir array tutar
	int board_size ;
	int result = 0 ;
	char file [15] ; // file length max 15
	
	srand(time(NULL));	
	char turn = '1', kind ;
	int NewCount = 0 ; 
	decltype(NewCount) NewTotal ;
	NewTotal = 0 ;
	
	cout<< "  ...  WELCOME TO CONNECT4 ...   "<<endl;
	
	char choice;
	board_size=getSize();

	choice=get_choice();									// kullanici oyunu hangi sekilde oynayacagini secer
	initial_board(game_board, board_size);
	print_board(game_board, board_size);
	cin.ignore();
	result = StyleOfPlay( game_board, board_size, choice, file, turn ,  NewCount , NewTotal );

	while( result == 1 )
	{	
		read_file( file, game_board, board_size, turn, kind,  NewCount , NewTotal );
		print_board(game_board, board_size);
		result = StyleOfPlay( game_board, board_size, kind, file, turn, NewCount , NewTotal );
	}
	
	return 0;
}
int read_file( char file_name[], char  game_board[][MaxSize], int& board_size, char& turn, char& kind , int& NewCount , int& NewTotal ){
	
	ifstream fin ;
	string str, str1, str2, str3 ,str4, str_ALPHBT ;

	fin.open( file_name );
	if ( fin.fail( ) )
	{
		cerr<< "The file opening failed.\n" ;
		fin.clear();
		exit( 1 ) ;
	}

	fin >>str;
	fin >> board_size;

	fin >> str1 ;
	fin >> turn ;
	
	fin >> str2 ;
	fin >> kind ;
	
	fin >> str3 ;
	fin >> NewCount ;
	
	fin >> str4 ;
	fin >> NewTotal ;
	
	fin >> str_ALPHBT ;
	
	for( int i = 0 ; i < board_size ; ++i )
	{	
		for( int j = 0 ; j < board_size ; ++j ){
			fin >> game_board[ i ][ j ] ;		
		}		
	}

	fin.close() ;
	
	return 0 ;
}


void fill_file( char file_name[], char game_board[][MaxSize], int board_size ,char& turn, char& kind , int& NewCount , int& NewTotal ){

	ofstream fout;

	fout.open( file_name, ios :: out | ios :: in | ios :: trunc );
	if ( fout.fail( ) )
	{
		cerr<< "The file opening failed.\n" ;
		fout.clear();
		exit( 1 ) ;
	}

	fout << "size " << board_size << endl ;
	fout << "OYUN_SIRA " << turn << endl ;
	fout << "OYUN_SEKLI " << kind << endl ;
	fout << "COUNT " << NewCount << endl ;
	fout << "TOTAL " << NewTotal << endl ;
	
	char chr= 'a' ;
	
	for(int i=0, j=0; i <board_size; ++i, ++j)
		fout<<char(chr+j) ;
	fout<<endl;
	
	for(int i=0; i < board_size; ++i)
	{
		for(int j=0; j < board_size; ++j)
			fout<< game_board[i][j] ;
		fout<<endl;
	}

	fout.clear();
	fout.close() ;

}

int StyleOfPlay( char game_board[][MaxSize], int board_size, char choice, char* file_name, char& turn , int& NewCount , int& NewTotal ){

	char str_C[]= "OOOO" ;
	int win_test = 0, win_test2=0, win_test3=0 ;
	int row=0, count=0;
	int val1=0, val2=0;
	int total=board_size*board_size;
	const int max_index = board_size - 1;
	int  GoBack = 1  ;
	int complete = 0 ;

	NewTotal = total ;

	if( choice == 'C' )
	{	
		char  value;
		val1 = get_input( max_index + 1 );
		
		while( win_test != 1 && win_test !=2 && count != total && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && NewCount != NewTotal )
		{
			if (  complete != 1  && turn == '1'  )
			{
				cout << "PLAYER : ";
				GoBack = received(game_board, max_index, board_size, val1, row, 2 ,'X', file_name, turn, choice ,  NewCount , NewTotal );
				if ( GoBack ==  1 )
					return GoBack ;
				
				++ count;
				++ NewCount ;
				print_board(game_board, board_size);
				win_test2 = vertical_check(game_board, board_size , str_C ) ;		// Dikey line da dortlu arar
				win_test = horizontal_check(game_board, board_size , str_C ) ;		// yatayda dortlu arar
				win_test3 = diagonal_check( game_board, board_size , str_C ) ;		// capraz dortluleri arar
				turn = '1' ;
				if( win_test==1 || win_test2 == 1 || win_test3 == 1)
				{
					cout<<"	THE PLAYER  WON !		"<<endl;
					print_board(game_board, board_size);		
					complete = 1 ;		
				}
			}
			turn = '2' ;			
			
			if ( complete != 1  && turn == '2'  )
			{		
				GoBack = received(game_board, max_index, board_size, val1, row, 1 ,'O', file_name, turn, choice ,  NewCount , NewTotal );
				if ( GoBack ==  1 )
					return GoBack ;
					
				++ count;
				++ NewCount ;
				print_board(game_board, board_size);
				win_test2 = vertical_check(game_board, board_size, str_C );	
				win_test = horizontal_check(game_board, board_size, str_C );
				win_test3 = diagonal_check( game_board, board_size, str_C );
				turn = '2' ;	
			
				if( win_test == 2 || win_test2 == 2 || win_test3 == 2)
				{
					cout<<"	THE COMPUTER WON !		"<<endl;
					print_board(game_board, board_size);		
					complete = 1 ;	
				}
				turn = '1' ;
			}		

		}

		if( count == total || NewCount == NewTotal )
			cout<<"\nGAME OVER !"<<endl;
	}
	
	if ( choice == 'P' )
	{	
		while( win_test != 1 && win_test !=2 && count != total && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 && NewCount != NewTotal )
		{	
			if (  complete != 1  && turn == '1'  )
			{
				cout << "PLAYER 1: ";
			
				GoBack = received(game_board, max_index, board_size, val1, row, 2, 'X' , file_name, turn, choice ,  NewCount , NewTotal );

				if ( GoBack == 1 )
					return GoBack ;
				
				++ count;
				++ NewCount ;


				print_board(game_board, board_size);
				win_test2 = vertical_check(game_board, board_size, str_C );		// Dikey line da dortlu arar
				win_test = horizontal_check(game_board, board_size, str_C );		// yatayda dortlu arar
				win_test3 = diagonal_check( game_board, board_size, str_C );		// capraz dortluleri arar

				if ( win_test==1 || win_test2 == 1 || win_test3 == 1)
				{
					cout<<"	THE PLAYER 1 WON !		"<<endl;
					print_board(game_board, board_size);
					complete = 1 ;	
				}

			}	
			turn = '2' ;	
			if ( complete != 1  && turn == '2'  )
			{

				cout << "PLAYER 2: ";
				GoBack = received(game_board, max_index, board_size, val2, row, 2, 'O', file_name , turn, choice ,  NewCount , NewTotal );

				if ( GoBack == 1 )
					return GoBack ;
				++count;
				++ NewCount ;

				print_board(game_board, board_size);
				win_test2 = vertical_check( game_board, board_size , str_C );
				win_test = horizontal_check(game_board, board_size , str_C );
				win_test3 = diagonal_check( game_board, board_size , str_C );
			
				if ( win_test == 2 || win_test2 == 2 || win_test3 == 2)
				{
					cout<<"	THE PLAYER 2 WON !		"<<endl;
					print_board(game_board, board_size);
					complete = 1 ;					
				}
				turn = '1' ;
			}		

		}
		
		if ( count == total || NewCount ==  NewTotal )
			cout<<"\nGAME OVER !"<<endl;
	}	

	return 0;

}

int received(char game_board[][MaxSize],const int max_index,int board_size,int& lastValue,int& row,int selection,char target,char* file_name,char& turn,char& choice,int& NewCount,int& NewTotal)
{
	bool legal= false;
	char GoBack ;
	char value;
	char nearValue;
	int RoWsize= max_index;
	bool control { false };
	if( selection == 1 )
	{
		while(  control != true )
		{	
			RoWsize= max_index;
			if( row == 0 )
			{	
				lastValue = charTo_int( lastValue );
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
					legal= isEmpty(game_board, RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;
				if( legal == true )
					game_board[RoWsize + 1][lastValue]= target;
				else
				{	char k= nearValue;	
					while( k== nearValue || lastValue < 0 || lastValue > max_index )
					{
						nearValue = get_near_input( nearValue );
						lastValue= charTo_int( nearValue );

					}

					legal = false ;
					RoWsize = max_index ;
					while( legal != true && RoWsize >= 0)
					{	
						legal= isEmpty(game_board, RoWsize, lastValue);
						--RoWsize;
					}
					control = legal;
					if( legal == true )
						game_board[RoWsize + 1][lastValue]= target;
				}
			}
		}		
	}
	
	
	if( selection ==2 )
	{
		while(  control != true )
		{	
			RoWsize= max_index;
			value= getUserValue( game_board , board_size , file_name, turn, choice,  NewCount , NewTotal );	
			GoBack = value;

			if ( GoBack == '/' ) //   '/' karakteri rastgele secilmistir
			{
				return 1 ;
			}
			else{				
				lastValue= charTo_int(value);

			}	
			if(  lastValue < 0 || lastValue > max_index || isdigit( value ) )
			{
				while( lastValue < 0 || lastValue > max_index  )
				{			
					cout<<"INVALID VALUE Please Enter Again:	"<<endl;
					value= getUserValue( game_board, board_size, file_name, turn, choice , NewCount , NewTotal );
					lastValue= charTo_int(value);
				}
			}

			while( legal != true && RoWsize >= 0)
			{	
				legal= isEmpty(game_board, RoWsize, lastValue);
				--RoWsize;
			}
			control = legal;
		
			if( legal == true )
				game_board[RoWsize + 1][lastValue]= target;
			else
			{	char k= value;	
		
				while( k== value)
				{
					cout<<"INVALID VALUE Please Enter Again:		"<<endl;
					cin>> value;
				}

				lastValue= charTo_int(value);

				legal = false ;
				RoWsize = max_index ;
				while( legal != true && RoWsize >= 0)
				{		
					legal= isEmpty(game_board, RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;
				if( legal == true )
					game_board[RoWsize + 1][lastValue]= target;

			}
		}	
	}
	return 0;
}

char getUserValue( char game_board[][MaxSize] ,int board_size, char* file_name, char& turn, char& kind, int& NewCount, int& NewTotal ){
	char value ;	
	string str ;
	char main_board[MaxSize][MaxSize] ;
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
			for( int i=0 ; str[ i ] != ' '; ++i){
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
			strcpy( file_name,nextStr2 ) ;
			
			if( ! strcmp ( nextStr, "SAVE" ) )
				fill_file( nextStr2, game_board, board_size, turn, kind , NewCount, NewTotal ) ;
			if( ! strcmp ( nextStr, "LOAD" ) )
			{	
				return '/' ;

			}	
				
		}
	}
}

char get_near_input(char first ){
	char str[ str_size ];
	int get=0;

	str[0] = first - 1;
	str[1] = first;
	str[2] = first + 1;
	get = rand() % 3;
	
	return  str[get];
}
char  get_input(int arr_size ){
	char value;
	int c_input=0;
	c_input= 1+ rand() % ( arr_size - 2 );

	value = char(c_input+ 'a' );
	return value;

}

int diagonal_check( char board[][MaxSize], const int size, const char* str_C ){
	
	char str_U[]= "XXXX" ;

	char string_temp[str_length];
	int winner=0;
	int temp_row = 0, last_row = 0, temp_col = 0, last_col = 0 ;
	for( int j= size-4, count=0; j > 0 && count < size -3; -- j, ++count )
	{	
		int i=0, temp=0, sayac=0 ;
		while( sayac <= count )
		{
			for( int  k=0; k<4 ; ++k )
			{	
				string_temp[k] = board[ i + sayac ][ j + sayac];
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
					board[ r ][ c ] = 'x';
				
				return 1 ;				
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{					
				for( int r = temp_row, c = temp_col ; r < last_row , c < last_col ; ++  r , ++c )
					board[ r ][ c ] = 'o';
					
				return 2;
			}	
			else
				winner = 0;
		}		
	}
	
	for(int i= size-4, count=0; i >=0 && count <= size-3; --i, ++count )
	{
		int j=0 ,temp=0 , sayac=0;
		while( sayac <= count )
		{
			for( int  k=0; k<4 ; ++k )
			{
				string_temp[k] = board[ i + sayac ][ j + sayac];
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
					board[ r ][ c ] = 'x' ;
				return 1 ;
				
			}
			else if(  strcmp( str_C , string_temp ) == 0  )
			{
				temp_row= i + sayac -1 ;
				last_row = temp_row + 4 ;
				temp_col = j + sayac -1;
				last_col= temp_col + 4 ;
				
				for( int r = temp_row, c = temp_col;  r < last_row, c < last_col; ++ r, ++ c )
					board[ r ][ c ] = 'o' ;
				
				return 2;
				
			}	
			else
				winner = 0;
		}	
	}
		
	for( int j=size-4, count=0 ; j > 0 && count < size -3 ; -- j , ++count )
	{
		int i=size-1 , temp=0, sayac=0;
		while( sayac <= count )
		{
			for( int  k=0; k<4 ; ++k )
			{	
				string_temp[k] = board[ i - sayac ][ j + sayac];
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
					board[ r ][ c ] = 'x' ;
				return 1 ;
				
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{	
				temp_row= i - sayac + 1;
				last_row = temp_row - 4 ;
				temp_col = j + sayac - 1 ;
				last_col= temp_col + 4 ;
				
				for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
					board[ r ][ c ] = 'o' ;
				return 2;
				
			}	
			else
				winner = 0;
		}	
	}
	
	for( int i= diagonal, count=0; i < size && count <= size - 3 ; ++i, ++count )
	{	
		int j=0, temp=0, sayac=0;
		while( sayac <= count )
		{	
			for( int  k=0; k<4 ; ++k )
			{	
				string_temp[k] = board[ i - sayac ][ j + sayac];
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
					board[ r ][ c ] = 'x' ;
				return 1 ;
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{
				temp_row= i - sayac  + 1;
				last_row = temp_row - 4 ;
				temp_col = j + sayac - 1 ;
				last_col= temp_col + 4 ;
				for( int r = temp_row, c = temp_col;  r > last_row, c < last_col; -- r, ++ c )
					board[ r ][ c ] = 'o' ;
				
				return 2;
				
			}	
			else
				winner = 0;		
		}
	}
	
	return winner;	
}
int vertical_check( char board[][MaxSize], const int size, const char* str_C , int quadruple ){

	char str_U[]= "XXXX" ;

	char string_temp[str_length];
	int winner=0, k;
	for( int j = 0; j < size ; ++j )
	{	
		for(int i=size-1; i >= 3 ; -- i )
		{	
			k=0;
			while( k < quadruple ){
				string_temp[k] = board[i][j];
				-- i;
				++k;
			}
			i += quadruple;
			string_temp[ k ] =  '\0' ;
			
			int temp = i  , last_temp = temp - quadruple ;

			if( strcmp( str_U , string_temp ) == 0  )
			{	
				for( int s = temp ; s > last_temp ; --s )
					board[s][j] = 'x';					
				return 1 ;
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{		
				for( int s = temp ; s > last_temp ; --s )
					board[s][j] = 'o';	
				return 2;				
			}	
			else
				winner = 0;
		}											
	}
	return winner;	
}
int horizontal_check( char board[][MaxSize], int size, const char* str_C ){	
	char str_U[]= "XXXX"  ;

	char string_temp[str_length] ;
	int winner = 0 ;
	int k ;
	for( int i = size-1; i >= 0; --i )
	{
		for( int j = 0 ; j < (size - 3) ; ++j )
		{	
			k=0;
			while( k<4 ){
				string_temp[k] = board[i][j];
				++j;
				++k;
			}
			j -= 4;

			string_temp[ k ] =  '\0' ;
			int temp = j, last_temp = j + 4 ;
			
			if( strcmp( str_U , string_temp ) == 0  )
			{					
				for( int s = temp ; s < last_temp ; ++s )
					board[i][s] = 'x';
					
				return 1 ;
			}	
			else if(  strcmp( str_C , string_temp ) == 0  )
			{
				for( int s = temp ; s < last_temp ; ++s )
					board[i][s] = 'o';
					
				return 2;		
			}	
			else
				winner = 0;			
		}
	}
	return winner;
}

bool isEmpty(char board[][MaxSize], int i, int input){
	bool empty;
	
	if( board[i][input]== '.' )
		empty= true ;
	else
		empty= false;

	return empty;
}

int charTo_int(char user ){
	
	int int_val;		
	int_val = int(user) - 'a';		// char in integer a donusturulmus degeri
	return int_val;
}
void initial_board(char board[MaxSize][MaxSize], int size){
	
	for( int i=0; i<size; ++i )
		for( int j=0;  j<size; ++j )
			board[i][j]= '.' ;	

}
void print_board(char board[MaxSize][MaxSize], int size){	
	char chr= 'a' ;
	
	cout<<"\t";
	for(int i=0, j=0; i<size; ++i, ++j)
		cout<<char(chr+j)<< " " ;
	cout<<endl;

	for(int i=0; i<size; ++i)
	{
		cout<<"\t";
		for(int j=0; j<size; ++j)
			cout<<board[i][j]<< " " ;
		cout<<endl;
	}
		cout<<endl;	
}
char get_choice(){
	char choice;
	do{
		cout<<" \npvp :  P	or	  pvc :  C\n"
			<<"\nEnter a choice : ";
		cin>>choice;
		choice=toupper( choice );
	}while( choice != 'P' && choice != 'C' );
	
	return choice;
}

int getSize(){
	auto board_size = 0;	
	cout<<"\nPlease enter an even number 4x4, 6x6, ..., 20x20 for board : ";
	cin>>board_size;
	
	while( board_size< MinSize || board_size> MaxSize || board_size%2 != 0  )
	{		
			cout<< "INVALID VALUE Enter Again"<< endl
				<< "Please enter an even number from 4 to 20 :	";
			cin>>board_size;		
	}
	return board_size;
	
}
