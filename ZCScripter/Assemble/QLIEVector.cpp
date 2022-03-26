#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<Assemble.h>
using namespace std;

namespace QLIE
{
	_QLIEVarient QLIEVector::operator[](const unsigned _k_Hash) noexcept
	{
		return _base[_k_Hash];
	}
	
	vector<allocator<_QLIEVarient>::value_type>::iterator QLIEVector::begin() noexcept
	{
		return _base.begin();
	}
	vector<allocator<_QLIEVarient>::value_type>::iterator QLIEVector::end() noexcept
	{
		return _base.end();
	}
	vector<std::allocator<_QLIEVarient>::value_type>::reverse_iterator QLIEVector::rbegin() noexcept
	{
		return _base.rbegin();
	}
	vector<std::allocator<_QLIEVarient>::value_type>::reverse_iterator QLIEVector::rend() noexcept
	{
		return _base.rend();
	}
	const size_t QLIEVector::size() noexcept
	{
		return _base.size();
	}
	const void QLIEVector::push_back(const _QLIEVarient& _Val) noexcept
	{
		return _base.push_back(_Val);
	}
	const void QLIEVector::push_front(const _QLIEVarient& _Val) noexcept
	{
		reverse(_base.begin(), _base.end());
		_base.push_back(_Val);
		reverse(_base.begin(), _base.end());
	}
	const void QLIEVector::pop_back() noexcept
	{
		return _base.pop_back();
	}
	const void QLIEVector::resize(const size_t _Val) noexcept
	{
		return _base.resize(_Val);
	}
	const void QLIEVector::clear() noexcept
	{
		return _base.clear();
	}
	QLIEVector::QLIEVector()
	{
	}
	QLIEVector::QLIEVector(const size_t k_PreAllocate)
	{
		_base.resize(k_PreAllocate);
	}
	QLIEVector::QLIEVector(const vector<_QLIEVarient>& k_PreBase)
	{
		_base.assign(k_PreBase.begin(), k_PreBase.end());
	}
	QLIEVector::QLIEVector(QLIEVector& k_PreBase)
	{
		_base.assign(k_PreBase.begin(), k_PreBase.end());
		
	}
}
