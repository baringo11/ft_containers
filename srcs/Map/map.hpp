#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <utility>

namespace ft
{
	template<class key, class T, class Compare = std::less<key>, class Alloc = std::allocator<std::pair<const key,T> > >
	class map
	{
		public:
			typedef key													key_type;
			typedef T													mapped_type;
			typedef std::pair<const key_type, mapped_type>				value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			// iterarors

			typedef std::ptrdiff_t										difference_type;
			typedef size_t												size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			

	};
}

#endif