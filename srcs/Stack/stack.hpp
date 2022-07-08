#ifndef STACK_HPP
# define STACK_HPP

#include "../Vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

		protected:
			container_type _cnt;
		
		public:

// -----------  CONSTRUCTORS -----------

			explicit stack(const container_type& ctnr = container_type()) : _cnt(ctnr){}
			
			stack(const stack<T, Container>& src) : _cnt(src)
			{
				*this = src;
			} 

// ----------- DESTRUCTOR -----------

			~stack()
			{}


// -----------  OPERATOR = OVERLOAD -----------

			stack<T, Container>& operator= (const stack<T, Container>& src)
			{
				this->_cnt = src._cnt;
				return (*this);
			}

// -----------  MEMBER FUNCTIONS -----------

			bool empty() const { return (this->_cnt.empty()); }

			size_type size() const { return (this->_cnt.size()); }

			value_type& top() { return (this->_cnt.back()); }

			const value_type& top() const { return (this->_cnt.back()); }

			void push(const value_type& val)
			{
				this->_cnt.push_back(val);
			}

			void pop()
			{
				this->_cnt.pop_back();
			}

// ----------- Friend declaration for non member function overloads -----------

			template <class U, class Cont>
			friend bool	operator== (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator!= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator<  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator<= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator>  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator>= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

    };

// ----------- Non member function overloads -----------

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt == rhs._cnt);
	}

	template <class T, class Container>
	bool	operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt != rhs._cnt);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt < rhs._cnt);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt <= rhs._cnt);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt > rhs._cnt);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cnt >= rhs._cnt);
	}

}

#endif