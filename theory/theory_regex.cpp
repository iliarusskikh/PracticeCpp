#include <iostream>
#include <regex>
#include <string>
#include <vector>

bool validatePassword(const std::string& password)
{
    // At least 8 characters, at least 1 lowercase, 1 uppercase, 1 digit
    // Only allows letters, digits and some common special characters
    const std::regex pattern(
        R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d!@#$%^&*()_+\-=\[\]{};':",.<>?/]{8,})"
    );

    return std::regex_match(password, pattern);
}

int main()
{
    // ────────────────────────────────────────────────
    // 1. Password validation examples
    // ────────────────────────────────────────────────
    std::vector<std::string> passwords = {
        "abc123",           // too weak
        "Abcdef12",         // good
        "ABCDEFGH1",        // no lowercase
        "P@ssw0rd2025!",    // good
        "short1A"           // too short
    };

    std::cout << "Password validation:\n";
    for (const auto& pw : passwords) {
        std::cout << "  \"" << pw << "\"  →  "
                  << (validatePassword(pw) ? "VALID" : "INVALID")
                  << "\n";
    }
    std::cout << "\n";

    // ────────────────────────────────────────────────
    // 2. Simple email search
    // ────────────────────────────────────────────────
    std::string text = "Email: john.doe123@example.com";
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");//last one - two or more letters

    std::smatch matches;
    if (std::regex_search(text, matches, email_pattern)) {
        std::cout << "Found email: " << matches[0] << "\n\n";
    }

    // ────────────────────────────────────────────────
    // 3. Date with capturing groups
    // ────────────────────────────────────────────────
    std::string text2 = "Date: 2024-11-23";
    std::regex date_pattern(R"(Date: (\d{4})-(\d{2})-(\d{2}))");

    std::smatch matches2;
    if (std::regex_search(text2, matches2, date_pattern)) {
        std::cout << "Year:  " << matches2[1] << "\n";
        std::cout << "Month: " << matches2[2] << "\n";
        std::cout << "Day:   " << matches2[3] << "\n\n";
    }

    // ────────────────────────────────────────────────
    // 4. Name swap using backreferences
    // ────────────────────────────────────────────────
    std::string text3 = "John Doe";
    std::regex name_pattern(R"((\w+)\s+(\w+))");//two groups created
    std::string result = std::regex_replace(text3, name_pattern, "$2, $1");

    std::cout << "Name swap: " << text3 << " → " << result << "\n\n";

    // ────────────────────────────────────────────────
    // 5. Find multiple IP addresses (with iterator loop)
    // ────────────────────────────────────────────────
    std::string text4 = "IP addresses: 192.168.1.1 and 10.0.0.1 and 256.1.2.3 (invalid)";
    std::regex ip_pattern(R"(\b(?:\d{1,3}\.){3}\d{1,3}\b)");

    std::cout << "Found IP addresses:\n";

    auto begin = text4.cbegin();
    auto end   = text4.cend();

    std::smatch ip_matches;
    while (std::regex_search(begin, end, ip_matches, ip_pattern)) {
        std::cout << "  " << ip_matches[0] << "\n";
        begin = ip_matches.suffix().first;
    }

    std::cout << "\n";

    return 0;
}



/*
 Password validation:
   "abc123"  →  INVALID
   "Abcdef12"  →  VALID
   "ABCDEFGH1"  →  INVALID
   "P@ssw0rd2025!"  →  VALID
   "short1A"  →  INVALID

 Found email: john.doe123@example.com

 Year:  2024
 Month: 11
 Day:   23

 Name swap: John Doe → Doe, John

 Found IP addresses:
   192.168.1.1
   10.0.0.1
 */



/*
 \d digit(0–9)
 {n,m} previous item repeated n to m times
 {n} exactly n times
 (?: … )group – do not capture
 \b word boundary
 . literal dot (in raw string)
 
 
 (\w+) letters, digits, underscore (1+)
 \s+ whitespace (1+)
 
 
 matches[0] whole matchDate: 2025-02-07
 matches[1] group 1 – year 2025
 
 
 */
