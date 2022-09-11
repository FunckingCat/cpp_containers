/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidzh <davidzh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:20:57 by hexa              #+#    #+#             */
/*   Updated: 2022/09/11 19:43:03 by davidzh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;

		pair (void)
		: first(), second()
		{}

		pair (const T1& a, const T2& b)
		: first(a), second(b)
		{}

		template <typename U1, typename U2>
		pair (const pair<U1, U2>& p)
		: first(p.first), second(p.second)
		{}
	};

	template <typename T1, typename T2>
	inline bool
	operator==	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template <typename T1, typename T2>
	inline bool
	operator<	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (x.first < y.first
			|| (!(y.first < x.first) && x.second < y.second));
	}

	template <typename T1, typename T2>
	inline bool
	operator!=	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(x == y));
	}

	template <typename T1, typename T2>
	inline bool
	operator>	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (y < x);
	}

	template <typename T1, typename T2>
	inline bool
	operator<=	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(y < x));
	}

	template <typename T1, typename T2>
	inline bool
	operator>=	(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(x < y));
	}

	template <typename T1, typename T2>
	inline pair<T1, T2>
	makepair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}

#endif
