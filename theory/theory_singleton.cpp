#include <iostream>
#include <mutex>           // only needed if you need thread-safe lazy init before C++11 guaranteed
#include <string>

// ────────────────────────────────────────────────
// Thread-safe Singleton (since C++11)
// Most recommended / cleanest version
// ────────────────────────────────────────────────
class Singleton
{
public:
    static Singleton& Get(){ //static ensures only one instance
        return s_Instance;
    }
    
    void Function(){}
    
private:
    Singleton() {}
    
    static Singleton s_Instance;
};

Singleton Singleton::s_Instance;





class Logger {
private:
    // Private constructor → prevents direct instantiation
    Logger() {
        std::cout << "Logger created!\n";
    }

    // Delete copy and move operations
    Logger(const Logger&) = delete;//deleting copy construcor
    Logger& operator=(const Logger&) = delete;//copy
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;//move
    
    /*void operator=(Logger&&){
        throw std::logic_error("Can not move Singleton")
     }

     */

public:
    // The only way to get the instance
    static Logger& getInstance() {
        // Static local variable → initialized exactly once, thread-safe since C++11
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << "\n";
    }

    ~Logger() {
        std::cout << "Logger destroyed!\n";
    }
};
 
// ────────────────────────────────────────────────
// Usage example
// ────────────────────────────────────────────────
int main() {
    // Get the singleton instance (creates it on first call)
    Logger& logger1 = Logger::getInstance();
    logger1.log("Application started");

    // Same instance everywhere
    Logger& logger2 = Logger::getInstance();
    logger2.log("Processing data...");

    // You can even do this – still the same object
    Logger::getInstance().log("Finished!");

    std::cout << "logger1 address: " << &logger1 << "\n";
    std::cout << "logger2 address: " << &logger2 << "\n";
    
    
    
    Singleton::Get().Function();

    return EXIT_SUCCESS;
}
