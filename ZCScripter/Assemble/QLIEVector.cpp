#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<Assemble.h>
using namespace std;

namespace QLIE
{
	inline _QLIEVarient QLIEVector::operator[](const unsigned _k_Hash) noexcept
	{
		return _base[_k_Hash];
	}
	const inline vector<_QLIEVarient>::iterator QLIEVector::begin() noexcept
	{
		return _base.begin();
	}
	const inline vector<_QLIEVarient>::iterator QLIEVector::end() noexcept
	{
		return _base.end();
	}
	const inline vector<_QLIEVarient>::reverse_iterator QLIEVector::rbegin() noexcept
	{
		return _base.rbegin();
	}
	const inline vector<_QLIEVarient>::reverse_iterator QLIEVector::rend() noexcept
	{
		return _base.rend();
	}
	const inline size_t QLIEVector::size() noexcept
	{
		return _base.size();
	}
	const inline void QLIEVector::push_back(const _QLIEVarient& _Val) noexcept
	{
		return _base.push_back(_Val);
	}
	const inline void QLIEVector::push_front(const _QLIEVarient& _Val) noexcept
	{
		reverse(_base.begin(), _base.end());
		_base.push_back(_Val);
		reverse(_base.begin(), _base.end());
	}
	const inline void QLIEVector::pop_back() noexcept
	{
		return _base.pop_back();
	}
	const inline void QLIEVector::resize(const size_t _Val) noexcept
	{
		return _base.resize(_Val);
	}
	const inline void QLIEVector::clear() noexcept
	{
		return _base.clear();
	}
}
