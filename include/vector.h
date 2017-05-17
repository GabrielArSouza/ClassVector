#ifndef _VECTOR_H_
#define _VECTOR_H_

	#include <iostream> //std::cout 
	#include <string> //std::string
	#include <iterator> 
	#include <stdexcept> // out_of_range
	#include <cassert> //assert
	#include <algorithm> //std::copy

	namespace ls 
	{
		//<! formato dos sizes 
		using size_type = size_t;

		/**
		 * @brief      Classe do iterador usado na classe vector
		 *
		 * @tparam     T     parâmetro para o template
		 */
		template <typename T>
		class MyIterator {

			private:
				T *m_ptr; //<! poteiro que representa o iterado

			public:

				/**
				 * @brief      Construtor Default
				 *
				 * @param      ptr_  O iterador
				 */
				MyIterator( T * ptr_ = nullptr ) 
					:m_ptr( ptr_ )
				{ /*empty*/ } 

				/**
				 * @brief      Destroi o objeto.
				 */
				~MyIterator() = default;

				/**
				 * @brief      construtor cópia
				 *
				 * @param[in]  recebe um iterador e constroi a cópia default
				 */
				MyIterator( const MyIterator & ) = default;

				/**
				 * @brief      Utiliza o operador =
				 *
				 * @param[in]  recebe um iterador
				 *
				 * @return     faz a atribuição default para o operador =
				 */
				MyIterator & operator=( const MyIterator & ) = default;

				/**
				 * @brief      Acessa o valor que o ponteiro guarda, equivalente ao
				 *             usar o * sobre um iterador para saber o valor salvo 
				 *             naquele endereço de memória.
				 *
				 * @return     o valor salvo no endereço de memória do ponteiro
				 */
				T & operator* ( );
				
				/**
				 * @brief      Avança para o próximo endereço de memória, equivalente ao
				 *             usar o ++it para acessar o próximo do vector
				 *
				 * @return     O iterador para o próximo espaço de memória usado pelo vector
				 */
				MyIterator & operator++ ( );	

				/**
				 * @brief      Avança para o próximo endereço de memória, equivalente ao
				 *             usar o it++ para acessar o próximo do vector
				 *
				 * @param[in]  a     default, padrão para esse tipo de implementação
				 *
				 * @return     O iterador para o próximo espaço de memória usado pelo vector
				 */
				MyIterator operator++ ( int a );		

				/**
				 * @brief      retorna para o endereço de memória anterior ao atual equivalen
				 *             te ao usar o --it para acessar um elemento antes
				 *
				 * @return     O iterador para o espaço de memória anterior ao atual
				 */
				MyIterator & operator-- ( ); 

				/**
				 * @brief      retorna para o endereço de memória anterior ao atual equivalen
				 *             te ao usar o it-- para acessar um elemento antes
				 *
				 * @param[in]  a     default, padrão para esse tipo de implementação
				 *
				 * @return     O iterador para o espaço de memória anterior ao atual
				 */
				MyIterator operator-- ( int a );

				/**
				 * @brief      compara se dois iteradores são iguais
				 *
				 * @param[in]  rhs   o iterador que se deseja comparar
				 *
				 * @return     Sim, caso sejam iguais, não se forem diferentes
				 */
				bool operator== ( const MyIterator & rhs ) const;

				/**
				 * @brief      Verifica de dois iteradores são diferentes
				 *
				 * @param[in]  rhs   o iterador que se deseja comparar
				 *
				 * @return     sim, caso sejam diferentes, não se forem iguais
				 */
				bool operator!= ( const MyIterator & rhs ) const;;

		};

		template <typename T>
		class vector {
						
		public:
			const static size_type DEFAULT_SIZE = 10;
			using iterator = MyIterator<T> ;
			using const_iterator = MyIterator<const T> ;
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

			T * data( void );
			const T * data( void ) const;

			// [VI] Operators
			bool operator==( const vector & rhs ) const;
			
			bool operator!=( const vector & rhs ) const;

			void print () const;

	};

	
	#include "vector.inl"
} 

#endif