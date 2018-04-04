#include <iostream>

#include "GTUSetBase.h"

namespace GTUSetAndMap{

	template<class T>
	GTUSetBase<T>::GTUSetBase()
				: capacity(50), used(0)
	{
		// empty
	}	

	template<class T>
	GTUSetBase<T>::GTUSetBase( int container_size )
				: capacity( container_size ), used(0)
	{
		// empty
	}

	template<class T>
	void GTUSetBase<T>::set_used(int choice){
		if(choice == 1)
			++used;
		else if(choice == 2)
			--used;
		else if( choice == 0)
			used = 0;
	}


}