//Reversing a Queue

//You are given a queue Q, and your task is to reverse the elements of the queue. You are only allowed to use the following standard queue operations:
//
//enqueue(x): Add an item x to the rear of the queue.
//dequeue(): Remove an item from the front of the queue.
//empty(): Check if the queue is empty or not.

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void print(queue<int>& q)
{
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
}

// Function to reverse the queue
void reverseQueue(queue<int>& q)
{
    stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

int main()
{
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);
    q.push(80);
    q.push(90);
    q.push(100);

    reverseQueue(q);
    print(q);
}


/*
 
 // C++ code for reversing a queue
 #include <bits/stdc++.h>
 using namespace std;

 // Utility function to print the queue
 void printQueue(queue<int> q)
 {
     while (!q.empty()) {
         cout << q.front() << " ";
         q.pop();
     }
 }

 // Recursive function to reverse the queue
 void reverseQueue(queue<int>& q)
 {
     // Base case
     if (q.empty())
         return;

     // Dequeue current item (from front)
     long long int data = q.front();
     q.pop();

     // Reverse remaining queue
     reverseQueue(q);

     // Enqueue current item (to rear)
     q.push(data);
 }

 // Driver code
 int main()
 {
     queue<int> q;
     q.push(56);
     q.push(27);
     q.push(30);
     q.push(45);
     q.push(85);
     q.push(92);
     q.push(58);
     q.push(80);
     q.push(90);
     q.push(100);
     reverseQueue(q);
     printQueue(q);
 }
 
 */
