#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>

#include "../utils/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../utils/equal.hpp"

#include "tree_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template<class key, class T, class Compare = std::less<key>, class Alloc = std::allocator<ft::node<ft::pair<const key,T> > > >
	class map
	{
		public:
			typedef key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;

			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;

			typedef ft::node<value_type>										node_type;
			typedef node_type*													node_ptr;

			typedef ft::tree_iterator<value_type, node_type>					iterator;
			typedef ft::tree_iterator<const value_type, node_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			typedef std::ptrdiff_t												difference_type;
			typedef size_t														size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
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

		private:
			node_ptr		_root;
			allocator_type	_alloc;
			size_type		_size;
			key_compare		_key_cmp;
			value_compare	_val_cmp;

		public:

// -----------  CONSTRUCTORS -----------

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_root(NULL), _alloc(alloc), _size(0), _key_cmp(comp), _val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
			}

			template <class InputIterator> 
			map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, 
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_root(NULL), _alloc(alloc), _size(0), _key_cmp(comp), _val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
				this->insert(first, last);
			}

			map (const map& x) : _root(NULL), _alloc(allocator_type()), _size(0), _key_cmp(key_compare()), _val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
				*this = x;
			}

// ----------- DESTRUCTOR -----------

			virtual ~map(void)
			{
				//this->clear();
				this->_alloc.deallocate(this->_root, 1);
			}

// -----------  OPERATOR = OVERLOAD -----------

// 			map& operator= (map const &rhs)
// 			{
// //					std::cout << "Map Operator = " <<std::endl;
// 				if (this != &rhs)
// 				{
// 					this->clear();
// 					this->insert(rhs.begin(), rhs.end());
// 				}
// 				return (*this);
// 			}

// -----------  ITERATORS -----------

			iterator begin() { return iterator(leftmost(this->_root)); }
			const_iterator begin() const { return const_iterator(leftmost(this->_root)); }

			iterator end() { return iterator(rightmost(this->_root)); }
			const_iterator end() const { return const_iterator(rightmost(this->_root)); }

			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

// -----------  MODIFIERS -----------

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> ret;
				ret.first = this->find(val.first);
				if (ret.first == this->end())
				{
					node_ptr	newnode = this->_alloc.allocate(1);
					this->_alloc.construct(newnode, node_type(val));
					this->_add_node(newnode);
					ret.first = iterator(newnode);
					ret.second = true;
				}
				else
					ret.second = false;
				return (ret);
			}

			iterator insert(iterator position, const value_type& val)
			{
				static_cast<void>(position);
				return this->insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			// void clear(void)
			// {
			// 	if (this->_size == 0)
			// 		return ;
			// 	erase(begin(), end());
			// }

// -----------  OPERATIONS -----------

			iterator find(const key_type& k)
			{
				node_ptr	curr = this->_root;

				while (curr && (this->_key_cmp(curr->data.first, k) || this->_key_cmp(k, curr->data.first)))
				{
					if (this->_key_cmp(k, curr->data.first))
						curr = curr->left;
					else
						curr = curr->right;
				}
				if (curr)
					return (iterator(curr));
				else
					return (this->end());
			}

			const_iterator find(const key_type& k) const
			{
				return const_iterator(this->find(k));
			}


// -----------  PRIVATE FUNCTIONS -----------

		private:

			void _add_node(node_ptr to_add)
			{
				node_ptr*	parent = &this->_root;
				node_ptr*	curr = &this->_root;
				node_ptr	endnode = rightmost(this->_root);
				bool		which_direction;

				++this->_size;
				while (*curr && *curr != endnode)
				{
					parent = curr;
					which_direction = _val_cmp(to_add->data, (*curr)->data);
					curr = (which_direction ? &(*curr)->left : &(*curr)->right);
				}
				if (*curr == NULL)
				{
					to_add->parent = *parent;
					*curr = to_add;
				}
				else
				{
					*curr = to_add;
					to_add->parent = endnode->parent;
					endnode->parent = rightmost(to_add);
					rightmost(to_add)->right = endnode;
				}
			}
	};
}

#endif