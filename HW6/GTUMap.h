#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.h"

using std::pair;
namespace GTUSetAndMap{

	template<class K,class V>
	class GTUMap: public GTUSet< std::pair<K,V> >
	{
	public:
		GTUMap(int container_size);
		V& operator[] ( const K& k );
		int get_used(){		return used;	}
		int get_capacity(){		return capacity;	}
		void set_used(int choice);

		int max_size();
		int size() const {	return used;	}
		bool empty();
		void insert(K theKey, V theValue);
		void erase(V theValue);
		void print();

	private:
		pair<K,V> *mpair;
		int capacity;
		int used;

	};

}

#endif