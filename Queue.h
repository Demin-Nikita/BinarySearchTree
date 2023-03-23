#pragma once

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual void enQueue(const T& e) = 0;
	virtual const T deQueue() = 0;
	virtual bool isEmpty() = 0;

	class QueueException {
	public:
		std::string getMessage() const;
	private:
		std::string message_;
	};
};