#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_USE_CERTS_FROM_MACOSX_KEYCHAIN  // Optional for macOS
#include "http_lib.h"  // Your renamed httplib.h
#include <iostream>
//#include <nlohmann/json.hpp>  // For JSON parsing; include via header or submodule
//brew install openssl@3 -> need to fix error with openssl.


int main() {
    httplib::Client cli("https://api.open-meteo.com");
    cli.set_connection_timeout(5, 0);  // 5 seconds timeout
    cli.set_read_timeout(5, 0);
      
    auto res = cli.Get("/v1/forecast?latitude=37.8136&longitude=144.9631&current=temperature_2m");
      
    if (res) {
        std::cout << "Status: " << res->status << std::endl;
        std::cout << "Body: " << res->body << std::endl;
          
        // Parse JSON (example)
//        try {
//            auto json = nlohmann::json::parse(res->body);
//            double temperature = json["current"]["temperature_2m"].get<double>();
//            std::cout << "Current Temperature: " << temperature << "°C" << std::endl;
//        } catch (const std::exception& e) {
//            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
//        }
    } else {
        std::cerr << "Request Failed: " << httplib::to_string(res.error()) << std::endl;
        // Handle specific errors, e.g., if (res.error() == httplib::Error::SSLConnection) { ... }
    }
      
    return 0;
}
