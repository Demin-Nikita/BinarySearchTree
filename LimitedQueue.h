#pragma once
#include <iostream>
#include "Queue.h"

template <class T>
class LimitedQueue : public Queue<T>
{
private:
	T* array_;
	size_t top_;
	size_t bot_;
	size_t size_;
	size_t count_;
	void swap(LimitedQueue<T>& src);

public:
	LimitedQueue(size_t size = 100);
	LimitedQueue(const LimitedQueue<T>& src);
	LimitedQueue(LimitedQueue<T>&& src) = delete;
	LimitedQueue& operator=(const LimitedQueue<T>& src) = delete;
	LimitedQueue& operator=(LimitedQueue<T>&& src) = delete;
	~LimitedQueue() = default;
	bool isEmpty();
	void enQueue(const T& e);
	const T deQueue();

	//-------------------------------exception classes--------------------------------------------------//
		// QueueUnderflow
	class QueueOverflow : public Queue<T>::QueueException {
	public:
		QueueOverflow(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};

	// QueueOverflow
	class QueueUnderflow : public Queue<T>::QueueException {
	public:
		QueueUnderflow(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};

	// WrongQueueSize
	class WrongQueueSize : public Queue<T>::QueueException {
	public:
		WrongQueueSize(const std::string& message);
		std::string getMessage() const;
	private:
		std::string message_;
	};
};
//--------------------------------------------------------------------------------------------------//


//-------------------------------realization of exception classes-----------------------------------//
// QueueUnderflow
template <class T>
LimitedQueue<T>::QueueUnderflow::QueueUnderflow(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedQueue<T>::QueueUnderflow::getMessage() const { return message_; }

// QueueOverflow
template <class T>
LimitedQueue<T>::QueueOverflow::QueueOverflow(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedQueue<T>::QueueOverflow::getMessage() const { return message_; }

// WrongQueueSize
template <class T>
LimitedQueue<T>::WrongQueueSize::WrongQueueSize(const std::string& message) : message_(message) {}
template <class T>
std::string LimitedQueue<T>::WrongQueueSize::getMessage() const { return message_; }
//--------------------------------------------------------------------------------------------------//


//-------------------------------realization of LimitedQueue class----------------------------------//
template <class T>
LimitedQueue<T>::LimitedQueue(size_t size) : size_(size), top_(0), bot_(0), count_(0) {
	try {
		if (size <= 100000) { array_ = new T[size + 1]; }
		else { throw WrongQueueSize("Wrong queue size!"); }
	}
	catch (const LimitedQueue<T>::WrongQueueSize& e) {
		std::cerr << "Error: " << e.getMessage() << "\n";
		exit(1);
	}
}

template <class T>
LimitedQueue<T>::LimitedQueue(const LimitedQueue<T>& src) : size_(src.size_), top_(src.top_), count_(src.count_) {
	try {
		if (src.size_ <= 100000) { array_ = new T[src.size_ + 1]; }
		else { throw WrongQueueSize("Wrong queue size!"); }
	}
	catch (const LimitedQueue<T>::WrongQueueSize& e) {
		std::cerr << "Error: " << e.getMessage() << "\n";
		exit(1);
	}
	for (size_t i = 1; i < src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

template <class T>
void LimitedQueue<T>::swap(LimitedQueue<T>& src) {
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
bool LimitedQueue<T>::isEmpty() { return top_ == bot_; }

template <class T>
void LimitedQueue<T>::enQueue(const T& e) {
	if (count_ == size_) { throw QueueOverflow("No space in the queue!"); }
	array_[(++top_) % (size_ + 1) + (top_ / size_)] = e;
	count_++;
}

template <class T>
const T LimitedQueue<T>::deQueue() {
	if (isEmpty()) { throw QueueUnderflow("Not enough elements in the queue!"); }
	count_--;
	return array_[(++bot_) % (size_ + 1) + (bot_ / size_)];
}
//--------------------------------------------------------------------------------------------------//