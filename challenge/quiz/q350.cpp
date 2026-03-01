#include <functional>
#include <iostream>

struct Q {
    int v = 0;

    Q() { std::cout << "D"; }
    Q(const Q&) { std::cout << "C"; }
    Q(Q&&) { std::cout << "M"; }

    void change() { ++v; }
    void func() { std::cout << v; }
};

void takeQfunc(std::function<void(Q)> qfunc) { //takes by value/copy std::function<void(Q)> qfunc
    Q q;
    q.func();
    qfunc(q);
    q.func();
}

int main() {
    takeQfunc([](Q&& q) { q.change(); });
}



/*
 First, a Q instance is default-constructed in takeQfunc(), printing D.
 Then q.func() is called, which prints 0.
 Next, we call qfunc(q). Although the lambda's parameter list specifies that it takes an rvalue reference Q&&, the q is actually first passed to qfunc, which takes a plain Q by value. A copy is made, printing C. Then, the std::function::operator() std::forwards its argument to the lambda, and the lambda's rvalue reference can bind to the newly copied q. Since the reference binds to this copy rather than the original, q.change() doesn't change the original q.
 Then, q.func() is called again, which prints 0.

 the function object itself expects its argument by value (Q, not Q&& or Q&).
 Binding an rvalue reference to a temporary does not call a constructor
 It's just a reference binding — no copy, no move.
 
 
 D – default construction of local q
 0 – first print of q.v
 C – copy of q when calling qfunc(q) (because std::function<void(Q)> takes by value)
 0 – second print of q.v (original object never changed)
 */
