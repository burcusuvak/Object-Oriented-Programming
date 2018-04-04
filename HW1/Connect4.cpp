#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<cctype>
#define MinSize 4											// board icin alinabilcek min boyut
#define MaxSize 20											// board icin alinabilcek max boyut
#define connect4 4											// oyunda birada bulunmasi gereken tas sayisi ( yatay, dikey vaya capraz olarak )
#define length 5											// substringler icin tutulacak array in boyutu
#define diagonal 3
#define str_size 3											// capraz check icin en az 3. indisten baslanabilir
void initial_board(char board[][MaxSize], int size);			// board icin tutulan arrayi initialize eder
void print_board(char board[][MaxSize], int size);			// board un son halini ekrana basar
char get_input(int size );
char get_near_input(char first );
bool is_empty(char board[][MaxSize], int i, int input);			// gidilmek istenen yerin bos olup olmadigini kontrol eder
int horizontal_check( char board[][MaxSize], int size );		// her satir icin yatay dortlu arar
int vertical_check( char board[][MaxSize], const int size );
int diagonal_check( char board[][MaxSize], const int size );
int charTo_int( char user );
int getSize();
char getUserValue();
char get_choice();
void received(char game_board[][MaxSize], const int max_index, int& lastValue, int& row, int choice, char target );

using namespace std;

int main()
{
	char game_board[MaxSize][MaxSize];					 // oyun tahtasi icin bir array tutar
	int board_size, user_1=0, user_2=0;
	int row=0, count=0;
	int val1=0, val2=0;
	int win_test = 0, win_test2=0, win_test3=0 ;
	cout<< "  ...  WELCOME TO CONNECT4 ...   "<<endl;
	
	char choice;
	board_size=getSize();
	choice=get_choice();									// kullanici oyunu hangi sekilde oynayacagini secer
	int total=board_size*board_size;
	const int max_index = board_size - 1;
					
	initial_board(game_board, board_size);
	print_board(game_board, board_size);
	
	srand(time(NULL));
	
	if( choice == 'C' )
	{	
		char  value;
		val1 = get_input( max_index + 1 );
		
		while( win_test != 1 && win_test !=2 && count != total && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 )
		{
			cout << "PLAYER : ";
			received(game_board, max_index, val1, row, 2 ,'X');
			++count;
			print_board(game_board, board_size);
			win_test2 = vertical_check(game_board, board_size);		// Dikey line da dortlu arar
			win_test = horizontal_check(game_board, board_size);		// yatayda dortlu arar
			win_test3 = diagonal_check( game_board, board_size );		// capraz dortluleri arar

			if( win_test==1 || win_test2 == 1 || win_test3 == 1)
			{
				cout<<"	THE PLAYER  WON !		"<<endl;
				print_board(game_board, board_size);			
			}	
			
			else
			{		
				received(game_board, max_index, val1, row, 1 ,'O');
				++count;
				print_board(game_board, board_size);
				win_test2 = vertical_check(game_board, board_size);	
				win_test = horizontal_check(game_board, board_size);
				win_test3 = diagonal_check( game_board, board_size );	
			}
			if( win_test == 2 || win_test2 == 2 || win_test3 == 2)
			{
				cout<<"	THE COMPUTER WON !		"<<endl;
				print_board(game_board, board_size);		
			}	

		}
		if( count == total )
			cout<<"\nGAME OVER !"<<endl;
	}
	
	if( choice == 'P' )
	{
		while( win_test != 1 && win_test !=2 && count != total && win_test2 != 1 && win_test2 != 2 && win_test3 != 1 && win_test3 != 2 )
		{
			cout << "PLAYER 1: ";
			received(game_board, max_index, val1, row, 2, 'X');
			++count;
			print_board(game_board, board_size);
			win_test2 = vertical_check(game_board, board_size);		// Dikey line da dortlu arar
			win_test = horizontal_check(game_board, board_size);		// yatayda dortlu arar
			win_test3 = diagonal_check( game_board, board_size );		// capraz dortluleri arar

			if( win_test==1 || win_test2 == 1 || win_test3 == 1)
			{
				cout<<"	THE PLAYER 1 WON !		"<<endl;
				print_board(game_board, board_size);	
			}	
			else{
				cout << "PLAYER 2: ";
				received(game_board, max_index, val2, row, 2, 'O');
				++count;
				print_board(game_board, board_size);
				win_test2 = vertical_check( game_board, board_size );
				win_test = horizontal_check(game_board, board_size);
				win_test3 = diagonal_check( game_board, board_size );
			}
			if( win_test == 2 || win_test2 == 2 || win_test3 == 2)
			{
				cout<<"	THE PLAYER 2 WON !		"<<endl;
				print_board(game_board, board_size);
			}	

		}
		if( count == total )
			cout<<"\nGAME OVER !"<<endl;
	}	
	
	return 0;
}
void received(char game_board[][MaxSize], const int max_index, int& lastValue, int& row, int choice, char target ){
	int legal= 0;
	char value;
	char nearValue;
	int RoWsize= max_index;
	int control = 0;

	if( choice == 1 )
	{
		while(  control != 1 )
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

				while( legal != 1 && RoWsize >= 0)
				{	
					legal= is_empty(game_board, RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;
				if( legal == 1 )
					game_board[RoWsize + 1][lastValue]= target;
				else
				{	char k= nearValue;	
					while( k== nearValue || lastValue < 0 || lastValue > max_index )
					{
						nearValue = get_near_input( nearValue );
						lastValue= charTo_int( nearValue );

					}

					legal=0;
					RoWsize = max_index ;
					while( legal != 1 && RoWsize >= 0)
					{	
						legal= is_empty(game_board, RoWsize, lastValue);
						--RoWsize;
					}
					control = legal;
					if( legal == 1 )
						game_board[RoWsize + 1][lastValue]= target;
				}
			}
		}		
	}
	
	
	if( choice==2 )
	{
		while(  control != 1 )
		{	
			RoWsize= max_index;
			value= getUserValue();	
			lastValue= charTo_int(value);
	
			if(  lastValue < 0 || lastValue > max_index || isdigit( value ) )
			{
				while( lastValue < 0 || lastValue > max_index  )
				{			
					cout<<"INVALID VALUE Please Enter Again:	"<<endl;
					value= getUserValue();
					lastValue= charTo_int(value);
				}
			}

			while( legal != 1 && RoWsize >= 0)
			{	
				legal= is_empty(game_board, RoWsize, lastValue);
				--RoWsize;
			}
			control = legal;
		
			if( legal == 1 )
				game_board[RoWsize + 1][lastValue]= target;
			else
			{	char k= value;	
		
				while( k== value)
				{
					cout<<"INVALID VALUE Please Enter Again:		"<<endl;
					cin>> value;
				}

				lastValue= charTo_int(value);

				legal=0;
				RoWsize = max_index ;
				while( legal != 1 && RoWsize >= 0)
				{		
					legal= is_empty(game_board, RoWsize, lastValue);
					--RoWsize;
				}
				control = legal;
				if( legal == 1 )
					game_board[RoWsize + 1][lastValue]= target;

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
	
	return str[get];
}
char  get_input(int arr_size ){
	char value;
	int c_input=0;
	c_input= 1+ rand() % ( arr_size - 2 );

	value = char(c_input+ 'a' );
	return value;

}

int diagonal_check( char board[][MaxSize], const int size ){
	
	char str_U[]= "XXXX" ;
	char str_C[]= "OOOO" ;
	char string_temp[length];
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
				return 1 ;
			else if(  strcmp( str_C , string_temp ) == 0  )
				return 2;
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
int vertical_check( char board[][MaxSize], const int size ){

	char str_U[]= "XXXX" ;
	char str_C[]= "OOOO" ;
	char string_temp[length];
	int winner=0, k;
	for( int j = 0; j < size ; ++j )
	{	
		for(int i=size-1; i >= 3 ; -- i )
		{	
			k=0;
			while( k<4 ){
				string_temp[k] = board[i][j];
				-- i;
				++k;
			}
			i += 4;
			string_temp[ k ] =  '\0' ;
			
			int temp = i  , last_temp = temp - 4 ;

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
int horizontal_check( char board[][MaxSize], int size ){	
	char str_U[]= "XXXX"  ;
	char str_C[]= "OOOO"  ;
	char string_temp[length] ;
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

bool is_empty(char board[][MaxSize], int i, int input){
	int empty;
	
	if( board[i][input]== '.' )
		empty= true ;
	else
		empty= false;

	return empty;
}
char getUserValue(){
	char value;	
		cin >> value;

	if( isupper( value ) )
		return tolower( value );

	return value;
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

	for(int i=0; i<size; ++i){
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
	int board_size=0;	
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
