#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

namespace ft 
{
	template <typename T>
	struct node
	{
		T			data;
		node*		parent;
		node*		left;
		node*		right;
		int			height;

		node(const T& src = T()) : data(src), parent(NULL), left(NULL), right(NULL), height(1) 
		{};
	};

	template <typename T>
	node<T>* rightmost(node<T>* node)
	{
		while (node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	node<T>* leftmost(node<T>* node)
	{
		while (node->left != NULL)
			node = node->left;
		return (node);
	}

	template <typename T, typename node_type>
	class tree_iterator : ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >
	{
		public:
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::iterator_category iterator_category;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::value_type		value_type;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::difference_type	difference_type;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::reference			reference;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::pointer			pointer;

		private:
			node_type* _node;

		public:

// -----------  CONSTRUCTORS -----------

			tree_iterator(node_type* src = NULL) : _node(src)
			{}

			tree_iterator(const tree_iterator &src)
			{
				*this = src;
			}	

// -----------  DESTRUCTOR -----------

			~tree_iterator()
			{}

// -----------  OPERATOR OVERLOADS -----------

			tree_iterator& operator= (tree_iterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_node = rhs._node;
				return (*this);
			}

			node_type* base() const
			{
				return (this->_node);
			}

			reference operator* (void) const
			{
				return (this->_node->data);
			}

			pointer operator-> (void) const
			{
				return (&this->_node->data);
			}

			tree_iterator& operator++ (void)
			{
				if (this->_node->right != NULL)
					this->_node = leftmost(this->_node->right);
				else
				{
					node_type*	child = this->_node;
					this->_node = this->_node->parent;
					while (this->_node && child == this->_node->right)
					{
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}

			tree_iterator operator++ (int)
			{
				tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			tree_iterator& operator-- (void)
			{
				if (this->_node->left != NULL)
					this->_node = rightmost(this->_node->left);
				else
				{
					node_type*	child = this->_node;
					this->_node = this->_node->parent;
					while (this->_node && child == this->_node->left)
					{
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}

			tree_iterator operator-- (int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			template <class U>
			bool operator== (const tree_iterator<U, node_type> &rhs) const
			{
				return (this->_node == rhs._node);
			}

			template <class U>
			bool operator!= (const tree_iterator<U, node_type> &rhs) const
			{
				return (this->_node != rhs._node);
			}
	};
}

#endif