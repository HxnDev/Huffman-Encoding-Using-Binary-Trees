#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <typename T>
class Vector
{
	T* ptr;
	int size_;
	int c_index;
	int cap;

public:
	Vector() : ptr(NULL), size_(0), c_index(0), cap(0) {};

	Vector(int size) : size_(0), c_index(0), cap(size)
	{
		ptr = new T[cap];
	}

	Vector(int size, const T& iv) : size_(size), c_index(size_)
	{
		ptr = new T[size_];

		for (int i = 0; i < size_; i++)
			ptr[i] = iv;
	}

	~Vector()
	{
		delete[]ptr;
	}

	const T& operator = (const T& obj) // copies one vector to another
	{
		if (size_ == cap) {
			Vector<T> copy(*this);
			~*this;

			cap *= 2;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy.ptr[i];

			delete[]copy.ptr;
		}

		size_++;
		ptr[size_] = obj;
		return ptr[size_];
	}

	int size() {
		return size_;
	}

	void resize(int x) {
		if (x == cap)
			return;

		else if (x > cap) {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}

		else {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			if (size_ > cap)
				size_ = cap;

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}
	}

	bool empty() {
		if (size_ == -1)
			return true;

		return false;
	}

	void shrink_to_fit(int x) {

		Vector<T> copy(*this);
		delete[]ptr;

		cap = x;
		ptr = new T[cap];

		if (size_ > cap)
			size_ = cap;

		for (int i = 0; i < size_; i++)
			ptr[i] = copy[i];

		delete[]copy.ptr;
	}

	T& operator [] (int index) {
		return ptr[index];
	}

	void push_back(const T& value) {

		if (size_ == cap)
			this->resize(cap * 2);

		ptr[size_] = value;
		size_++;
	}

	void pop_back() {
		size_--;
	}

	void clear() {
		//c_index = 0;
		size_ = -1;
	}

	int capacity() {
		return cap;
	}

	bool search(T& item) {
		for (int i = 0; i < this->size_; i++) {
			if (ptr[i] == item)
				return true;
		}
		return false;
	}

	void display() {
		for (int i = 0; i < this->size_; i++)
			cout << ptr[i];

		cout << endl;
	}
};
