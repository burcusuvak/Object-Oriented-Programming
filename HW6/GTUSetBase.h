#ifndef GTUSETBASE_H
#define GTUSETBASE_H
#include <iostream>
#include <memory>


namespace GTUSetAndMap{

	template<class T>
	class GTUIterator
	{

	public:
	
		GTUIterator( T* initial )
					:iter(initial)
		{ }			

		GTUIterator operator ++ (){
			iter = iter + 1;
			return iter;
		}

		GTUIterator operator -- (){ 
			iter = iter - 1; 
			return iter; 
		}

		const T operator *()const{	return *iter;	}

		bool operator == (const GTUIterator& rightSide) const{
			
			return ( iter == rightSide.iter );			
		}

		const T* operator ->(){

			return &iter;
		}

		GTUIterator& operator = (const GTUIterator& rightSide){

			iter = rightSide.iter;
		}

	private:

		T* iter;	
	};

	template<class T>
	class GTUSetBase{
	
	public:

		GTUSetBase();
		GTUSetBase( int container_size );

		int get_capacity()const{	return capacity;	}
		int get_used()const{		return used;	}

		void set_used(int choice);


		virtual bool empty() = 0;
		virtual void insert( T theValue ) = 0;
		virtual T* begin() = 0;
		virtual T* end() = 0;
		
		virtual void erase( T theValue ) = 0;
		virtual int size() = 0;
		virtual int max_size() = 0;
		virtual int count(T theValue) = 0;
		virtual T* find( T theValue ) = 0;
		virtual void clear() = 0;
	

	
	private:

		int capacity;
		int used;

	};

	
}

#endif