#include<iostream>
#include <ctime>

int main(){
    time_t now = time(nullptr);//get current time
    
    std::cout << "Seconds since epoch: "<<now <<std::endl;
    std::cout << "Seconds since epoch: "<<ctime(&now) <<std::endl;

    struct tm *local_time = localtime(&now);//convert to local time struct
    //access struct members
    int year = local_time->tm_year + 1990;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;//hour min sec wday
    
    char buffer[80];
    
    //format :: yyyy mm dd hh mm ss
    strftime(buffer, 80,"%Y-%m-%d %H:%M:%S", local_time);
    std::cout <<"Formated time: "<< buffer<<std::endl;

    
    time_t start = time(nullptr);
    time_t end = time(nullptr);
    
    double diff  = difftime(end,start);//in seconds
    std::cout <<"Difference: "<< diff<<std::endl;

    return EXIT_SUCCESS;
}
