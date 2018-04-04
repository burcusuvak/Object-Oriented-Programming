#ifndef GTUSET_H
#define GTUSET_H

#include <memory>
#include "GTUSetBase.h"

namespace GTUSetAndMap{

	template<class T>
	class GTUSet : public GTUSetBase<T>
	{
	public:
		typedef GTUIterator<T> Iterator;

		GTUSet();
		GTUSet( int container_size );

		T& operator[](int index);

		bool empty();
		void insert( T theValue );
		void sort();
		void erase( T theValue );
		void print();
		
		T* begin();
		T* end();

		int size();
		int max_size();
		int count(T theValue);
		T* find(T theValue);
		void clear();

	
	private:

	std::shared_ptr<T> container;

	};

}


#endif
