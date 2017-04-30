#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept> // out_of_range

namespace ls 
{
	using size_type = size_t;
	using iterator = MyIterator< T > 
	using const_iterator = MyIterator< const T >
	
	template <typename T>
	class vector
	{
		private:
			static const size_t DEFAULT_SIZE = 10;	

			size_type m_len; //<! tamanho lógico do vetor
			size_type m_size; //<! tamanho físico atual
			T * m_data; //<! vetor dinâmico
			
			
		public:
			//<! Construtor default
			vector( size_type sz = DEFAULT_SIZE )
				: m_len(0)
				, m_size( sz )
				, m_data( new T[sz] )

			{
				//<! empty
			}

			//<! Construtor com atribuição
			// vector( T *first, T *last )
			// {
			// 	m_len = std::distance(first, last)/sizeof(T);
			// 	m_size = m_len;
			// 	m_data = new T[m_size];
			// 	std::copy( first, last, m_data );
			// }

			//<! Destrutor
			~vector()
			{
				delete m_data;
			}	

			// Construtor Cópia
			vector( const vector & copy_ )
			{
				m_data = new T;
				*m_data = *copy_.m_data;
			}

			// Operador de atribuição cópia
			vector & operator=( const vector & rhs )
			{
				return *this;
			}

			T & at( size_type pos )
			{
				if ( pos < 0 || pos > m_len )
					throw std::out_of_range("[at()]: índice inválido ");
				
				return m_data[pos];
			}

			T & operator[]( size_type pos)
			{
				return m_data[pos];
			}

			// bool operator==( const vector& rhs )
			// {
			// 	bool veri = false;
				
			// 	if ( m_size == rhs.m_size ) veri = true;
			// 	else return false;
			// 	if ( m_len == rhs.m_len ) veri = true;
			// 	else return false;
				
			// 	for ( auto i(0ul); i < m_len; ++i )
			// 	{
			// 		if ( *(m_data+i) == *(rhs.m_data+i) )
			// 			veri = true;
			// 		else return false;
			// 	}

			// 	return veri;
				
			// }

			//<! retorna a quantidade de elementos no vetor
			size_type size() const
			{
				return m_len;
			}

			//<! remove os elementos no vetor
			void clear () 
			{
				m_len = 0;
			}

			//<! verifica se o vetor está vazio
			bool empty() const 
			{
				return m_len == 0;
			}

			bool full() const 
			{
				return m_len == m_size;
			}

			void shrink_to_fit()
			{
				m_size = m_len;
			}

		private:

			void reserve () 
			{
				T * temp = new T[ m_size * 2 ];
				std::copy(m_data, m_data+m_len, temp);
				delete m_data;
				m_data = temp;
				m_size *= 2;
			}

		public:

			void push_back ( const T & value )
			{
				if ( this->full() ) this->reserve();

				m_data[m_len++] = value;
			}

			void push_front ( const T & value )
			{
				if ( this->full() ) this->reserve();
				std::copy( m_data, m_data+m_len, m_data+1 );

				m_data[0] = value;
				m_len++;
			}

			T pop_back()
			{
				if ( this->empty() )
					throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");

				return m_data[--m_len];
			}

			T pop_front()
			{
				if ( this->empty() )
					throw std::out_of_range("[pop_front()]: Cannot recover an element from an empty vector!");

				std::copy( m_data+1, m_data+m_len, m_data );
				
				return m_data[--m_len];
			}

			const T & back () const
			{
				if ( this->empty() )
					throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");

				return m_data[m_len];
			}

			const T & front () const
			{
				if ( this->empty() )
					throw std::out_of_range("[front()]: Cannot recover an element from an empty vector!");

				return m_data[0];
			}

			void assign( const T & value )
			{
				if ( this->empty() )
					throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");

				for (auto i(0u); i <= m_len; ++i)
					*(m_data+i) = value;
			}

			size_type capacity() const
			{
				return m_size;
			}

			void print () const 
			{
				std::cout << ">>> [ ";
				std::copy( &m_data[0], &m_data[m_len],
                           std::ostream_iterator< T >(std::cout, " ") );
				std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";

			}

			//<! Iteradores
			iterator begin()
			{
				return &m_data[0];
			}

	}; 
}


int main () {

	ls::vector <int> v;
	
	int aux;
	std::cout << "Entre com números...\n";
	while ( std::cin >> aux && aux != 404 )
	{
		v.push_front(aux);
	}

	v.print();

	std::cout << ">> Testando o pop_back\n ";
	v.pop_back();
	v.print();

	std::cout << ">> Testando o pop_front\n ";
	v.pop_front();
	v.print();

	std::cout << ">> Testando o back: " << v.back() << std::endl;
	std::cout << ">> Testando o front: " << v.front() << std::endl;
	
	std::cout << ">> Testando o assign\n ";
	v.assign(10);
	v.print();

	std::cout << ">> Testando o [] " << v[2] << "\n";
	std::cout << ">> Testando o at " << v.at(2) << "\n";
	std::cout << ">> Testando o capacity " << v.capacity() << "\n";
	
	std::cout << ">> Testando o shrink_to_fit\n ";
	v.shrink_to_fit();
	v.print();

	std::cout << "Entre com números...\n";
	while ( std::cin >> aux && aux != 404 )
	{
		v.push_back(aux);
	}

	v.print();

	//testando o begin
	std::cout << "primeiro da lista: " << *(v.begin()) << std::endl;

	// std::cout << "testando Construtor com atribuição \n";
	// ls::vector <int> v2(&v[0], &v[v.capacity()]);
	// std::cout << "deve ser igual a v: \n";
	// v2.print();


	
	// std::cout << "testando == \n";
	// v2.print();
	// if ( v == v2 ) std::cout << "Deu Certo!\n";
	// else std::cout << "Deu Ruim!\n";

	return EXIT_SUCCESS;
}