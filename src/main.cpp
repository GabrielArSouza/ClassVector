#include <cassert>
#include "vector.h"


int main ()
{
	
	//testando construtores
	{
		//vazios
		ls::vector<int> v1;
		ls::vector<char> v2;
		ls::vector<std::string> v3;
		ls::vector<char> v4;

		//contagem
		ls::vector<int> v5(20);
		assert(v5.capacity() == 20);

		//cópia
		ls::vector<int> v6(v5);
		
		v1.push_back(1);
		v1.push_back(2);
		
		ls::vector<int> v7(v1.begin(), v1.end());
		assert (v7[0] == 1);
		assert (v7[1] == 2);

		ls::vector<int> v8 {1, 2, 3};
		assert (v8[0] == 1);
		assert (v8[1] == 2);
		assert (v8[2] == 3);

		ls::vector<std::string> v10 {"ga", "bri", "el"};
		assert (v10[0] == "ga");
		assert (v10[1] == "bri");
		assert (v10[2] == "el");

		ls::vector<int> v9;
		v9 = v7;
		assert (v9[0] == 1);
		assert (v9[1] == 2);
		
	}

	//testando iteradores
	{
		ls::vector<int> v {1, 2, 3};
		assert( v.begin() == &v[0]);
		assert( v.cbegin() == &v[0]);

	}

	//testando capacity
	{
		ls::vector<int> vv = {12, 13, 14};
		ls::vector<char> v1;

		assert( vv.size() == 3 );
		assert( v1.size() == 0 );
		assert( vv.capacity() == 3 );
		assert( v1.capacity() == 10 );
		assert( vv.empty() == false );
		assert( v1.empty() == true );
		assert( vv.full() == true );
		assert( v1.full() == false );

	}

	//testando modificadores
	{
		ls::vector<int> v {1, 2, 3};

		assert( v.empty() == false );
		v.clear();
		assert( v.empty() == true );

		ls::vector<int> v1 {2, 3, 4};
		v1.push_front(1);
		assert(v1[0] == 1);

		v1.push_back(5);
		auto aux = v1.size()-1;
		assert(v1[aux] == 5);

		ls::vector<char> v2 {'a', 'b', 'c'};
		v2.push_front('d');
		assert(v2[0] == 'd');

		v2.push_back('e');
		auto aux1 = v2.size()-1;
		assert(v2[aux1] == 'e');
		
		v2.pop_back();
		aux1 = v2.size()-1;
		assert(v2[aux1] == 'c');

		v2.pop_front();
		assert(v2[0] == 'a');

		v2.insert( v2.begin(), 'h');
		assert(v2[0] == 'h');

		v2.insert( &v2[2], 'g');
		assert(v2[2] == 'g');

		ls::vector<int> auxvec {10, 11, 12, 13, 14, 15, 16, 17};

		ls::vector<int> v3 {5, 6, 7, 8, 9};
		v3.insert(&v3[2], &auxvec[0], &auxvec[8]);
		v3.print();

		ls::vector<int> v4 {1, 2, 3, 4, 5};
		v4.insert(&v4[5], &auxvec[0], &auxvec[8]);
		v4.print();

		ls::vector<char> v5 {'a', 'b', 'c', 'd'};
		std::cout << "BEFORE: ";
		v5.print();
		v5.insert(&v5[0], {'e', 'f', 'g'});
		std::cout << "AFTER: ";
		v5.print();

		v5.shrink_to_fit();
		assert (v5.size() == v5.capacity());
		
		auxvec.assign(2);
		for ( auto i(auxvec.begin()); i != auxvec.end(); ++i)
			assert( *i == 2);

		ls::vector<int> v6 {1, 2, 3, 4, 5};
		std::cout << "BEFORE: ";
		v6.print();
		v6.assign({12, 13});
		std::cout << "AFTER: ";
		v6.print();
	}
	//teste assign
	{
		ls::vector<int> v6 {1, 2, 3, 4, 5};
		std::cout << "BEFORE: ";
		v6.print();
		v6.assign(&v6[0], &v6[3]);
		std::cout << "AFTER: ";
		v6.print();
	}
	//teste erase
	{
		ls::vector<int> v6 {1, 2, 3, 4, 5};
		std::cout << "BEFORE ERASE: ";
		v6.print();
		v6.erase(v6.begin(), v6.end());
		std::cout << "AFTER: ";
		v6.print();
	}
	//teste erase
	// {
	// 	ls::vector<int> v6 {1, 2, 3, 4, 5};
	// 	std::cout << "BEFORE ERASE: ";
	// 	v6.print();
	// 	v6.erase(v6.begin());
	// 	std::cout << "AFTER: ";
	// 	v6.print();
	// }



	return EXIT_SUCCESS;
}
