#ifndef STACK_HPP
# define STACK_HPP

#include "../Vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class Stack
	{
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

		protected:
			container_type _ctn;
		
		public:

// -----------  CONSTRUCTORS -----------

			explicit stack(const container_type& ctnr = container_type()) : _ctn(ctnr){}
			
			stack(const stack<T, Container>& src) : _ctn(ctnr)
			{
				*this = src;
			} 

// ----------- DESTRUCTOR -----------

			~stack()
			{}


// -----------  OPERATOR = OVERLOAD -----------

			stack<T, Container>& operator= (const stack<T, Container>& src)
			{
				this->_ctn = src._ctn;
				return (*this);
			}

// -----------  MEMBER FUNCTIONS -----------

			bool empty() const { return (this->_c.empty()); }

			size_type size() const { return (this->_c.size()); }

			value_type& top() { return (this->_c.back()); }

			const value_type& top() const { return (this->_c.back()); }
			
			void push(const value_type& val)
			{
				this->_c.push_back(val);
			}

			void pop()
			{
				this->_c.pop_back();
			}

    };
}

#endif