#pragma once

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0;
	virtual const T& pop() = 0;
	virtual bool isEmpty() = 0;

	class StackException {
	public:
		std::string getMessage() const;
	private:
		std::string message_;
	};
};