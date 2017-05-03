#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept> // out_of_range
#include <cassert>
#include <algorithm>

namespace ls 
{

	using size_type = size_t;

	template <typename T>
	class MyIterator {

	private:
		T *m_ptr;

	public:

		MyIterator( T * ptr_ = nullptr ) 
			:m_ptr( ptr_ )
		{ /*empty*/ } 

		~MyIterator() = default;
		MyIterator( const MyIterator & ) = default;
		MyIterator & operator=( const MyIterator & ) = default;

		const T & operator* ( ) const
		{
			assert( m_ptr != nullptr );
			return *m_ptr;
		}
		
		// ++it;
		MyIterator & operator++ ( )
		{
			m_ptr++;
			return *this;
		}	

		// it++;
		MyIterator operator++ ( int a )
		{
			MyIterator temp = *this;
			m_ptr++;
			return temp;
		}

		// --it;
		MyIterator & operator-- ( )
		{
			m_ptr--;
			return *this;
		}  

		// it--;
		MyIterator operator-- ( int a )
		{
			MyIterator temp = *this;
			m_ptr--;
			return temp;
		}
		                                // 
		bool operator== ( const MyIterator & rhs ) const
		{
			return m_ptr == rhs.m_ptr;
		}

		bool operator!= ( const MyIterator & rhs ) const
		{
			return m_ptr != rhs.m_ptr;
		}

	};


	template <typename T>
	class vector {
		
	public:
		const static size_type DEFAULT_SIZE = 10;
		using iterator = MyIterator< T > ;
		using const_iterator = MyIterator< const T >;
		using const_reference = const T &;
		using reference = T &; 

	private:
		size_type m_len; //<! tamanho lógico do vetor
		size_type m_size; //<! tamanho físico atual
		T * m_data; //<! vetor dinâmico

	public:
		// [I] SPECIAL MEMBERS
		
		/**
		 * @brief      Construtor, se recebe um valor em sz, controi um vetor
		 *             do tamanho sz, se não, do tamanho DEFAULT_SIZE
		 * @param[in]  sz    Tamanho do vetor
		 */
		vector( size_type sz = DEFAULT_SIZE )
			: m_len(0)
			, m_size( sz )
			, m_data( new T[sz] )
		{
			//<! empty
		} 

		/**
		 * @brief      Destrutor
		 */
		~vector( )
		{
			delete [] m_data;
		}

		/**
		 * @brief      Constrói a lista com a cópia profunda do conteúdo de copy
		 * @param[in]  copy  Conteúdo a ser copiado
		 */
		vector( const vector & copy )
		{
			m_data = new T;
			*m_data = *copy.m_data;
		}	

		/**
		 * @brief      Constrói a lista com o conteúdo de other usando
		 *             semântica de movimento.
		 * @param[in]  other  Contéudo que se deseja criar no vetor
		 */
		vector( vector && other )
		{
			m_data = new T;
			m_data = other.m_data;
			other.m_data = nullptr;
		}

		// template < typename InputItr >
		// vector( InputItr first, InputItr last)
		// {
		// 	m_data = new T;
		// 	for (auto i(0); first != last; ++first, ++i)
		// 		m_data[i] = (*first);
		// 	shrink_to_fit();
		// }

		vector &operator= ( const vector & other )
		{
			m_len = other.m_len;
			m_size = other.m_size;

			for (auto i(0u); i < m_len; ++i )
				*(m_data+i) = *(other.m_data+i);

			return *this;
		}
		
		vector &operator= ( vector && other)
		{
			m_data = other.m_data;
			other.m_data = nullptr;	

			return *this;
		}

		// [II] ITERATORS
		iterator begin( void )
		{ return iterator ( &m_data[0] ); }

		iterator end( void )
		{ return iterator ( &m_data[m_len] ); }

		const_iterator cbegin( void ) const
		{ return const_iterator ( &m_data[0] ); }

		const_iterator cend( void ) const
		{ return const_iterator ( &m_data[m_len] ); }

		// [III] Capacity
		size_type size( void ) const
		{
			return m_len;
		}

		size_type capacity( void ) const
		{
			return m_size;
		}

		bool empty( void ) const
		{
			return m_len == 0;
		}

		bool full( void ) const
		{
			return m_len == m_size;
		}

		// [IV] Modifiers
		void clear( void )
		{
			m_len = 0;
		}

		void push_front( const_reference value )
		{
			if ( this->full() ) this->reserve();
			std::copy( m_data, m_data+m_len, m_data+1 );

			m_data[0] = value;
			m_len++;
		}

		void push_back( const_reference value )
		{
			if ( this->full() ) this->reserve();

			m_data[m_len++] = value;
		}

		void pop_back( void )
		{
			if ( this->empty() )
				throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");

			m_len--;
		}

		void pop_front( void )
		{
			if ( this->empty() )
				throw std::out_of_range("[pop_front()]: Cannot recover an element from an empty vector!");

			std::copy( m_data+1, m_data+m_len, m_data );
				
			m_len--;
		}

		iterator insert( iterator pos, const_reference value )
		{
			auto i = 0;
			auto cont = 0;
			
			while ( *pos != m_data[i] )
			{
				cont++;
				i++;
			}

			std::copy(&m_data[cont], &m_data[m_len], &m_data[cont+1]);
			m_data[cont] = value;
			m_len++;

			return pos;
		}

		template < typename InputItr >
		iterator insert( iterator pos, InputItr first, InputItr last)
		{
			auto i = 0;
			auto cont = 0;
			
			while ( *pos != m_data[i] )
			{
				cont++;
				i++;
			}
			auto temp = first;
			auto d(0);
			while ( *temp != *last )
			{
				d++;
				temp++;
			} 
			
			std::copy(&m_data[cont], &m_data[m_len], &m_data[cont+d]);

			for (/*empty*/; first != last; ++first, ++cont)
			{
				m_data[cont] = *first;
				m_len++;

			}

			return pos;

		}

		// iterator insert( iterator, std::initializer_list< value_type > );
		
		void reserve( void )
		{
			T * temp = new T[ m_size * 2 ];
			std::copy(m_data, m_data+m_len, temp);
			delete m_data;
			m_data = temp;
			m_size *= 2;
		}

		void shrink_to_fit( void )
		{
			m_size = m_len;
		}
		
		void assign( const_reference value)
		{
			if ( this->empty() )
				throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");

			for (auto i(0u); i <= m_len; ++i)
				*(m_data+i) = value;
		}

		void assign( std::initializer_list<T> value )
		{
			if ( this->empty() )
				throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");

			for (auto i(0u); i <= m_len; ++i)
				*(m_data+i) = value;
		}
		
		// template < typename InputItr >
		// void assign( InputItr, InputItr );

		// iterator erase( iterator, iterator );
		// iterator erase( iterator pos );

		// [V] Element access
		const_reference back( void ) const
		{
			if ( this->empty() )
				throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");

			return m_data[m_len];
		}

		const_reference front( void ) const
		{
			if ( this->empty() )
				throw std::out_of_range("[front()]: Cannot recover an element from an empty vector!");

			return m_data[0];
		}

		const_reference operator[]( size_type pos ) const
		{
			return m_data[pos];
		}

		reference operator[]( size_type pos )
		{
			return m_data[pos];
		}

		const_reference at( size_type pos ) const
		{
			if ( pos < 0 || pos > m_len )
				throw std::out_of_range("[at()]: índice inválido ");
				
			return m_data[pos];
		}

		reference at( size_type pos )
		{
			if ( pos < 0 || pos > m_len )
				throw std::out_of_range("[at()]: índice inválido ");
				
			return m_data[pos];
		}

		//pointer data( void );
		// const_reference data( void ) const;

		// [VI] Operators
		bool operator==( const vector & rhs ) const
		{
			if ( m_len != rhs.m_len ) return false;
			if ( m_size != rhs.m_size ) return false;

			for ( auto i(0u); i < m_len; i++ )
			{
				if (*(m_data+i) != *(rhs.m_data+i) ) return false;
			}

			return true;
		}
		
		bool operator!=( const vector & rhs ) const
		{
			if ( m_len != rhs.m_len ) return true;
			if ( m_size != rhs.m_size ) return true;

			for ( auto i(0u); i < m_len; i++ )
			{
				if (*(m_data+i) != *(rhs.m_data+i) ) return true;
			}

			return false;
		}

		// [VII] Friend functions.
		//friend std::ostream & operator<<( std::ostream & os_, const Vector<T> & v_ );
		// friend void swap( Vector<T> & first_, Vector<T> & second_ );
		// 
		void print () const 
		{
			std::cout << ">>> [ ";
			std::copy( &m_data[0], &m_data[m_len],
                       std::ostream_iterator< T >(std::cout, " ") );
			std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";

		}
	};

}

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