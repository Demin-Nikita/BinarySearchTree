#pragma once
#include <iostream>
#include "Stack.h"

template <class T>
class LimitedStack : public Stack<T>
{
private:
	T* array_;
	size_t top_;
	size_t size_;
	void swap(LimitedStack<T>& src);

public:
	LimitedStack(size_t size = 100);
	LimitedStack(const LimitedStack<T>& src);
	LimitedStack(LimitedStack<T>&& src) = delete;
	LimitedStack& operator=(const LimitedStack<T>& src) = delete;
	LimitedStack& operator=(LimitedStack<T>&& src) = delete;
	~LimitedStack();
	bool isEmpty();
	void push(const T& e);
	const T& pop();
	const T& peek();

	//-------------------------------exception classes--------------------------------------------------//
		// StackUnderflow
	class StackOverflow : public Stack<T>::StackException {
	public:
		StackOverflow(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};

	// StackOverflow
	class StackUnderflow : public Stack<T>::StackException {
	public:
		StackUnderflow(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};

	// WrongStackSize
	class WrongStackSize : public Stack<T>::StackException {
	public:
		WrongStackSize(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};
};
//--------------------------------------------------------------------------------------------------//


//-------------------------------realization of exception classes-----------------------------------//
// StackUnderflow
template <class T>
LimitedStack<T>::StackUnderflow::StackUnderflow(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedStack<T>::StackUnderflow::getMessage() const { return message_; }

// StackOverflow
template <class T>
LimitedStack<T>::StackOverflow::StackOverflow(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedStack<T>::StackOverflow::getMessage() const { return message_; }

// WrongStackSize
template <class T>
LimitedStack<T>::WrongStackSize::WrongStackSize(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedStack<T>::WrongStackSize::getMessage() const { return message_; }
//--------------------------------------------------------------------------------------------------//


//-------------------------------realization of LimitedStack class----------------------------------//
template <class T>
LimitedStack<T>::LimitedStack(size_t size) : size_(size), top_(0) {
	try {
		if (size <= 100000) { array_ = new T[size + 1]; }
		else { throw WrongStackSize("Wrong stack size!"); }
	}
	catch (const LimitedStack<T>::WrongStackSize& e) {
		std::cerr << "Error: " << e.getMessage() << "\n";
		exit(1);
	}
}

template <class T>
LimitedStack<T>::LimitedStack(const LimitedStack<T>& src) : size_(src.size_), top_(src.top_) {
	try {
		if (src.size_ <= 100000) { array_ = new T[src.size_ + 1]; }
		else { throw WrongStackSize("Wrong stack size!"); }
	}
	catch (const LimitedStack<T>::WrongStackSize& e) {
		std::cerr << "Error: " << e.getMessage() << "\n";
		exit(1);
	}

	for (size_t i = 1; i < src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

template <class T>
LimitedStack<T>::~LimitedStack() { delete[] array_; }

template <class T>
void LimitedStack<T>::swap(LimitedStack<T>& src) {
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
bool LimitedStack<T>::isEmpty() { return top_ == 0; }

template <class T>
void LimitedStack<T>::push(const T& e) {
	if (top_ == size_) { throw StackOverflow("No space in the stack!"); }
	array_[++top_] = e;
}

template <class T>
const T& LimitedStack<T>::pop() {
	if (isEmpty()) { throw StackUnderflow("Not enough elements in the stack!"); }
	return array_[top_--];
}

template <class T>
const T& LimitedStack<T>::peek() {
	if (isEmpty()) { throw StackUnderflow("Not enough elements in the stack!"); }
	return array_[top_];
}
//--------------------------------------------------------------------------------------------------//