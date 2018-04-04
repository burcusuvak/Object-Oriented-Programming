#include <iostream>
#include "GTUSet.h"
#include <memory>
#include <stdexcept>

using namespace std;

namespace GTUSetAndMap{

	template<class T>
	GTUSet<T>::GTUSet()
			: GTUSetBase<T>()
	{	
		container = shared_ptr<T>(new T[this->get_capacity()],std::default_delete<T[]>());
	}		

	template<class T>
	GTUSet<T>::GTUSet( int container_size )
			: GTUSetBase<T>( container_size )
	{
		container = shared_ptr<T>(new T[ this->get_capacity()],std::default_delete<T[]>());
	}

	template<class T>
	T& GTUSet<T>::operator[](int index){

		if ( index >= this->get_used() ){
			cout << "illegal index value" << endl;
			exit(1);
		}
		else
			return container.get()[index];
	}

	template<class T>		
	bool GTUSet<T>::empty(){

		if( this->get_used() == 0 )
			return true;
		else
			return false;
	}


	template<class T>
	void GTUSet<T>::insert( T theValue ){
		
		int found = 0;

		for (int i = 0; i < this->get_used(); ++i)
		{
			if( theValue == container.get()[i] )
				found = 1;

		}
		
		if( !found ){
			container.get()[this->get_used() ] = theValue;
			this->set_used(1);
		}
		else
			throw std::invalid_argument("The element is already in the set.\n");
			

		this->sort();
	}

	template<class T>
	void GTUSet<T>::sort(){

		for ( int i = 0; i < this->get_used() - 1 ; ++i )
		{	
			for (int j = i+1; j < this->get_used(); ++j)
			{	
				if ( container.get()[j] < container.get()[i]  ){
					T temp = container.get()[i];
					container.get()[i] = container.get()[j];
					container.get()[j] = temp;
				}									
			}
		}
	}

	template<class T>
	void GTUSet<T>::erase(T theValue){
		int size;
		T *arr;
		for ( int i = 0; i < this->get_used() ; ++i ){

			if ( container.get()[i] == theValue )
			{	
				size = this->get_used() - (i+1);
				arr = new T[size];

				for (int j = i+1, k = 0; j < this->get_used(); ++j, ++k)
				{
					arr[k] = container.get()[j];
				}

				for (int j = 0, k = i; j < size; ++j, ++k)				
					container.get()[k] = arr[j];

				this->set_used(2);
			}

		}
	}

	template<class T>
	void GTUSet<T>::print(){

		for (int i = 0; i < this->get_used(); ++i)
			cout << container.get()[i] << "  ";

		cout << endl;

	}

	template<class T>
	T* GTUSet<T>::begin(){
		T* iter;
		iter = &(*container);
		return iter;
	}		


	template<class T>
	T* GTUSet<T>::end(){
		T* iter;
		iter = &(container.get()[this->get_used()-1]);
		return iter;
	}

	template<class T>
	int GTUSet<T>::size(){	return this->get_used();	}

	template<class T>
	int GTUSet<T>::max_size(){	return this->get_capacity();	}

	template<class T>
	int GTUSet<T>::count(T theValue){

		int count = 0;

		for (int i = 0; i < this->get_used(); ++i)
		{
			if( theValue == container.get()[i] )
				++count;
		}

		return count;
	}

	template<class T>
	T* GTUSet<T>::find(T theValue){

		T* iter;
		int found = 0;

		for (int i = 0; i < this->get_used(); ++i)
		{
			if( theValue == container.get()[i] ){
				iter = &(container.get()[i]);
				found = 1;
			}				
		}

		if (found == 1)
			return iter;
	}
	
	template<class T>
	void GTUSet<T>::clear(){

		this->set_used(0);

	}


}