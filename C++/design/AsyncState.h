#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <functional>
using namespace std;

namespace AsyncCallbackImpl {

    using Caller = void*;
    using State = void*;

    class IAsyncState
    {
    public:
        virtual Caller GetCaller() = 0;
        virtual State GetState() = 0;
        virtual bool IsCompleted() = 0;
        virtual bool GetStatus() = 0;
    };

#define STATIC_CALLBACK(_Method) s_##_Method
#define DEFINE_STATIC_CALLBACK(_Type, _Method) \
    static void STATIC_CALLBACK(_Method)(IAsyncState* result) \
    { \
        auto thisPointer = static_cast<_Type*>(result->GetCaller()); \
        thisPointer->_Method(result); \
    }

    typedef void (*Callback)(IAsyncState* state);
    class AsyncStateBase : public IAsyncState
    {
    protected:
        Caller caller;
        State state;
        Callback callback;
        bool completed;
        int hr;
        bool isInit;

    public:
        AsyncStateBase()
        {
            caller = nullptr;
            state = nullptr;
            callback = nullptr;
            completed = false;
            hr = -1;
            isInit = false;
        }

        AsyncStateBase(const AsyncStateBase&) = delete;
        AsyncStateBase operator=(AsyncStateBase) = delete;

        virtual bool Init(Caller caller, Callback callback, State state)
        {
            if (!isInit) {
                this->caller = caller;
                this->callback = callback;
                this->state = state;
                isInit = true;
                return true;
            }
            return false;
        }

        virtual Caller GetCaller() {
            return caller;
        }

        virtual State GetState() {
            return state;
        }

        virtual bool IsCompleted() {
            return completed;
        }

        virtual bool GetStatus() {
            return hr;
        }

        virtual bool Complete(int hr = -1) {
            if (!completed) {
                completed = true;
                this->hr = hr;
                callback(this);
                return true;
            }
            return false;
        }
    };

    template <class Result>
    class AsyncState : public AsyncStateBase
    {
    private:
        Result result;

    public:
        AsyncState() : AsyncStateBase() {}
        virtual bool Complete(Result result)
        {
            if (!completed) {
                completed = true;
                this->result = result;
                callback(this);
                return true;
            }
            return false;
        }

        Result GetResult()
        {
            return result;
        }
    };

    template <>
    class AsyncState<void> : public AsyncStateBase
    {
    public:
        AsyncState() : AsyncStateBase() {}
        virtual bool Complete()
        {
            return AsyncStateBase::Complete();
        }
    };
}