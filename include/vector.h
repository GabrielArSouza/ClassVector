#ifndef _VECTOR_H_
#define _VECTOR_H_

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
		class vector {

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

				T & operator* ( );
				
				// ++it;
				MyIterator & operator++ ( );	

				// it++;
				MyIterator operator++ ( int a );		

				// --it;
				MyIterator & operator-- ( ); 

				// it--;
				MyIterator operator-- ( int a );

				// 
				bool operator== ( const MyIterator & rhs ) const;

				bool operator!= ( const MyIterator & rhs ) const;;

			};
			
		public:
			const static size_type DEFAULT_SIZE = 10;
			using iterator = MyIterator ;
			using const_iterator = MyIterator const ;
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
			 * @brief      Constrói a lista com a cópia do conteúdo de copy
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

			template < typename InputItr >
			vector( InputItr first, InputItr last)
			{
				int cont = 0;
				auto f = first;
				while ( f != last )
				{
					f++;
					cont++;
				}
				//construindo vector
				m_data = new T[cont];
				m_size = cont;
				m_len = 0;

				int aux = 0;
				for (/*empty*/; first != last ; ++first, ++aux)
				{
					m_data[aux] = *first;
					m_len++;

				}
			}

			vector( std::initializer_list<T> ilist )
			{
				auto size = ilist.size();
				m_data = new T[size];
				m_size = size;
				m_len = 0;
				
				int aux = 0;
				for (const T * i = ilist.begin(); i != ilist.end() ; ++i, ++aux)
				{
					m_data[aux] = *i;
					m_len++;

				}
			}

			vector &operator= ( const vector & other );
			
			vector &operator= ( vector && other);

			// [II] ITERATORS
			iterator begin( void );

			iterator end( void );

			const_iterator cbegin( void ) const;

			const_iterator cend( void ) const;

			// [III] Capacity
			size_type size( void ) const;

			size_type capacity( void ) const;

			bool empty( void ) const;

			bool full( void ) const;

			// [IV] Modifiers
			void clear( void );

			void push_front( const_reference value );

			void push_back( const_reference value );

			void pop_back( void );

			void pop_front( void );

			iterator insert( iterator pos, const_reference value );

			template < typename InputItr >
			iterator insert( iterator pos, InputItr first, InputItr last);

			iterator insert( iterator, std::initializer_list< T > );
			
			void reserve( void );

			void shrink_to_fit( void );
			
			void assign( const_reference value);
			
			void assign( std::initializer_list<T> value );
			
			template < typename InputItr >
			void assign( InputItr, InputItr );

			iterator erase( iterator, iterator );
			iterator erase( iterator pos );

			// [V] Element access
			const_reference back( void ) const;

			const_reference front( void ) const;

			const_reference operator[]( size_type pos ) const;
			
			reference operator[]( size_type pos );

			const_reference at( size_type pos ) const;

			reference at( size_type pos );

			//pointer data( void );
			// const_reference data( void ) const;

			// [VI] Operators
			bool operator==( const vector & rhs ) const;
			
			bool operator!=( const vector & rhs ) const;

			// [VII] Friend functions.
			/*uma função, ele não é um método*/
			//friend std::ostream & operator<<( std::ostream & os_, const Vector<T> & v_ );
			// friend void swap( Vector<T> & first_, Vector<T> & second_ );
			// 
			void print () const;

	};

	
	#include "vector.inl"
} 

#endif