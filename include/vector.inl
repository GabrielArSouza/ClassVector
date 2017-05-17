/**
 * @file vector.inl
 * @author Gabriel Araújo de Souza
 * @date 17 May 2017
 * @brief Arquivo contendo as implementações das classes vector e MyIterator
 */

// [I] SPECIAL MEMBERS

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
typename ls::MyIterator<T>
ls::vector<T>::begin( void )
{ return ls::MyIterator<T> ( &m_data[0] ); }

template <typename T>
typename ls::MyIterator<T>
ls::vector<T>::end( void )
{ return ls::MyIterator<T> ( &m_data[m_len] ); }

template <typename T>
typename ls::MyIterator<const T>
ls::vector<T>::cbegin( void ) const
{ return ls::MyIterator< const T> ( &m_data[0] ); }

template <typename T>
typename ls::MyIterator<const T>
ls::vector<T>::cend( void ) const
{ return ls::MyIterator<const T> ( &m_data[m_len] ); }

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
typename ls::MyIterator<T> ls::vector<T>::insert
( iterator pos, const_reference value )
{
	if ( this->full() ) this->reserve();

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
typename ls::MyIterator<T> ls::vector<T>::insert
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
	
	while ( (m_len + d) > m_size ) this->reserve();
	std::copy(&m_data[cont], &m_data[m_len], &m_data[cont+d]);

	for (/*empty*/; first != last; ++first, ++cont)
	{
		m_data[cont] = *first;
		m_len++;

	}

	return pos;

}

template <typename T>
typename ls::MyIterator<T> ls::vector<T>::insert
( iterator pos, std::initializer_list< T > ilist)
{
	auto i = 0;
	auto cont = 0;
	
	//encontrar local de inserção
	while ( *pos != m_data[i] )
	{
		cont++;
		i++;
	}

	auto tam = ilist.size();
	while ( (m_len + tam) > m_size ) this->reserve();
	std::copy(&m_data[cont], &m_data[m_len], &m_data[cont+tam]);

	for (auto first(ilist.begin()); first != ilist.end(); ++first, ++cont)
	{
		m_data[cont] = *first;
		m_len++;

	}

	return pos;

}

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

template <typename T>
void ls::vector<T>::assign( std::initializer_list<T> value )
{
	if ( this->empty() )
		throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");

	unsigned int i = 0;
	auto elem_list = value.begin();
	while ( i != m_len )
	{
		if ( elem_list == value.end() ) 
			elem_list = value.begin();
		m_data[i++] = *elem_list++;
	}

}

template <typename T>
template < typename InputItr >
void ls::vector<T>::assign( InputItr first, InputItr last )
{
	if ( this->empty() )
		throw std::out_of_range("[assign()]: Cannot recover an element from an empty vector!");	

	auto elem_intr = first;
	unsigned int i = 0;
	while ( i != m_len )
	{
		if ( elem_intr == last )
			elem_intr = first;
		m_data[i++] = *elem_intr;
		elem_intr++;
	}
}

template < typename T>
typename ls::MyIterator<T> ls::vector<T>::erase
( iterator first, iterator last )
{
	auto init_er = last;
	while ( init_er != this->end() )
	{
		*first = *init_er;
		first++;
		init_er++;
	}

	auto cont = 0;
	auto t = first;
	while ( t != last )
	{
		cont++;
		t++;
	}
	m_len = m_len - cont;

	return first;
}

template < typename T>
typename ls::MyIterator<T> ls::vector<T>::erase
( iterator pos )
{
	auto ponter = pos;
	auto init = ++pos; 

	while ( init != this->end() )
	{
		*ponter = *init;
		ponter++;
		init++;
	}
	m_len--;

	return ponter;
}

// [V] Element access
template <typename T>
typename ls::vector<T>::const_reference 
ls::vector<T>::back( void ) const
{
	if ( this->empty() )
		throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");

	return m_data[m_len-1];
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

template <typename T>
T * ls::vector<T>::data( void )
{
	return &m_data[0];
}

template <typename T>
const T * ls::vector<T>::data( void ) const
{
	return &m_data[0];
}

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

template <typename T>
void ls::vector<T>::print () const 
{
	std::cout << ">>> [ ";
	std::copy( &m_data[0], &m_data[m_len],
               std::ostream_iterator< T >(std::cout, " ") );
	std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";

}

template <typename T>
T & ls::MyIterator<T>::operator* ( )
{
	assert( m_ptr != nullptr );
	return *m_ptr;
}

// ++it;
template <typename T>
typename ls::MyIterator<T> 
& ls::MyIterator<T>::operator++ ( )
{
	m_ptr++;
	return *this;
}	

// it++;
template <typename T>
typename ls::MyIterator<T>
ls::MyIterator<T>::operator++ ( int a )
{
	MyIterator temp = *this;
	m_ptr++;
	return temp;
}

// --it;
template <typename T>
typename ls::MyIterator<T>
& ls::MyIterator<T>::operator-- ( )
{
	m_ptr--;
	return *this;
}  

// it--;
template <typename T>
typename ls::MyIterator<T>
ls::MyIterator<T>::operator-- ( int a )
{
	MyIterator temp = *this;
	m_ptr--;
	return temp;
}

template <typename T> 
bool ls::MyIterator<T>::operator== ( const MyIterator & rhs ) const
{
	return m_ptr == rhs.m_ptr;
}

template <typename T>
bool ls::MyIterator<T>::operator!= ( const MyIterator & rhs ) const
{
	return m_ptr != rhs.m_ptr;
}
