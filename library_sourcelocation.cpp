//releases unused memory, useful after elements release
#include <iostream>
#include <source_location>
//allows getting info about call function, including line of the code, etc

void logMessage(const std::string& message, std::source_location loc = std::source_location::current())
{
    std::cout <<"File " <<loc.file_name() << loc.line() << loc.function_name() << message;
    
}

int main()
{
    logMessage("Error in the code");
    return 0;
}
