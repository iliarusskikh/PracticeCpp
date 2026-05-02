int a;

int main () {
    std::cout << a;
} // Output: 0
//Since a has static storage duration and no initializer, it is guaranteed to be zero-initialized. Had a been defined as a local non-static variable inside main(), this would not have happened.
