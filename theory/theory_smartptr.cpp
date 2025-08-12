#include <memory>
#include <iostream>

using namespace std;

/*auto_ptr
unique_ptr
shared_ptr
weak_ptr
*/

int main() {
    
    // Pointer declaration
    auto_ptr<int> ptr1(new int(10));
    cout << *ptr1 << endl;
    
    // Transfer ownership to
    // pointer ptr2,
    auto_ptr<int> ptr2 = ptr1;
    cout << *ptr2;
    
    
    //unique_ptr stores one pointer only at a time. We cannot copy unique_ptr, only transfer ownership of the object to another unique_ptr using the move() method.
    unique_ptr<int> P1(13)
    unique_ptr<int> P2;

    // Copy the addres of P1 into p2
    P2 = move(P1);
    
    //By using shared_ptr, more than one pointer can point to same object at a time, and it will maintain a reference counter using the use_count() method.
    
    shared_ptr<int> P1(11)
    shared_ptr<int> P2;
    // P1 and P2 are pointing
    // to same object
    P2 = P1;
    cout << P1.use_count();
    
    //weak_ptr is a smart pointer that holds a non-owning reference to an object. It's much more similar to shared_ptr except it will not maintain a reference counter.
    // Create shared_ptr Smart Pointer
    shared_ptr<int> P1(16);
    
    // Created a weak_ptr smart pointer
    weak_ptr<int> P2(P1);
    // Returns the number of shared_ptr
    // objects that manage the object
    cout << P2.use_count();
    
    
    return 0;
}
