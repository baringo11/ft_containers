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

			typedef typename allocator_type::template rebind<value_type>::other	node_allocator_type;
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
				protected:
					Compare comp;
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					value_compare (Compare c) : comp(c) {}

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
				this->clear();
				this->_alloc.deallocate(this->_root, 1);
			}

// -----------  OPERATOR = OVERLOAD -----------

			map& operator= (map const &rhs)
			{
				if (this != &rhs)
				{
					this->clear();
					this->insert(rhs.begin(), rhs.end());
				}
				return (*this);
			}

// -----------  ITERATORS -----------

			iterator begin() { return iterator(leftmost(this->_root)); }
			const_iterator begin() const { return const_iterator(leftmost(this->_root)); }

			iterator end() { return iterator(rightmost(this->_root)); }
			const_iterator end() const { return const_iterator(rightmost(this->_root)); }

			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

// ----------- CAPACITY -----------

			bool empty(void) const
			{
				return (this->_size == 0 ? true : false);
			}

			size_type size(void) const
			{
				return (this->_size);
			}

			size_type max_size(void) const
			{
				return (this->_alloc.max_size());
			}

// ----------- ELEMENT ACCESS -----------

			mapped_type& operator[] (const key_type& k)
			{
				return (this->insert(value_type(k, mapped_type()))).first->second;
			}

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

			void erase(iterator position)
			{
				this->_del_node(position.base());
			}

			size_type erase(const key_type& k)
			{
				iterator it = this->find(k);

				if (it == this->end())
					return (0);
				this->_del_node(it.base());
				return (1);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last) 
					this->erase(first++);
			}

			void swap(map& x)
			{
				node_ptr		tmp_root = this->_root;
				key_compare		tmp_cmp = this->_key_cmp;
				allocator_type	tmp_alloc = this->_alloc;
				size_type		tmp_size = this->_size;

				this->_root = x._root;
				x._root = tmp_root;
				this->_key_cmp = x._key_cmp;
				x._key_cmp = tmp_cmp;
				this->_alloc = x._alloc;
				x._alloc = tmp_alloc;
				this->_size = x._size;
				x._size = tmp_size;
			}

			void clear(void)
			{
				if (this->_size == 0)
					return ;
				erase(begin(), end());
			}

// -----------  OBSERVERS -----------

			key_compare key_comp(void) const
			{
				return (this->_key_cmp);
			}

			value_compare value_comp(void) const
			{
				return (this->_val_cmp);
			}

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
				node_ptr	curr = this->_root;

				while (curr && (this->_key_cmp(curr->data.first, k) || this->_key_cmp(k, curr->data.first)))
				{
					if (this->_key_cmp(k, curr->data.first))
						curr = curr->left;
					else
						curr = curr->right;
				}
				if (curr)
					return (const_iterator(curr));
				else
					return (this->end());
			}

			size_type count(const key_type& k) const
			{
				return (find(k) != this->end() ? 1 : 0);
			}

			iterator lower_bound(const key_type& k)
			{
				iterator	it_beg = this->begin();
				iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (!this->_key_cmp(it_beg->first, k))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator	it_beg = this->begin();
				const_iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (!this->_key_cmp(it_beg->first, k))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			iterator upper_bound(const key_type& k)
			{
				iterator	it_beg = this->begin();
				iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (this->_key_cmp(k, it_beg->first))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator	it_beg = this->begin();
				const_iterator	it_end = this->end();

				while (it_beg != it_end)
				{
				if (this->_key_cmp(k, it_beg->first))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			ft::pair<iterator,iterator> equal_range(const key_type& k)
			{
				ft::pair<iterator, iterator> ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return (ret);
			}

			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				ft::pair<const_iterator, const_iterator> ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return (ret);
			}

// -----------  ALLOCATOR -----------

			allocator_type get_allocator() const
			{
				return (this->_alloc);
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

			void _del_node(node_ptr to_del)
			{
				if (!to_del->left)
				{
					if (!to_del->parent)
						this->_root = to_del->right;
					else if (to_del == to_del->parent->left)
						to_del->parent->left = to_del->right;
					else
						to_del->parent->right = to_del->right;
					if (to_del->right)
						to_del->right->parent = to_del->parent;
				}
				else if (!to_del->right)
				{
					if (!to_del->parent)
						this->_root = to_del->left;
					else if (to_del == to_del->parent->left)
						to_del->parent->left = to_del->left;
					else
						to_del->parent->right = to_del->left;
					to_del->left->parent = to_del->parent;
				}
				else
				{
					node_ptr	successor = leftmost(to_del->right);
					if (!(to_del == successor->parent))
					{
						if (successor == successor->parent->left)
							successor->parent->left = successor->right;
						else
							successor->parent->right = successor->right;
						if (successor->right != NULL)
							successor->right->parent = successor->parent;
						successor->right = to_del->right;
						successor->right->parent = successor;
					}
					if (!to_del->parent)
						this->_root = successor;
					else if (to_del == to_del->parent->left)
						to_del->parent->left = successor;
					else
						to_del->parent->right = successor;
					successor->parent = to_del->parent;
					successor->left = to_del->left;
					successor->left->parent = successor;
				}
				--this->_size;
				this->_alloc.deallocate(to_del, 1);
			}
	};

// -----------   Non-member function overloads  -----------

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif