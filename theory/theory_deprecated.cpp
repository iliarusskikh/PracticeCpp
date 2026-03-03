#include <iostream>

[[deprecated]] void do_work(int) = delete; //instead of just removing, to prevent from smb to call this func with int and cause implicit conversion
void do_work(double);

//or
[[deprecated]] void use_string(const char *) = delete;
//{
//    use_string(std::string_view{ptr});
//};
void use_string(std::string_view);


int main(){
    do_work(43.0);
    do_work(43); //no cause error since call to a function that was deleted!
    
    std::string data;
    use_string(data);
}
