#ifndef VECTOR_HPP
# define VECTOR_HPP


#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/reverse_iterator.hpp"
#include "vector_iterator.hpp"

#include <iostream>

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
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

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

			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

// -----------  CAPACITY -----------

			size_type size() const { return this->_size ;}

			size_type max_size() const { return this->_alloc.max_size(); }

			void resize(size_type n, value_type val = value_type())
			{
				if (n > this->_size)
				{
					if (n > this->_capacity)
						this->reallocation(n);
					for (size_t i = this->_size; i < n; i++)
						this->push_back(val);
				}
				else if (n < this->_size)
					for (size_t i = this->_size - n; i > 0; i--)
						this->pop_back();
			}

			size_type capacity() const { return (this->_capacity); }

			bool empty() const { return (this->_size == 0); }

			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					if (n > this->max_size())
						throw std::length_error("vector::reserve");
					this->reallocation(n);
				}
			}

// -----------  ELEMENT ACCESS -----------

			reference operator[] (size_type n) { return (this->_array[n]); }
			const_reference operator[] (size_type n) const { return (this->_array[n]); }
			
			reference at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("Index out of vector bounds!");
				return (this->_array[n]);
			}
			const_reference	at (size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("Index out of vector bounds!");
				return (this->_array[n]);
			}

			reference front() { return (this->_array[0]); }
			const_reference front() const { return (this->_array[0]); }

			reference back() { return (this->_array[this->_size - 1]); }
			const_reference back() const { return (this->_array[this->_size - 1]); }

// -----------  MODIFIERS -----------

			void assign(size_type n, const value_type& val)
			{
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			template <class InputIterator>
			void assign(typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_t	i = last - first;
				this->clear();

				if (this->_capacity < i)
					this->reserve(i);
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}

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

			void pop_back()
			{
				if (!this->empty())
				{
					this->_alloc.destroy(this->_array + (this->_size - 1));
					this->_size--;
				}
			}

			iterator insert(iterator position, const value_type& val)
			{
				if (this->_capacity == this->max_size())
					return (NULL);
				if (this->_capacity == 0)
				{
					this->push_back(val);
					return (this->begin());
				}
				if (this->_capacity == this->_size)
				{
					std::ptrdiff_t pos = position - this->begin();
					this->reallocation(2 * this->_capacity);
					position = this->begin() + pos;
				}
				vector tmp(position, this->end());
				for (size_t i = 0; i < tmp.size(); i++)
					this->pop_back();
				this->push_back(val);
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					this->push_back(*it);

				return (position);
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++)
					position = this->insert(position, val);
			}

			template <class InputIterator>
			void insert(iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last)
			{
				for (; first != last; first++)
				{
					position = this->insert(position, *first);
					position++;
				}
			}

			iterator erase(iterator position)
			{
				if (this->empty() == true || position > this->end())
					return (NULL);

				vector tmp(position + 1, this->end());

				for (size_t i = 0; i <= tmp.size(); i++)
					this->pop_back();
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					this->push_back(*it);
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				if (this->empty() == true || last > this->end() || first > this->end())
					return (NULL);
				iterator tmp = first;
				while (tmp != last)
				{
					erase(first);
					tmp++;
				}
				return (first);
			}

			void swap(vector& x)
			{
				allocator_type tmp_alloc = x._alloc;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;
				pointer tmp_array = x._array;

				x._alloc = this->_alloc;
				this->_alloc = tmp_alloc;
				x._size = this->_size;
				this->_size = tmp_size;
				x._capacity = this->_capacity;
				this->_capacity = tmp_capacity;
				x._array = this->_array;
				this->_array = tmp_array;
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				this->_size = 0;
			}

// -----------  ALLOCATOR -----------

			allocator_type get_allocator() const
			{
				return (this->_alloc);
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