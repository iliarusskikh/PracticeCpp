//Given a stack that supports push and pop operations, your task is to implement a queue using one or more instances of that stack along with its operations.
//
//enqueue(q, x):
//
//While stack1 is not empty, push everything from stack1 to stack2.
//Push x to stack1 (assuming size of stacks is unlimited).
//Push everything back to stack1.
//dequeue(q):
//
//If stack1 is empty then error.
//Pop an item from stack1 and return it.


//By Making Enqueue Operation Costly
/*#include <bits/stdc++.h>
using namespace std;

struct Queue {
    stack<int> s1, s2;

    void enqueue(int x) {

        // Move all elements from s1 to s2
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        // Push item into s1
        s1.push(x);

        // Push everything back to s1
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    // Dequeue an item from the queue
    int dequeue() {

        // if first stack is empty
        if (s1.empty()) {
            return -1;
        }

        // Return top of s1
        int x = s1.top();
        s1.pop();
        return x;
    }
};

// Driver code
int main() {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << q.dequeue() << '\n';
    cout << q.dequeue() << '\n';
    cout << q.dequeue() << '\n';

    return 0;
}


*/



//Queue Implementation Using One Stack and Recursion Time Complexity: O(n), for push operation
//enqueue(x)
//
//Push the element x onto stack1.
//dequeue()
//
//If stack1 is empty, return an error.
//If stack1 has only one element, return it.
//Otherwise, recursively pop all elements from stack1, store the popped element in a variable res, then push res back into stack1 and return res.
#include <bits/stdc++.h>
using namespace std;

struct Queue {
    stack<int> s;

    // Enqueue an item to the queue
    void enqueue(int x) {
        s.push(x);
    }

    // Dequeue an item from the queue
    int dequeue() {
        if (s.empty()) {
            return -1;
        }

        int x = s.top();        // pop an item from the stack
        s.pop();

        // if stack becomes empty, return the popped item
        if (s.empty())
            return x;

        // recursive call
        int item = dequeue();

        // push popped item back to the stack
        s.push(x);

        // return the result of dequeue() call
        return item;
    }
};

int main() {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << q.dequeue() << '\n';
    cout << q.dequeue() << '\n';
    cout << q.dequeue() << '\n';

    return 0;
}
