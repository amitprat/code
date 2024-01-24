#include "../header.h"

class SortStack
{
public:
    static void test()
    {
        stack<int> st;
        st.push(3);
        st.push(1);
        st.push(2);
        st.push(7);
        st.push(4);
        st.push(6);
        st.push(5);

        SortStack obj;
        obj.sortIterative(st);

        cout << "Stack: ";
        while (!st.empty())
        {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }

    void sortIterative(stack<int> &st)
    {
        stack<int> aux;

        while (!st.empty())
        {
            auto val = st.top();
            st.pop();

            insertSortedOrder(aux, st, val);
        }

        swap(st, aux);
    }

    void insertSortedOrder(stack<int> &aux, stack<int> &st, int val)
    {
        while (!aux.empty() && val > aux.top())
        {
            st.push(aux.top());
            aux.pop();
        }

        aux.push(val);
    }

    void sortUsingRecursion(stack<int> &st)
    {
        if (st.empty())
            return;

        auto cur = st.top();
        st.pop();

        sortUsingRecursion(st);

        insertAtBottom(st, cur);
    }

    void insertAtBottom(stack<int> &st, int cur)
    {
        if (st.empty() || cur < st.top())
        {
            st.push(cur);
            return;
        }

        auto val = st.top();
        st.pop();

        insertAtBottom(st, cur);
        st.push(val);
    }

    friend std::ostream &operator<<(std::ostream &out, std::stack<int> &st)
    {
        stack<int> newSt;
        while (!st.empty())
        {
            out << st.top() << " ";
            newSt.push(st.top());
            st.pop();
        }

        while (!newSt.empty())
        {
            st.push(newSt.top());
            newSt.pop();
        }

        return out;
    }
};