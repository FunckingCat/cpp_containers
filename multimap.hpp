/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: YanYan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:30:56 by YanYan            #+#    #+#             */
/*   Updated: 2020/07/19 02:35:38 by YanYan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

namespace ft
{
	template <typename _Key, typename _Tp,
			typename _Compare = ft::less<_Key>,
			typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
		class multimap
		{
			public:
				typedef _Key						key_type;
				typedef _Tp							mapped_type;
				typedef ft::pair<const _Key, _Tp>	value_type;
				typedef _Compare					key_compare;
				typedef _Alloc						allocator_type;

			private:
				typedef typename _Alloc::value_type	_Alloc_value_type;

			public:
				class value_compare
				: public ft::binary_function<value_type, value_type, bool>
				{
					friend class multimap<_Key, _Tp, _Compare, _Alloc>;
					protected:
						_Compare comp;

						value_compare(_Compare c)
						: comp(c)
						{}

					public:
						bool operator()(const value_type& x, const value_type& y) const
						{
							return (comp(x.first, y.first));
						}
				};

			private:
				typedef typename _Alloc::template
						rebind<value_type>::other _Pair_alloc_type;

				typedef _bin_tree<key_type, value_type, _Select1st<value_type>,
						 key_compare, _Pair_alloc_type> _Rep_type;
				_Rep_type _M_t;

				typedef _Pair_alloc_type _Alloc_traits;

			public:
				typedef typename _Alloc_traits::pointer				pointer;
				typedef typename _Alloc_traits::const_pointer		const_pointer;
				typedef typename _Alloc_traits::reference			reference;
				typedef typename _Alloc_traits::const_reference		const_reference;
				typedef typename _Rep_type::iterator				iterator;
				typedef typename _Rep_type::const_iterator			const_iterator;
				typedef typename _Rep_type::size_type				size_type;
				typedef typename _Rep_type::difference_type			difference_type;
				typedef typename _Rep_type::reverse_iterator		reverse_iterator;
				typedef typename _Rep_type::const_reverse_iterator	const_reverse_iterator;

				multimap (void)
				: _M_t()
				{}

				explicit
				multimap(const _Compare& comp,
					 const allocator_type& a = allocator_type())
				: _M_t(comp, _Pair_alloc_type(a))
				{}

				multimap(const multimap& x)
				: _M_t(x._M_t)
				{}

				template<typename _InputIterator>
					multimap(_InputIterator first, _InputIterator last)
					: _M_t()
					{
						_M_t._M_insert_equal(first, last);
					}

				template<typename _InputIterator>
					multimap(_InputIterator first, _InputIterator last,
						 const _Compare& comp,
						 const allocator_type& a = allocator_type())
					: _M_t(comp, _Pair_alloc_type(a))
					{
						_M_t._M_insert_equal(first, last);
					}

				multimap&
				operator=(const multimap& x)
				{
					_M_t = x._M_t;
					return *this;
				}

				allocator_type
				get_allocator (void) const
				{
					return (allocator_type(_M_t.get_allocator()));
				}

				iterator
				begin (void)
				{
					return (_M_t.begin());
				}

				const_iterator
				begin (void) const
				{
					return (_M_t.begin());
				}

				iterator
				end (void)
				{
					return (_M_t.end());
				}

				const_iterator
				end (void) const
				{
					return (_M_t.end());
				}

				reverse_iterator
				rbegin (void)
				{
					return (_M_t.rbegin());
				}

				const_reverse_iterator
				rbegin (void) const
				{
					return (_M_t.rbegin());
				}

				reverse_iterator
				rend (void)
				{
					return (_M_t.rend());
				}

				const_reverse_iterator
				rend (void) const
				{
					return (_M_t.rend());
				}

				bool
				empty (void) const
				{
					return (_M_t.empty());
				}

				size_type
				size (void) const
				{
					return (_M_t.size());
				}

				size_type
				max_size (void) const
				{
					return (_M_t.max_size());
				}

				iterator
				insert (const value_type& x)
				{
					return (_M_t._M_insert_equal(x));
				}

				iterator
				insert (iterator position, const value_type& x)
				{
					return (_M_t._M_insert_equal_(position, x));
				}

				template<typename _InputIterator>
					void
					insert(_InputIterator first, _InputIterator last)
					{
						_M_t._M_insert_equal(first, last);
					}

				void
				erase(iterator position)
				{
					_M_t.erase(position);
				}

				size_type
				erase(const key_type& x)
				{
					return( _M_t.erase(x));
				}

				void
				erase(iterator first, iterator last)
				{
					_M_t.erase(first, last);
				}

				void
				swap(multimap& x)
				{
					_M_t.swap(x._M_t);
				}

				void
				clear (void)
				{
					_M_t.clear();
				}

				key_compare
				key_comp (void) const
				{
					return (_M_t.key_comp());
				}

				value_compare
				value_comp (void) const
				{
					return (value_compare(_M_t.key_comp()));
				}

				iterator
				find(const key_type& x)
				{
					return (_M_t.find(x));
				}

				const_iterator
				find(const key_type& x) const
				{
					return (_M_t.find(x));
				}

				size_type
				count(const key_type& x) const
				{
					return (_M_t.count(x));
				}

				iterator
				lower_bound(const key_type& x)
				{
					return (_M_t.lower_bound(x));
				}

				const_iterator
				lower_bound(const key_type& x) const
				{
					return (_M_t.lower_bound(x));
				}

				iterator
				upper_bound(const key_type& x)
				{
					return (_M_t.upper_bound(x));
				}

				const_iterator
				upper_bound(const key_type& x) const
				{
					return (_M_t.upper_bound(x));
				}

				ft::pair<iterator, iterator>
				equal_range(const key_type& x)
				{
					return (_M_t.equal_range(x));
				}

				ft::pair<const_iterator, const_iterator>
				equal_range(const key_type& x) const
				{
					return (_M_t.equal_range(x));
				}

				template<typename _K1, typename _T1, typename _C1, typename _A1>
					friend bool
					operator==(const multimap<_K1, _T1, _C1, _A1>&,
				 const multimap<_K1, _T1, _C1, _A1>&);

				template<typename _K1, typename _T1, typename _C1, typename _A1>
					friend bool
					operator<(const multimap<_K1, _T1, _C1, _A1>&,
				const multimap<_K1, _T1, _C1, _A1>&);
	};

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator==(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							 const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (x._M_t == y._M_t);
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator<(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (x._M_t < y._M_t);
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator!=(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							 const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (!(x == y));
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator>(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (y < x);
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator<=(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							 const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (!(y < x));
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline bool
		operator>=(const multimap<_Key, _Tp, _Compare, _Alloc>& x,
							 const multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			return (!(x < y));
		}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
		inline void
		swap(multimap<_Key, _Tp, _Compare, _Alloc>& x,
				 multimap<_Key, _Tp, _Compare, _Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
