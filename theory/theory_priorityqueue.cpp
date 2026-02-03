// C++ program to demonstrate
// min heap for priority queue
//implemented as heap data structure
//efficient for priority based processing
//(max-heap by default)

#include <iostream>
#include <queue>
#include <string>

using namespace std;



struct Person{
    std::string name;
    int age;
};




struct Task{
    std::string name;
    int priority;
    
    //to help organise priority queue based on priority attribute
    bool operator<(const Task& other) const{
        return priority < other.prirority; //to evaluate heap, based on pspecific attribute riority
    }
};



void showpq(priority_queue<int, vector<int>, greater<int> > g)
{
    while (!g.empty()) {
        cout << ' ' << g.top();
        g.pop();
    }
    cout << '\n';
}

void showArray(int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

// Driver Code
int main()
{
    int arr[6] = { 10, 2, 4, 8, 6, 9 };
    priority_queue<int, vector<int>, greater<int> > gquiz(arr, arr + 6);//min-heap

    cout << "Array: ";
    showArray(arr, 6);

    cout << "Priority Queue : ";
    showpq(gquiz);

    
    
    std::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(33);
    pq.push(32);
    
    int top = pq.top();//highest priority
    
    while (!pq.empty()){
        std::cout << pq.top()<<std::endl;
        pq.pop();
    }
    
    
    std::priority_queue<Task> tasks;
    tasks.push({"Email",2});
    tasks.push({"Coffee break",6});
    
    
    //lambda comparators
    //compare by age
    auto cmp = [](const Person& a, const Person& b){
        return a.age > b.age;
    };
    std::priority_queue<Person, std::vector<Person>, decltype(cmp)> people(cmp);
    //highly useful when you need to prioritise structure based on certain parameter
    
    
    //to improve the performance, if the size of elements is known
    std::vector<int> v;
    v.reserve(1000);
    std::priority_queue<int> pqq(v.begin(),v.end());
    pqq.emplace(11);
    
    
    
    
    return EXIT_SUCCESS;
}
//prints 2 4 6 8 9 10

