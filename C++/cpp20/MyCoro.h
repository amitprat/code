#include <coroutine>

#include "../header.h"

class Coro {
   public:
    class promise_type {
       public:
        promise_type() = default;
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        Coro get_return_object() { return {}; }
        void unhandled_exception() {}
    };
};