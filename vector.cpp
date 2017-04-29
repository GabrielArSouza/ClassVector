#include <iostream>

namespace ls 
{
	template <typename T>
	class vector
	{
		private:
			static const size_t SIZE = 128;	
			T * m_data;

		public:
			//<! Construtor default
			vector()
			{
				m_data = new T;
			}

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

			// Escrever no vetor
			void write ( T value )
			{
				*m_data = value;
			}

			// ler vetor
			T read ( void ) const
			{
				return *m_data
			}
	}; 
}


int main () {

	ls::vector <int> v;
	ls::vector <int> v2;


}