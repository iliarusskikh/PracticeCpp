//Implement Stack using Queues


//Implement a stack using queues. The stack should support the following operations:
//
//push(x): Insert element x onto the top of the stack.
//pop(): Remove the element from the top of the stack. If the stack is empty, do nothing.
//top(): Return the element at the top of the stack. If the stack is empty, return -1.
//size(): Return the number of elements in the stack.


#include <iostream>
#include <queue>
using namespace std;

class myStack {
    queue<int> q;

public:
    // push element on top
    void push(int x) {
        q.push(x);

        int sz = q.size();
        for (int i = 0; i < sz - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    // remove top element
    void pop() {
        if (!q.empty())
            q.pop();
    }

    // return top element
    int top() {
        if (q.empty())
            return -1;
        return q.front();
    }

    // return current size
    int size() {
        return q.size();
    }
};

int main() {
    myStack st;
    st.push(1);
    st.push(2);
    st.push(3);

    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    cout << st.size() << endl;
    return 0;
}
