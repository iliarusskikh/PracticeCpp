#include <iostream>
using namespace std;



template<typename T>
void swap(T& a, T& b)
    noexcept(noexcept(a.swap(b)))   // ← very common idiom
{
    a.swap(b);
}



template<typename T>
class Widget {
public:
    Widget(Widget&& other) noexcept
        : data(std::move(other.data))   // safe if data's move is noexcept
    {}

    // or even better – forwarding style
    template<typename U>
    Widget(U&& u) noexcept(noexcept(T(std::forward<U>(u))))
        : data(std::forward<U>(u)) {}
};



int divide(int a, int b){
    if(b == 0){
        throw "Division by zero error!"
    }
    
    return a/b;
}

//custom exception class
class DatabaseException : public std::exception{
    const char* what() const throw(){
        return "Database connection failed";
    }
};

//exception hierarchies
class NetworkError : public std::exception{};
class ConnectionTimeout : public NetworkError {};




//custom implementations
class FileException : public std::exception {
private:
    std::string m_message;
    
public:
    FileException(const std::string& filename, const std::string& error){
        m_message = "File error: " + filename + ", " + error;
    }
    
    //overrides what method
    const char* what() const throw(){
        return m_message.c_str();
    }
};


class TextFileExceptin: public FilException{
  //
};



//noexcept indicates that a function wont throw exceptions
//if throws, std::terminate is called
void safeFunction() noexcept{
    //wont throw exceptions
}


//conditional noexcept
//“This function is noexcept if and only if the move constructor of T is noexcept.”
tempalte <typename T>
void process(T&& value) noexcept(noexcept(std::is_nothrow_move_constructorible<T>::value)){
    //implemnetation
}

//using noexcept operatior
//evaluates at compile time whether an expression might throw an exception
void example(){
    //It returns true if that expression cannot throw
    constexpr bool canThrow = !noexcept(safeFunction());
    static_assert(!canThrow, "safeFunction should not throw");
}







int main()
{
    
    try
    {
       throw 'a';
    }
    
    throw 404; //integer exception
    throw "Error";// c-string exception
    throw std::runtime_error("Runtime error");
    throw std::out_of_range("index out of bounds");
    
    
    
    catch (int param)
    {
        cout << "int exception\n";
        
    }
    catch (const char* error){
        std::cout << error << std::endl;
    }
    
    //runtime_error..
    catch (std::exception& e){
        std::cout << e.what();
    }
    
    catch (...)
    {
        cout << "default exception\n"; //called
    }
    cout << "After Exception";//called
    
    
    
    /*
    try{
        throw FileException("data.txt", "not found");
    }
    catch (const FileException& e){
        std::cout << e.what();
    }
    
    
    try{
        readFile("config.txt");
    } catch (const FileNotFoundException& e){
        std::cerr >>"Error "<<e.what();
        return 1;
    }
    */
    
    
    
    
    //custom exceptions - exception class
    
    
    
    
    
    
    
    
    return EXIT_SUCCESS;
}


/*
#include <iostream>
using namespace std;

int main()
{
    try
    {
        try
        {
            throw 20;
        }
        catch (int n)
        {
            cout << "Inner Catch\n";
            throw;//re-throw again
        }
    }
    catch (int x)
    {
        cout << "Outer Catch\n";//here!
    }
    return 0;
}
*/
