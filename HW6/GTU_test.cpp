//	BURCU SUVAK OZTURK
//  141044079

// ***** MAIN fonksiyonu oldukca uzun oldu cunku tum fonksiyonlarin burada test edilmesi istendi *****


// SET ve MAP depolama yapilari tasarlandi
// Bu yapilar template sinif tipinde tasarlandi boylece icine her tipte integer,
// double, string degisken depolanabildi
// Set ve Map siniflari icin bir template base sinif olusturuldu
// BASE sinifin icinde size, max_size, insert, erase, find, count, begin ve end fonksiyonlari 
// pure virtual member function olarak yazildi;
// Daha sonra bu fonksiyonlar SET ve MAP yapilari icin ayri ayri override edildi

// empty() : Container in ici bos ise true dolu is false return eder
// size() : Container in icinde barindirdigi eleman sayisini verir
// max_size() : Container in kapasitesini verir
// insert() : Eleman ekleme isini yapar
// erase() : Parametere olarak verilen elemani siler
// find() : Verilen elemanin Container icindeki yerinin iteratorunu return eder
// count() : Belirli bir elemanin Containe ricindeki miktarini return eder
// begin() : iteratoru Container in basina getirir ve iteratoru return eder
// end() : iteratoru Container in son elemanina getirir ve iteratoru return eder


// GTUIterator adinda bir iterator class yazildi
// Container uzeirnde gezinmeyi, belirli bir noktaya gidebilmeyi saglar


// SET ve MAP yapilari shared_ptr ile dinamik bir bicimde olusturuldu


// Ayrica SetIntersection adinda global template bir fonksiyon yazildi
// bu fonksiyonun gorevi iki adet SET in INTERSECTION ini return etmektir


// Son olarak insert fonksiyonu icinde eklenmek istenen eleman yok ise invalid_argument exception firlatildi
// ve bunun try catch blogu main icinde olusturuldu
// yakalanan hatanin bilgisi verildi
// ayni islem insert ve find fonksiyonlari icindede yapilabilirdi ancak tekrara girecegi icin yapilmadi



#include <iostream>
#include <memory>
#include <string>

#include "GTUSet.cpp"
#include "GTUSetBase.cpp"
#include "GTUMap.cpp"


using namespace std;

using GTUSetAndMap::GTUSetBase;
using GTUSetAndMap::GTUSet;
using GTUSetAndMap::GTUMap;

template<typename T>
std::shared_ptr< GTUSet<T> > setIntersection( GTUSet<T>& setA, GTUSet<T>& setB ){
	
	std::shared_ptr<GTUSet<T> > s_ptr;
	int size = 0;

	if ( setA.get_used() <= setB.get_used() )
		size = setA.get_used();
	else
		size = setB.get_used();

	s_ptr = shared_ptr<GTUSet<T> >(new GTUSet<T>[size],std::default_delete<GTUSet<T>[]>());

	if ( setA.get_used() <= setB.get_used() ){
		for (int i = 0; i < setA.get_used(); ++i)
		{	
			for (int k = 0; k < setB.get_used(); ++k)
			{
				if ( setA[i] == setB[k] )
				{
					s_ptr.get()[i] = setA[i];
					cout << setA[i] << " ";
				}
			}
			
			
		}
	}	

	else{
		for (int i = 0; i < setB.get_used(); ++i)
		{	
			for (int k = 0; k < setA.get_used(); ++k)
			{
				if ( setB[i] == setA[k] )
				{
					s_ptr.get()[i] = setB[i];
					cout << setB[i] << " ";
				}
			}
			
			
		}

	}

	cout << endl;	
		
	return s_ptr;
}

int main(){
	
	cout << "_________________________________\n" << endl;
	cout << "setA creating"	 << endl;
	GTUSet<int> set1(10);

	cout << endl;
	cout << "Is empty the set ?" << endl;

	if(set1.empty()){
		cout<<"Yes,set is empty." << endl;
		cout << "setA: ";
		set1.print();
	}

	else
		cout<<"No,set is not empty." << endl;

	cout << endl;

	
	try{

		set1.insert(1);
		set1.insert(3);
		set1.insert(0);
		set1.insert(7);
		set1.insert(4);
		set1.insert(9);

		cout << "_________________________________" << endl;
		cout << "setA: ";
		set1.print();
		cout << "\nINSERTING 3" << endl;
		set1.insert(3);



	}

	catch(const std::invalid_argument& ia){
		cerr << "\nexception: " << ia.what() << endl;
	}

	cout << "_________________________________" << endl;
	cout << "\n********* SET **********" << endl;
	cout << "\nsetA:" << endl;
	set1.print();
	
	cout << endl;

	cout << "\nDELETE 4 ";
	set1.erase(4);

	cout << endl;

	cout << "NEW SET:" << endl;
	set1.print();

	cout << "_________________________________" << endl;
	cout << endl;

	cout << "\nIterator setting to container's BEGIN..." << endl;
	
	GTUSet<int>::Iterator ptr = set1.begin();
	
	cout <<"ptr: " << *ptr << endl; 
	
	cout <<"\nIncrementing ptr..." << endl;
	++ ptr;
	cout <<"ptr: " << *ptr << endl;

	cout << "\nIterator setting to container's END..." << endl;
	ptr = set1.end();
	cout <<"ptr: " << *ptr << endl;

	cout <<"\nDecrementing ptr..." << endl;
	--ptr;
	cout <<"ptr: " << *ptr << endl;

	cout << "\nNew Iterator ptr_2 creating..." << endl;
	GTUSet<int>::Iterator ptr_2 = set1.begin();

	cout << "ptr_2: " << *ptr_2 << endl;
	cout << "\nIs ptr equal to ptr_2 ?" << endl;
	
	if ( ptr == ptr_2 )
		cout << "Yes,they are equal." << endl;
	else 
		cout << "No,they are not equal." << endl;

	GTUSet<int>::Iterator ptr_3 = ptr;

	cout << "ptr_3: " << *ptr_3 << endl;

	cout << "_________________________________" << endl;
	cout << "\nLOOKING FOR VALUE: 0\n";
	cout << "Searching..." << endl;
	ptr_3 = set1.find(0);
	cout << "ptr_3: " << (*ptr_3) << endl << endl;
		
	cout << "_________________________________\n" << endl;
	GTUSet<int> set2(3);
	set2.insert(3);
	set2.insert(5);
	set2.insert(9);

	cout<< "setA: ";
	set1.print();

	cout<< "setB: ";
	set2.print();
		
	cout << "INTERSECTION:  ";	
	setIntersection(set1,set2);
	cout << endl;

	cout << "_________________________________" << endl;
	
	GTUSet<double> set5(3);
	set5.insert(1.5);
	set5.insert(0.2);
	set5.insert(3.7);

	cout<< "\nsetA: ";
	set5.print();

	cout << "_________________________________" << endl;

	cout << "setA is CLEANING " << endl;

	set5.clear();
	cout << "setA: ";
	set5.print();
	cout << endl;

	cout << "_________________________________" << endl;
	GTUSet<string> set3(5);
	set3.insert("dark");
	set3.insert("purple");
	set3.insert("blue");
	set3.insert("pink");

	GTUSet<string> set4(3);
	set4.insert("white");
	set4.insert("blue");
	set4.insert("pink");
	
	cout << endl;
	cout<< "setA: ";
	set3.print();

	cout<< "setB: ";
	set4.print();
			
	cout << "_________________________________" << endl;
	cout << "********* MAP *********" << endl;

	GTUMap<int,int> map1(4);

	try{
		map1.insert(10,20);
		map1.insert(30,40);
		map1.insert(60,70);
	}

	catch(const std::invalid_argument& ia){
		cerr << "\nexception: " << ia.what() << endl;
	}

	map1.print();

	cout << "\nDELETE VALUE: 40" << endl;
	map1.erase(40);
	map1.print();

	cout << "_________________________________" << endl;
	GTUMap<string,string> map2(3);
	map2.insert("LONDON","ENGLAND");
	map2.insert("PARIS","FRANCE");
	map2.insert("NEW YORK","AMERICA");
	map2.print();
	cout << "\nDELETE VALUE: FRANCE\n" << endl;
	map2.erase("FRANCE	");
	map2.print();
	


	return 0;
}


