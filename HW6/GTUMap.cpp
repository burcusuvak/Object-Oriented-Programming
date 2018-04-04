#include <iostream>

#include "GTUMap.h"
using std::pair;
using namespace std;

namespace GTUSetAndMap{

	template<class K,class V>
	GTUMap<K,V>::GTUMap(int container_size)
				: capacity(container_size), used(0)
	{
		mpair = new pair<K,V>[capacity];
	}

	template<class K,class V>
	V& GTUMap<K,V>::operator[]( const K& k ){
		
		int found = 0;
		for (int i = 0; i < this->get_used(); ++i)
		{
			if (mpair[i].first == k )
				found = 1;
		}

		if( found == 1 )
			return mpair[k].second;
		else
			cout << "No element..." << endl;

	}

	template<class K,class V>
	void GTUMap<K,V>::set_used(int choice){
		if(choice == 1)
			++used;
		else if(choice == 2)
			--used;
	}

	template<class K,class V>
	int GTUMap<K,V>::max_size(){
		return this->get_capacity();
	}

	template<class K,class V>
	bool GTUMap<K,V>::empty(){

		if ( this->get_used() ){
			cout << "It is empty" << endl;
			return true;
		}
		else
			return false;
	}	

	template<class K,class V>
	void GTUMap<K,V>::insert(K theKey,V theValue){
		
		int found = 0;

		for (int i = 0; i < this->get_used(); ++i)
		{
			if ( mpair[i].first == theKey )
				found = 1;
		}
		
		if( !found ){
			mpair[this->get_used()].first = theKey;
			mpair[this->get_used()].second = theValue;
			this->set_used(1);
		}
	}

	template<class K,class V>
	void GTUMap<K,V>::erase(V theValue){

		int size;
		pair<K,V> *arr;
		for ( int i = 0; i < this->get_used() ; ++i ){

			if ( mpair[i].second == theValue )
			{	
				size = this->get_used() - (i+1);
				arr = new pair<K,V>[size];

				for (int j = i+1, k = 0; j < this->get_used(); ++j, ++k)
				{
					arr[k].first = mpair[j].first;
					arr[k].second = mpair[j].second;
				}

				for (int j = 0, k = i; j < size; ++j, ++k){
					mpair[k].first = arr[j].first;
					mpair[k].second = arr[j].second;
				}

				this->set_used(2);
			}

		}


	}

	template<class K,class V>
	void GTUMap<K,V>::print(){

		for (int i = 0; i < this->get_used(); ++i)		
			cout << "map[" << mpair[i].first << "] = "<< mpair[i].second << endl;
	}




}