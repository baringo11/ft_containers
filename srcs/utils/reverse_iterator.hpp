#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <stdexcept>

namespace ft
{

	template <class Iterator>
	class reverse_iterator 
	{
		public:
			typedef	Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef	reverse_iterator<Iterator>								self;

		private:
			iterator_type _current;

		public:

// -----------  CONSTRUCTORS -----------

			reverse_iterator() :
				_current(NULL)
			{}

			explicit reverse_iterator(iterator_type it)	:
				_current(it)
			{}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it)	:
				_current(rev_it.base())
			{}

// -----------  DESTRUCTOR -----------
			~reverse_iterator()
			{}

// -----------  OPERATOR OVERLOADS -----------

			template<class Iter>
			reverse_iterator& operator= (const reverse_iterator<Iter>& rhs)
			{
				this->_current = rhs.base(); return (*this);
			}

			reference operator* () const
			{
				return (*(--this->base()));
			}

			pointer operator-> () const
			{
				return (&operator*());
			}

			reference operator[] (difference_type n) const
			{
				return (*(this->_current - n - 1));
			}

			self operator+ (difference_type n) const
			{
				return self(this->_current - n);
			}

			self& operator++()
			{
				--this->_current;
				return (*this);
			}

			self operator++(int)
			{
				self tmp = *this;
				--this->_current;
				return tmp;
			}

			self& operator+= (difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			self operator- (difference_type n) const
			{
				return self(this->_current + n);
			}

			self& operator--()
			{
				++this->_current;
				return (*this);
			}

			self operator--(int)
			{
				self tmp = *this;
				++this->_current;
				return (tmp);
			}

			self& operator-= (difference_type n)
			{
				this->_current += n;
				return (*this);
			}

// -----------  GETTER -----------

			iterator_type	base() const
			{
				return this->_current;
			}
	};

// -----------  NON-MEMBER FUNCTION OVERLOADS -----------

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() == lhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() != lhs.base());
	}

	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() <= lhs.base());
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() > lhs.base());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() >= lhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
