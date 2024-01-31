#pragma once

template<class T>class Property
{
private:
	T& r;
public:
	Property(T& ref) : r(ref) {}
	operator T(){ return r; }
	void operator =(T v) {	r = v; }
	T operator +(T v) { return r + v; }
	T operator -(T v) { return r - v; }
	T operator *(T v) { return r * v; }
	void operator +=(T v) { r += v; }
	void operator -=(T v) { r -= v; }
	void operator *=(T v) { r *= v; }
	T* operator&() { return &r; }
	T* operator->() { return &r; }
	bool operator >(T v) { return r > v; }
	bool operator <(T v) { return r < v; }
	bool operator ==(T v) { return r == v; }
	
};