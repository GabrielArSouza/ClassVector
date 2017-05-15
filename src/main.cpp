#include "vector.h"

int main ()
{
	
	{

		ls::vector<int> v(20);
		ls::vector<int>::iterator it = v.begin();

		for ( auto i(0); i < 10; ++i )
			v.push_back( i+1 );

		v.print();

		std::cout << ">>> begin() = " << *it << "\n";
		++it;
		std::cout << ">>> posição 2: " << *it << "\n";
		it++;
		std::cout << ">>> posição 3: " << *it << "\n";
		--it;
		std::cout << ">>> posição 2: " << *it << "\n";
		it--;
		std::cout << ">>> posição 1: " << *it << "\n";

		
		ls::vector<int> v2(20);
		ls::vector<int>::iterator it2 = v2.begin();

		for ( auto i(100); i < 1000; i+=100 )
			v2.push_back( i );	

		std::cout << ">>Antes: \n";
		v2.print();

		v2.insert(++it2, v.begin(), v.end());
		std::cout << ">>Depois: \n";
		v2.print();

					
	}

	return EXIT_SUCCESS;
}
