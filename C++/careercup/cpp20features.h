#pragma once
#include "../Header.h"
#include <experimental/coroutine>
#include <optional>

class CPP20Features {
	class Coroutine {
    public:
        cppcoro::task<int> someAsyncTask()
        {
            int result;
            // get the result somehow
            co_return result;
        }

        // task<> is analog of void for normal function
        cppcoro::task<> usageExample()
        {
            // creates a new task but doesn't start executing the coroutine yet
            cppcoro::task<int> myTask = someAsyncTask();
            // ...
            // Coroutine is only started when we later co_await the task.
            auto result = co_await myTask;
        }

        // will lazily generate numbers from 0 to 9
        cppcoro::generator<std::size_t> getTenNumbers()
        {
            std::size_t n{ 0 };
            while (n != 10)
            {
                co_yield n++;
            }
        }

        void printNumbers()
        {
            for (const auto n : getTenNumbers())
            {
                std::cout << n;
            }
        }
	};
};