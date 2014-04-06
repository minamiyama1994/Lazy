#ifndef LAZY_LIST_HPP
#define LAZY_LIST_HPP
#include"lazy/lazy.hpp"
namespace lazy
{
	template < typename T >
	class list
	{
		lazy < T > head_ ;
		lazy < list < T > > tail_ ;
	public :
		list ( ) = default ;
		list ( const list & ) = default ;
		list ( list && ) = default ;
		auto operator = ( const list & ) -> list & = delete ;
		auto operator = ( list && ) -> list & = delete ;
		~ list ( ) = default ;
		list ( const lazy < T > & head , const lazy < list < T > > & tail_ ) ;
		auto head ( ) const -> lazy < T >
		{
			return head_ ;
		}
		auto tail ( ) const -> lazy < list < T > >
		{
			return tail_ ;
		}
	} ;
	template < typename T >
	list < T >::list ( const lazy < T > & head , const lazy < list < T > > & tail_ )
		: head_ { std::move ( head ) }
		, tail_ { std::move ( tail_ ) }
	{
	}
	template < typename T >
	auto head ( const lazy < list < T > > & l ) -> lazy < T >
	{
		return l.get ( ).head ( ) ;
	}
	template < typename T >
	auto tail ( const lazy < list < T > > & l ) -> lazy < list < T > >
	{
		return l.get ( ).tail ( ) ;
	}
	template < typename T >
	auto range ( T begin ) -> lazy < list < T > >
	{
		return lazy < list < T > > { std::function < list < T > ( ) > { [ = ] ( )
			{
				return list < T > { lazy < T > { begin } , std::function < list < T > ( ) > { [ = ] ( )
					{
						return range ( begin + 1 ).get ( ) ;
					} }
				} ;
			} }
		} ;
	}
	template < typename T >
	auto range ( T begin , T end ) -> lazy < list < T > >
	{
		return ( begin >= end ) ? lazy < list < T > > { } : lazy < list < T > > { [ = ] ( )
			{
				return list < T > { lazy < T > { begin } , [ = ] ( )
					{
						return range ( begin + 1 ).get ( ) ;
					}
				} ;
			}
		} ;
	}
	template < typename A , typename B >
	auto foldl ( const std::function < A ( A , B ) > & f , const lazy < A > & a , const lazy < list < B > > & bs ) -> lazy < A >
	{
		return lazy < A > { [ = ] ( ) -> A
			{
				try
				{
					return f ( foldl ( f , a , tail ( bs ) ).get ( ) , head ( bs ).get ( ) ) ;
				}
				catch ( const bad_lazy & )
				{
					return a.get ( ) ;
				}
			}
		} ;
	}
	template < typename A , typename B >
	auto foldr ( const std::function < B ( A , B ) > & f , const lazy < B > & b , const lazy < list < A > > & as ) -> lazy < B >
	{
		return lazy < B > { [ = ] ( ) -> B
			{
				try
				{
					return foldr ( f , lazy < B > { [ = ] ( )
							{
								return f ( head ( as ).get ( ) , b.get ( ) ) ;
							}
						} , tail ( as ) ).get ( ) ;
				}
				catch ( const bad_lazy & )
				{
					return b.get ( ) ;
				}
			}
		} ;
	}
	template < typename T , typename U >
	auto map ( const std::function < U ( T ) > & f , const lazy < list < T > > & l ) -> lazy < list < U > >
	{
		return foldl ( std::function < list < U > ( list < U > , T ) > { [ = ] ( const list < U > & a , const T & b ) -> list < U >
				{
					return list < U > { lazy < U > { f ( b ) } , lazy < list < U > > { a } } ;
				} } , lazy < list < U > > { list < U > { } } , l ) ;
	}
	template < typename T >
	auto filter ( const std::function < bool ( T ) > & f , const lazy < list < T > > & l ) -> lazy < list < T > >
	{
		return foldl ( std::function < list < T > ( list < T > , T ) > { [ = ] ( const list < T > & a , const T & b ) -> list < T >
				{
					return f ( b ) ? list < T > { lazy < T > { b } , lazy < list < T > > { a } } : a ;
				} } , lazy < list < T > > { list < T > { } } , l ) ;
	}
	template < typename T >
	auto take ( std::size_t n , const lazy < list < T > > & l ) -> lazy < list < T > >
	{
		return n ? lazy < list < T > > { list < T > { lazy < T > { std::function < T ( ) > { [ = ] ( )
			{
				return head ( l ).get ( ) ;
			} } } , lazy < list < T > > { std::function < list < T > ( ) > { [ = ] ( )
			{
				return take ( n - 1 , tail ( l ) ).get ( ) ;
			} } } } } : lazy < list < T > > { list < T > { } } ;
	}
}
#endif
