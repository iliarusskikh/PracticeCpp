#include <iostream>
#include <ctime>

int main()
{
    std::cout <<"Time operations" <<"\n";
    
    time_t now = time(nullptr);//get current time
    
    std::cout <<"Seconds since epoch" <<now<<"\n";
    std::cout <<"Current time" <<ctime(&now)<<"\n";//more friendly

    struct tm *local_time = local_time(&now);
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;//hour, min, sec, wday
    
    char buffer[50];
    strftime(buffer,80,"%Y-%m-%d %H:%M:%S", local_time);
    std::cout <<"Formatted time" <<buffer<<"\n";

    
    
    //time calculations, in seconds
    time_t start = time(nullptr);
    //do work here...
    
    time_t end = time(nullptr);
    double diff = difftime(end,start);
    
    
    
    return EXIT_SUCCESS;
    
}


