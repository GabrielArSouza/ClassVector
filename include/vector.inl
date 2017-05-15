// [I] SPECIAL MEMBERS

/*>>std::distance e alocar a memória com o tamanho e o copy<<*/
// template < typename InputItr >
// vector( InputItr first, InputItr last)
// {
// 	m_data = new T;
// 	for (auto i(0); first != last; ++first, ++i)
// 		m_data[i] = (*first);
// 	shrink_to_fit();
// }

template <typename T>
ls::vector<T> &ls::vector<T>::operator=
( const vector & other )
{
	m_len = other.m_len;
	m_size = other.m_size;

	for (auto i(0u); i < m_len; ++i )
		*(m_data+i) = *(other.m_data+i);

	return *this;
}

template <typename T>
ls::vector<T> &ls::vector<T>::operator=
( vector && other)
{
	m_data = other.m_data;
	other.m_data = nullptr;	

	return *this;
}

// [II] ITERATORS
template <typename T>
typename ls::vector<T>::iterator
ls::vector<T>::begin( void )
{ return ls::vector<T>::iterator ( &m_data[0] ); }

template <typename T>
typename ls::vector<T>::iterator
ls::vector<T>::end( void )
{ return ls::vector<T>::iterator ( &m_data[m_len] ); }

template <typename T>
typename ls::vector<T>::const_iterator 
ls::vector<T>::cbegin( void ) const
{ return ls::vector<T>::const_iterator ( &m_data[0] ); }

template <typename T>
typename ls::vector<T>::const_iterator
ls::vector<T>::cend( void ) const
{ return ls::vector<T>::const_iterator ( &m_data[m_len] ); }

// [III] Capacity
template <typename T> 
size_type ls::vector<T>::size( void ) const
{
	return m_len;
}

template <typename T>
size_type ls::vector<T>::capacity( void ) const
{
	return m_size;
}

template <typename T>
bool ls::vector<T>::empty( void ) const
{
	return m_len == 0;
}

template <typename T>
bool ls::vector<T>::full( void ) const
{
	return m_len == m_size;
}

// [IV] Modifiers
template <typename T>
void ls::vector<T>::clear( void )
{
	m_len = 0;
}

template <typename T>
void ls::vector<T>::push_front
( const_reference value )
{
	if ( this->full() ) this->reserve();
	std::copy( m_data, m_data+m_len, m_data+1 );

	m_data[0] = value;
	m_len++;
}

template <typename T>
void ls::vector<T>::push_back
( const_reference value )
{
	if ( this->full() ) this->reserve();

	m_data[m_len++] = value;
}

template <typename T>
void ls::vector<T>::pop_back( void )
{
	if ( this->empty() )
		throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");

	m_len--;
}

template <typename T>
void ls::vector<T>::pop_front( void )
{
	if ( this->empty() )
		throw std::out_of_range("[pop_front()]: Cannot recover an element from an empty vector!");

	std::copy( m_data+1, m_data+m_len, m_data );
		
	m_len--;
}

template <typename T>
typename ls::vector<T>::iterator ls::vector<T>::insert
( iterator pos, const_reference value )
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

template <typename T>
template <typename InputItr>
typename ls::vector<T>::iterator ls::vector<T>::insert
( iterator pos, InputItr first, InputItr last)
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

template <typename T>
void ls::vector<T>::reserve( void )
{
	T * temp = new T[ m_size * 2 ];
	std::copy(m_data, m_data+m_len, temp);
	delete m_data;
	m_data = temp;
	m_size *= 2;
}

template <typename T>
void ls::vector<T>::shrink_to_fit( void )
{
	m_size = m_len;
}

template <typename T>
void ls::vector<T>::assign( const_reference value)
{
	if ( this->empty() )
		throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");

	for (auto i(0u); i <= m_len; ++i)
		*(m_data+i) = value;
}

//initializer é {1, 2, 3, 4 }
template <typename T>
void ls::vector<T>::assign( std::initializer_list<T> value )
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
template <typename T>
typename ls::vector<T>::const_reference 
ls::vector<T>::back( void ) const
{
	if ( this->empty() )
		throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");

	return m_data[m_len];
}

template <typename T>
typename ls::vector<T>::const_reference 
ls::vector<T>::front( void ) const
{
	if ( this->empty() )
		throw std::out_of_range("[front()]: Cannot recover an element from an empty vector!");

	return m_data[0];
}

template <typename T>
typename ls::vector<T>::const_reference
ls::vector<T>::operator[]( size_type pos ) const
{
	return m_data[pos];
}

template <typename T>
typename ls::vector<T>::reference 
ls::vector<T>::operator[]( size_type pos )
{
	return m_data[pos];
}

template <typename T>
typename ls::vector<T>::const_reference 
ls::vector<T>::at( size_type pos ) const
{
	if ( pos < 0 || pos > m_len )
		throw std::out_of_range("[at()]: índice inválido ");
		
	return m_data[pos];
}

template <typename T>
typename ls::vector<T>::reference 
ls::vector<T>::at( size_type pos )
{
	if ( pos < 0 || pos > m_len )
		throw std::out_of_range("[at()]: índice inválido ");
		
	return m_data[pos];
}

//pointer data( void );
// const_reference data( void ) const;

// [VI] Operators
template <typename T>
bool ls::vector<T>::operator==( const vector & rhs ) const
{
	if ( m_len != rhs.m_len ) return false;
	if ( m_size != rhs.m_size ) return false;

	for ( auto i(0u); i < m_len; i++ )
	{
		if (*(m_data+i) != *(rhs.m_data+i) ) return false;
	}

	return true;
}

template <typename T>
bool ls::vector<T>::operator!=( const vector & rhs ) const
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
/*uma função, ele não é um método*/
//friend std::ostream & operator<<( std::ostream & os_, const Vector<T> & v_ );
// friend void swap( Vector<T> & first_, Vector<T> & second_ );
// 
template <typename T>
void ls::vector<T>::print () const 
{
	std::cout << ">>> [ ";
	std::copy( &m_data[0], &m_data[m_len],
               std::ostream_iterator< T >(std::cout, " ") );
	std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";

}

template <typename T>
const T & ls::vector<T>::iterator::operator* ( ) const
{
	assert( m_ptr != nullptr );
	return *m_ptr;
}

// ++it;
template <typename T>
typename ls::vector<T>::iterator 
& ls::vector<T>::iterator::operator++ ( )
{
	m_ptr++;
	return *this;
}	

// it++;
template <typename T>
typename ls::vector<T>::iterator 
ls::vector<T>::iterator::operator++ ( int a )
{
	MyIterator temp = *this;
	m_ptr++;
	return temp;
}

// --it;
template <typename T>
typename ls::vector<T>::iterator 
& ls::vector<T>::iterator::operator-- ( )
{
	m_ptr--;
	return *this;
}  

// it--;
template <typename T>
typename ls::vector<T>::iterator 
ls::vector<T>::iterator::operator-- ( int a )
{
	MyIterator temp = *this;
	m_ptr--;
	return temp;
}

template <typename T> 
bool ls::vector<T>::iterator::operator== ( const MyIterator & rhs ) const
{
	return m_ptr == rhs.m_ptr;
}

template <typename T>
bool ls::vector<T>::iterator::operator!= ( const MyIterator & rhs ) const
{
	return m_ptr != rhs.m_ptr;
}
