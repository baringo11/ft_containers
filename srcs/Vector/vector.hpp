#ifndef VECTOR_HPP
# define VECTOR_HPP


#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "vector_iterator.hpp"

#include <iostream>
#include <vector>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T													value_type;
			typedef Alloc												allocator_type;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			typedef vector_iterator<pointer>							iterator;
			typedef vector_iterator<const_pointer>						const_iterator;
			typedef typename std::vector<T>::reverse_iterator			reverse_iterator;
			typedef typename std::vector<T>::reverse_iterator			const_reverse_iterator;

			typedef std::ptrdiff_t										difference_type;
			typedef size_t												size_type;

		private:
			T*			_array;
			size_t		_size;
			size_t		_capacity;
			Alloc		_alloc;

		public:

// -----------  CONSTRUCTORS -----------

			explicit vector (const allocator_type& alloc = allocator_type())
			: _array(NULL), _size(0), _capacity(0), _alloc(alloc){}
	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _array(NULL), _size(n), _capacity(n), _alloc(alloc)
			{
				this->_array = this->_alloc.allocate(n);
				for(size_t i = 0; i < n; i++)
					this->_alloc.construct(this->_array + i, val);
			}
		
			template <class InputIterator>
			vector (typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type first,
			 	InputIterator last, const allocator_type& alloc = allocator_type())
			: _array(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				for(; first != last; first++)
					this->push_back(*first);
			}
		
			vector (const vector& x)
			: _array(NULL), _size(0), _capacity(0)
			{
				*this = x;
			}

// ----------- DESTRUCTOR -----------

			~vector()
			{
				if (this->_capacity)
				{
					for (size_t i = 0; i < this->_size ; i++)
						this->_alloc.destroy(this->_array + i);
					this->_alloc.deallocate(this->_array, this->_capacity);
				}
			}

// -----------  OPERATOR = OVERLOAD -----------

			vector &operator= (const vector &x)
			{
				if (this != &x)
				{
					this->~vector();
					this->_size = x._size;
					this->_capacity = x._capacity;
					this->_alloc = x._alloc;
					if (this->_capacity != 0)
						this->_array = this->_alloc.allocate(this->_capacity);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_array + i, x._array[i]);
				}
				return (*this);
			}

// -----------  ITERATORS -----------

			iterator begin() { return iterator(this->_array); }
			const_iterator begin() const { return const_iterator(this->_array); }

			iterator end() { return iterator(this->_array + this->_size); }
			const_iterator end() const { return const_iterator(this->_array + this->_size); }


// -----------  ELEMENT ACCESS -----------

			reference operator[] (size_type n)
			{
				return (this->_array[n]);
			}

// -----------  MODIFIERS -----------

			void push_back (const value_type& val)
			{
				if (this->_size < this->_capacity)
					this->_alloc.construct(this->_array + this->_size, val);
				else
				{
					if (this->_capacity) 
						this->reallocation(this->_capacity * 2);
					else
					{
						this->_array = this->_alloc.allocate(1);
						this->_capacity++;
					}
					this->_alloc.construct(this->_array + this->_size, val);
				}
				this->_size++;
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				this->_size = 0;
			}
	
		private:

			void reallocation(size_t n)
			{
				pointer new_array = this->_alloc.allocate(n);

				for(size_t i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(new_array + i, this->_array[i]);
					this->_alloc.destroy(this->_array + i);
				}
				//if (this->_capacity != 0)
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_array = new_array;
				this->_capacity = n;
			}

	};
}

#endif