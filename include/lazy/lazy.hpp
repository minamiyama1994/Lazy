#ifndef LAZY_LAZY_HPP
#define LAZY_LAZY_HPP
#include<memory>
#include<functional>
namespace lazy
{
	template < typename T >
	class lazy ;
#define decl_lazy_bin_operator(op) \
	template < typename T , typename U > \
	auto operator op ( const lazy < T > & o1 ,  const lazy < U > & o2 ) -> lazy < decltype ( o1.get ( ) op o2.get ( ) ) > \
	{ \
		return lazy < decltype ( o1.get ( ) op o2.get ( ) ) > { [ = ] ( ) \
			{ \
				return o1.get ( ) op o2.get ( ) ; \
			} \
		} ; \
	}
#define decl_lazy_uni_operator(op) \
	template < typename T > \
	auto operator op ( const lazy < T > & o ) -> lazy < decltype ( op o.get ( ) ) > \
	{ \
		return lazy < decltype ( op o.get ( ) ) > { [ = ] ( ) \
			{ \
				return op o.get ( ) ; \
			} \
		} ; \
	}
	decl_lazy_bin_operator ( + )
	decl_lazy_bin_operator ( - )
	decl_lazy_bin_operator ( * )
	decl_lazy_bin_operator ( / )
	decl_lazy_bin_operator ( % )
	decl_lazy_bin_operator ( && )
	decl_lazy_bin_operator ( || )
	decl_lazy_bin_operator ( < )
	decl_lazy_bin_operator ( > )
	decl_lazy_bin_operator ( <= )
	decl_lazy_bin_operator ( >= )
	decl_lazy_bin_operator ( & )
	decl_lazy_bin_operator ( | )
	decl_lazy_bin_operator ( ^ )
	decl_lazy_bin_operator ( << )
	decl_lazy_bin_operator ( >> )
	template < typename T , typename U > \
	auto operator , ( const lazy < T > & o1 , const lazy < U > & o2 ) -> lazy < decltype ( o1.get ( ) , o2.get ( ) ) > \
	{
		return lazy < decltype ( o1.get ( ) , o2.get ( ) ) > { [ = ] ( )
			{
				return o1.get ( ) , o2.get ( ) ;
			}
		} ;
	}
	decl_lazy_uni_operator ( + )
	decl_lazy_uni_operator ( - )
	decl_lazy_uni_operator ( * )
	decl_lazy_uni_operator ( ~ )
	decl_lazy_uni_operator ( ! )
#undef decl_lazy_uni_operator
#undef decl_lazy_bin_operator
	class bad_lazy
		: public std::runtime_error
	{
	public :
		using std::runtime_error::runtime_error ;
	} ;
	template < typename T >
	class lazy
	{
		std::function < T ( ) > getter_ ;
	public :
		lazy ( ) = default ;
		lazy ( const lazy & ) = default ;
		lazy ( lazy && ) = default ;
		auto operator = ( const lazy & ) -> lazy & = delete ;
		auto operator = ( lazy && ) -> lazy & = delete ;
		~ lazy ( ) = default ;
		lazy ( T o ) ;
		lazy ( std::function < T ( ) > f ) ;
		auto get ( ) const -> T
		{
			return this->getter_ ? this->getter_ ( ) : throw bad_lazy { "empty lazy" } ;
		}
	} ;
	template < typename T >
	lazy < T >::lazy ( T o )
		: getter_ { [ = ] ( ) -> T
			{
				return o ;
			}
		}
	{
	}
	template < typename T >
	lazy < T >::lazy ( std::function < T ( ) > f )
		: getter_ { std::move ( f ) }
	{
	}
}
#endif
