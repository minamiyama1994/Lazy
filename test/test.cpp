#include"lazy/lazy.hpp"
#include"lazy/list.hpp"
#include<string>
#include<iostream>
#include<iomanip>
template < typename T >
auto print_list ( const lazy::lazy < lazy::list < T > > & l ) -> void
try
{
	std::cout << head ( l ).get ( ) << std::endl ;
	print_list ( tail ( l ) ) ;
}
catch ( const lazy::bad_lazy & )
{
	std::cout << std::endl ;
}
auto main ( ) -> int
{
	const lazy::lazy < int > i1 = 2 ;
	const lazy::lazy < int > i2 = 5 ;
	const auto i3 = i1 + i2 ;
	const auto i4 = i1 - i2 ;
	const auto i5 = i1 * i2 ;
	const auto i6 = i1 / i2 ;
	const auto i7 = i1 % i2 ;
	const auto i8 = i1 && i2 ;
	const auto i9 = i1 || i2 ;
	const auto iA = i1 < i2 ;
	const auto iB = i1 > i2 ;
	const auto iC = i1 <= i2 ;
	const auto iD = i1 >= i2 ;
	const auto iE = i1 & i2 ;
	const auto iF = i1 | i2 ;
	const auto iG = i1 ^ i2 ;
	const auto iH = i1 << i2 ;
	const auto iI = i1 >> i2 ;
	auto l1 = lazy::range ( 1 ) ;
	auto l2 = lazy::take ( 10 , l1 ) ;
	auto l3 = lazy::map ( std::function < int ( int ) > { [ ] ( int n ) { return 2 * n ; } } , l2 ) ;
	auto l4 = lazy::filter ( std::function < bool ( int ) > { [ ] ( int n ) { return n % 2 ; } } , l2 ) ;
	std::cout
		<< std::boolalpha
		<< i1.get ( ) << std::endl
		<< i2.get ( ) << std::endl
		<< i3.get ( ) << std::endl
		<< i4.get ( ) << std::endl
		<< i5.get ( ) << std::endl
		<< i6.get ( ) << std::endl
		<< i7.get ( ) << std::endl
		<< i8.get ( ) << std::endl
		<< i9.get ( ) << std::endl
		<< iA.get ( ) << std::endl
		<< iB.get ( ) << std::endl
		<< iC.get ( ) << std::endl
		<< iD.get ( ) << std::endl
		<< iE.get ( ) << std::endl
		<< iF.get ( ) << std::endl
		<< iG.get ( ) << std::endl
		<< iH.get ( ) << std::endl
		<< iI.get ( ) << std::endl ;
	print_list ( l2 ) ;
	print_list ( l3 ) ;
	print_list ( l4 ) ;
}
