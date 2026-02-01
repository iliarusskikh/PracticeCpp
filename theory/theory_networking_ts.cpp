//netowring ts namespace
#include <iostream>
#include <net>

namespace std::net{
//core networking components
class io_context;
class socket;
class endpoint;

//IP address handling
class ip::address;

}

void connect_to_server(){
    //create IO context
    std::net::io_context io_context;
    
    //create resolver and socket
    std::net::ip::tcp::resolver resolver(io_context);
    std::net::ip::tcp::socket socket(io_context);
    
    //resolve hostname
    auto endpoints = resolver.resolve("example.com","http");
    
    //connect to server
    std::net::async_connect(socket, endpoints);
     
}


//asynchronour operations

//callback-based approach
socket.async_read_some(buffer,[](std::error_code ec, std::size_t length){
    if(!ec){
        //handle received data
        process_data(length);
        
        //continue reading
        start_read();
    }
});

//coroutine-based approach
awaitable<void> echo(tcp::socket socket){
    try{
        for(;;){
            //suspend until data is available
            std::size_t n = co_await socket.async_read_some(buffer,use_awaitable);
            co_await async_write(socket,buffer,use_awaitable);
        }
    }catch(...){
        //handle exceptions
    }
}


//basic TCP server example
//tcp::acceptor - listens for incoming connections
//async_accept - non-blocking accept operation
//recursive acecpt pattern for continous listening
//error handling for robust server operation

class Server{
public:
    Server(std::net::io_context& io_context, unsigned short port) : acceptor_(io_context,{std::net::op::tcp::v4(),port}){
        start_accept();
    }
private:
    void start_accept(){
        acceptor_.async_accept([this](std::error_code ec, std::net::i[::tcp::socket socket){
            if(!ec){
                handle_connection(std::move(socket));
            }
            start_accept();//accept next connection
        });
    }
    std::net::ip::tcp::acceptor acceptor_;
};



//time operations
//timer types
//steady_timer - monotonic clock that never jumpts
//system_timer - system clock that can be adjusted
//high_resolution_timer - highest precision available

//create a timer with the io_context
std::net::steady_timer timer(io_context);

//set timer to expire after 5 seconds
timer.expires_after(std::chrono::seconds(5));

//asynchronous wait
timer.async_wait([](std::error_code ec)){
    if(!ec){
        std::cout << "Timer expired"<<std::endl;
    }
}





int main() {
  

    
    
    return EXIT_SUCCESS;
}

