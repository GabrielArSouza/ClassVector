/**
 * @file vector.h
 * @author Gabriel Araújo de Souza
 * @date 17 May 2017
 * @brief Arquivo contendo as definições das classes vector e MyIterator
 */

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

		/**
		 * @brief      Classe Vector
		 *
		 * @tparam     T     template
		 */
		template <typename T>
		class vector {
						
		public:
			/**
			 * Definições para facilitar a implementação
			 */
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
				m_len = copy.m_len;
				m_size = copy.m_size;
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
				m_len = other.m_len;
				m_size = other.m_size;
				other.m_data = nullptr;
			}

			/**
			 * @brief      Constrói um vector com o tamanho e elementos presentes
			 *             no intervalo fornecido
			 *
			 * @param[in]  first     Inicio do intervalo
			 * @param[in]  last      Final do intervalo
			 *
			 * @tparam     InputItr  para tipos de intervalo genérico
			 */
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

			/**
			 * @brief      Constrói um vector a partir de uma lista fornecida
			 *
			 * @param[in]  ilist  Lista fornecida
			 */
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

			/**
			 * @brief      Atribui o operador '=' para a construção de um vector
			 *             igualmente a outro fornecido sem modificá-lo
			 *
			 * @param[in]  other  Vector que se deseja clonar
			 *
			 * @return     Um novo vector com as mesmas características do
			 *             fornecido
			 */
			vector &operator= ( const vector & other );
			
			/**
			 * @brief      Atribui o operador '=' para a construção de um vector
			 *             igualmente a outro fornecido com lógica de movimento
			 *
			 * @param[in]  other  Vector que se deseja clonar
			 *
			 * @return     Um novo vector com as mesmas características do
			 *             fornecido
			 */
			vector &operator= ( vector && other);

			// [II] ITERATORS
			
			/**
			 * @brief      Fornece um ponteiro para o primeiro elemento do vector
			 *
			 * @return     Um iterador para o primeiro elemento do vector
			 */
			iterator begin( void );

			/**
			 * @brief      Fornece um ponteiro para o espaço depois do último 
			 *             elemento válido
			 *
			 * @return     Um iterador para o próximo espeço logo após o ultimo
			 *             elemento válido do vetor
			 */
			iterator end( void );

			/**
			 * @brief      Fornece um ponteiro constante para o primeiro elemento
			 *             do vector
			 *
			 * @return     Um iterador constante para o primeiro elemento do vector
			 */
			const_iterator cbegin( void ) const;

			/**
			 * @brief      Fornece um ponteiro constante para o espaço depois do último 
			 *             elemento válido
			 *
			 * @return     Um iterador constante para o próximo espeço, logo após o ultimo
			 *             elemento válido do vetor
			 */
			const_iterator cend( void ) const;

			// [III] Capacity
			
			/**
			 * @brief      Fornece a quantidade de elemento do vetor
			 *
			 * @return     A quantidade de elementos no vetor
			 */
			size_type size( void ) const;

			/**
			 * @brief      Fornece a capacidade máxima atual de elementos que 
			 *             cabem no vector
			 *
			 * @return     A atual capacidade máxima do vector
			 */
			size_type capacity( void ) const;

			/**
			 * @brief      Verifica se o vector está vazio
			 *
			 * @return     Sim, caso o vector esteja vazio, não, caso contrário.
			 */
			bool empty( void ) const;

			/**
			 * @brief      Verifica se o vector está lotado
			 *
			 * @return     Sim, caso o vector esteja na sua capacidade máxima,
			 *             não, caso contrário
			 */
			bool full( void ) const;

			// [IV] Modifiers
			
			/**
			 * @brief      Limpa o vector, removendo todos seus elementos
			 */
			void clear( void );

			/**
			 * @brief      Insere um elemento no inicio do vector
			 *
			 * @param[in]  value  o valor que se dejesa inserir
			 */
			void push_front( const_reference value );

			/**
			 * @brief      Insere um elemento no final do vector
			 *
			 * @param[in]  value  o valor que se deseja inserir
			 */
			void push_back( const_reference value );

			/**
			 * @brief      Remove o ultimo elemento do vector
			 */
			void pop_back( void );

			/**
			 * @brief      Remove o primeiro elemento do vector
			 */
			void pop_front( void );

			/**
			 * @brief      Insere um elemento na posição do vector informada
			 *
			 * @param[in]  pos    A posição que se deseja inserir o elemento
			 * @param[in]  value  O valor que se deseja inserir
			 *
			 * @return     Um iterado para a posição do elemento inserido
			 */
			iterator insert( iterator pos, const_reference value );

			/**
			 * @brief      Insere um intervalo de elementos a partir de uma 
			 *             posição informada
			 *
			 * @param[in]  pos       a posição que se deseja inserir o elementos
			 * @param[in]  first     O inicío do intervalo de elementos
			 * @param[in]  last      o final do intervalo de elementos
			 *
			 * @tparam     InputItr  Implementação para intervalos genéricos
			 *
			 * @return     Um iterador para o inicio do intervalo inserido
			 */
			template < typename InputItr >
			iterator insert( iterator pos, InputItr first, InputItr last);

			/**
			 * @brief      Insere uma lista de elementos a partir de uma 
			 *             posição informada
			 *
			 * @param[in]  pos    o local onde deve se inserir a lista
			 * @param[in]  ilist  A lista que se dejesa inserir
			 *
			 * @return     Um iterado para a posição inserida
			 */
			iterator insert( iterator pos, std::initializer_list< T > ilist );
			
			/**
			 * @brief      Dobra a capacidade atual do vector
			 */
			void reserve( void );

			/**
			 * @brief      Remove os espaços não utilizados do vector
			 */
			void shrink_to_fit( void );
			
			/**
			 * @brief      Transforma todos os elementos do vector em um 
			 *             valor fornecido
			 *
			 * @param[in]  value  o valor
			 */
			void assign( const_reference value);
			
			/**
			 * @brief      transforma todos os elementos do vector em repetições
			 *             de valores presentes em uma lista fornecida
			 *
			 * @param[in]  value  a lista com elementos para atribuir
			 */
			void assign( std::initializer_list<T> value );
			
			/**
			 * @brief      Tranforma todos os elementos do vector em repetições
			 *             de elementos presentes em um intervalo fechado-aberto fornecido
			 *
			 * @param[in]  first     O inicio do intervalo
			 * @param[in]  last      final do intervalo ( aberto )
			 *
			 * @tparam     InputItr  Implementação para tipos de intervalo genérico
			 */
			template < typename InputItr >
			void assign( InputItr first, InputItr last);

			/**
			 * @brief      Remove um intervalo fechado-aberto do vector
			 *
			 * @param[in]  first  incício do intervalo
			 * @param[in]  last   fim do intervalo
			 *
			 * @return     o iterador para o ultimo elemento apagado.
			 */
			iterator erase( iterator first, iterator last );

			/**
			 * @brief      Remove um elemento do vector
			 *
			 * @param[in]  pos   A posição do elemento que se deseja remover
			 *
			 * @return     o iterado para o o final da lista
			 */
			iterator erase( iterator pos );

			// [V] Element access
			
			/**
			 * @brief      Acessa o ultimo elemento do vector
			 *
			 * @return     O ultimo elemento do vector
			 */
			const_reference back( void ) const;

			/**
			 * @brief      Acessa o primeiro elemento do vector
			 *
			 * @return     O primeiro elemento do vector
			 */
			const_reference front( void ) const;

			/**
			 * @brief      Atribui o siginificado do operador [], que acessa
			 *             o valor na posição do vector fornecida nos [].
			 *
			 * @param[in]  pos   A posição informada
			 *
			 * @return     O objeto constante presente na posição informada
			 */
			const_reference operator[]( size_type pos ) const;
			
			/**
			 * @brief      Atribui o siginificado do operador [], que acessa
			 *             o valor na posição do vector fornecida nos [].
			 *
			 * @param[in]  pos   A posição informada
			 *
			 * @return     O objeto presente na posição informada
			 */
			reference operator[]( size_type pos );

			/**
			 * @brief      Acessa o elemento na posição informada
			 *
			 * @param[in]  pos   A posição informada
			 *
			 * @return     O elemento constante na posição informada
			 */
			const_reference at( size_type pos ) const;

			/**
			 * @brief      Acessa o elemento na posição informada
			 *
			 * @param[in]  pos   A posição informada
			 *
			 * @return     O elemento na posição informada
			 */
			reference at( size_type pos );

			/**
			 * @brief      Acessa o primeiro elemento do vector
			 *
			 * @return     Um ponteiro para o primeiro elemento do vector
			 */
			T * data( void );

			/**
			 * @brief      Acessa o primeiro elemento do vector
			 *
			 * @return     Um ponteiro constante para o primeiro elemento do vector
			 */
			const T * data( void ) const;

			// [VI] Operators
			
			/**
			 * @brief      Verifica se dois vetores são iguais
			 *
			 * @param[in]  rhs   o vector que se deseja comparar
			 *
			 * @return     Sim, caso os vetores sejam iguais, não, caso contrário
			 */
			bool operator==( const vector & rhs ) const;
			
			/**
			 * @brief      Verifica se dois vetores são diferentes
			 *
			 * @param[in]  rhs   o vector que se deja comparar
			 *
			 * @return     Sim, caso eles sejam diferente, não, se contrário.
			 */
			bool operator!=( const vector & rhs ) const;

			/**
			 * @brief      Imprime na saída padrão, o vetor informado
			 */
			void print () const;

	};

	/**
	 * impletação do template.
	 */
	#include "vector.inl"
} 

#endif