#ifndef VECTOR_ITERATOR
# define VECTOR_ITERATOR

#include "../utils/iterator_traits.hpp"
#include <vector>

namespace ft
{
	template <typename Iterator>
	class vector_iterator : public ft::iterator_traits<Iterator>
	{
		public:
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::vector_iterator<Iterator>						self;

		private:
			pointer	_ptr;

		public:

// -----------  CONSTRUCTORS -----------

			vector_iterator()
			{}

			template <typename Iter>
			vector_iterator(const vector_iterator<Iter>& it) :
				_ptr(it.get_ptr())
			{}

			vector_iterator(const pointer pt) :
				_ptr(pt)
			{}

// -----------  DESTRUCTOR -----------

			~vector_iterator()
			{}


// -----------  OPERATOR OVERLOADS -----------

			self& operator= (const self& it)
			{
				if (this != &it)
					this->_ptr = it._ptr;
				return (*this);
			}

			pointer operator-> () const
			{
				return (this->_ptr);
			}

			reference operator* (void) const
			{
				return (*this->_ptr);
			}

			reference operator[] (difference_type n) const
			{
				return (this->_ptr + n);
			}

			self& operator++ (void)
			{
				++this->_ptr;
				return (*this);
			}

			self operator++ (int)
			{
				self tmp(*this);
				++this->_ptr;
				return(tmp);
			}

			self& operator+= (difference_type n)
			{
				this->_ptr += n;
				return (*this);
			}

			self& operator-- (void)
			{
				--this->_ptr;
				return (*this);
			}

			self operator-- (int)
			{
				self tmp(*this);
				--this->_ptr;
				return(tmp);
			}

			self& operator-= (difference_type n)
			{
				this->_ptr -= n;
				return (*this);
			}

			self operator+ (difference_type n) const
			{
				return (self(this->_ptr + n));
			}

			self operator- (difference_type n) const
			{
				return (self(this->_ptr - n));
			}

// -----------  GETTER -----------

			pointer get_ptr() const
			{
				return (this->_ptr);
			}
	};

// -----------  NON-MEMBER FUNCTION OVERLOADS -----------

	template <class It1, class It2>
	bool operator== (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() == rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator!= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() != rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator< (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() < rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator<= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() <= rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator> (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() > rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator>= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() >= rhs.get_ptr());
	}

	template <class It>
	vector_iterator<It>	operator+ (typename vector_iterator<It>::difference_type n,
		const vector_iterator<It>& it)
	{
		return (it.get_ptr() + n);
	}

	template <class It1, class It2>
	typename vector_iterator<It1>::difference_type	operator- (const vector_iterator<It1>& lhs,
		const vector_iterator<It2>& rhs)
	{
		return(lhs.get_ptr() - rhs.get_ptr());
	}
}

#endif