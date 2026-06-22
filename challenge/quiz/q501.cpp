#include <array>
#include <iostream>

namespace GeneratedCode {
    namespace V1 {
        struct Order {
            int OrderId;
            std::array<char,8> Symbol;
        };
    }

    inline namespace V2 {
        struct Order {
            int OrderId;
            std::array<char,8> Symbol;
            int TraderId;
        };
    }
}

int main()
{
    //when schema updated, new updated namespace is featured whilst supporting V1, use inline, as it refers GeneratedCode to the most recent version
    GeneratedCode::Order order; //V2 is called
}
// Output: 8

