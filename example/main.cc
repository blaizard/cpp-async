#include "bzd.h"

#include <chrono>
#include <iostream>

void fct1();
void fct2();

bzd::platform::Stack<2000> stack1;
bzd::platform::Stack<2000> stack2;

int i = 0;

void fct1()
{
	while (i < 10)
	{
		std::cout << "Fct 1: " << i++ << std::endl;
		bzd::yield();
	}
}

/*
template <class V, class E>
class Promise : public bzd::Result<V, E>
{
public:
	virtual Result<bool> isReady() = 0;
};
*/

template <class T>
class Promise
{
public:
	Promise(T&& callack) : callack_{callack} {}
	bool isReady() const { return callack_(); }

private:
	T callack_;
};

uint64_t getTimestampMs()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

auto delay(const int timeMs)
{
	const auto timestampMs = getTimestampMs();
	return Promise([timestampMs, timeMs]() {
		const auto currentTimestampMs = getTimestampMs();
		if (currentTimestampMs < timestampMs + timeMs)
		{
			return false;
		}
		return true;
	});
}

void fct2()
{
	while (i < 10)
	{
		std::cout << "Fct 2: " << i++ << std::endl;
		bzd::yield();
	}
}

int main()
{
	int i = 100;
	bzd::Task task1{[&i] {
		while (i > 0)
		{
			std::cout << "Fct 1: " << i-- << std::endl;
			bzd::yield();
		}
		std::cout << "Fct 1: end" << std::endl;
	}};

	bzd::Task task2{[&i] {
		while (i > 0)
		{
			std::cout << "Fct 2: " << i-- << std::endl;
			bzd::yield();
		}
		std::cout << "Fct 2: end" << std::endl;
	}};

	task1.bind(stack1);
	task2.bind(stack2);

	const auto promise = delay(12);
	std::cout << promise.isReady() << std::endl;
	std::cout << getTimestampMs() << std::endl;

	bzd::getScheduler().addTask(task1);
	bzd::getScheduler().addTask(task2);

	bzd::getScheduler().start();

	return 0;
}
