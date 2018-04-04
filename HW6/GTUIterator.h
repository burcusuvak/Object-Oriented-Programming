#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <memory>

namespace GTUStAndMap{

	template<class T>
	class GTUIterator
	{

	public:
		GTUIterator();

	private:

		std::shared_ptr<T> *iter;
			
	};

}

#endif