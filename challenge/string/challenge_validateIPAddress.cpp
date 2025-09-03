//Program to validate an IP address

//IPv4 Addresses Validation
//IPv4 addresses use dot-decimal notation, consisting of four numbers (0-255) separated by dots, e.g., 172.16.254.1.

//[Naive Approach] Using the Inbulit Library Methods - O(n) Time and O(n) Space
/*#include <bits/stdc++.h>
using namespace std;

int isValid(string &s){

    int n = s.size();

    if (n < 7)
        return false;
        
    // Using string stream to separate all the string from '.' and push back into vector like for ex -
    vector<string> v;
    stringstream ss(s);
    while (ss.good()){
        string substr;
        getline(ss, substr, '.');
        v.push_back(substr);
    }

    if (v.size() != 4)
        return false;
        
    // Iterating over the generated vector of strings
    for (int i = 0; i < v.size(); i++){
        
        string temp = v[i];

        if (temp.size() > 1){
            if (temp[0] == '0')
                return false;
        }

        for (int j = 0; j < temp.size(); j++){
            if (isalpha(temp[j]))
                return false;
        }
        
        // And lastly we are checking if the
        // number is greater than 255 or not
        if (stoi(temp) > 255)
            return false;
    }
    return true;
}

int main(){
    string s = "128.0.0.1";
    isValid(s) ? cout << "true" : cout << "false";
    return 0;
}
*/


//[Expected Approach] Using Traversal over the IP String - O(n) Time and O(1) Space
#include <bits/stdc++.h>
using namespace std;

bool valid_part(string &s){
    int n = s.length();

    // Length must be between 1 and 3
    if (n == 0 || n > 3)
        return false;

    // Check if all characters are digits
    for (char c : s)
    {
        if (c < '0' || c > '9')
            return false;
    }

    // Prevent numbers like "00", "01"
    if (s[0] == '0' && n > 1)
        return false;

    // Convert to integer manually
    int num = 0;
    for (char c : s)
    {
        num = num * 10 + (c - '0');
    }

    return num >= 0 && num <= 255;
}

// Function to check if a given
// string is a valid IPv4 address
bool isValid( string &ip){

    istringstream ss(ip);
    string part;
    int segmentCount = 0;
    while (getline(ss, part, '.'))
    {
        if (!valid_part(part))
            return false;
        segmentCount++;
    }

    return segmentCount == 4;
}

int main()
{
    string s = "128.0.0.1";

    cout << (isValid(s) ? "true" : "false");

    return 0;
}


/*#include <bits/stdc++.h>
 using namespace std;

 bool isValidSegment(string &s){
     int n = s.length();

     // Length must be between 1 and 4
     if (n == 0 || n > 4)
         return false;

     // Check if all characters are
     // valid hexadecimal digits
     for (char c : s){
         if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
             return false;
     }

     return true;
 }

 bool isValid( string &ip){
     int colonCount = 0;
     int len = ip.length();

     // Count the number of colons
     for (char c : ip){
         if (c == ':')
             colonCount++;
     }

     // An IPv6 address must
     // have exactly 7 colons
     if (colonCount != 7)
         return false;

     // Split manually by ':'
     string segment;
     int segmentCount = 0;

     for (int i = 0; i < len; i++){
         if (ip[i] == ':'){
             if (!isValidSegment(segment))
                 return false;
             segment.clear();
             segmentCount++;
         }
         else{
             segment += ip[i];
         }
     }

     if (!isValidSegment(segment))
         return false;

     return segmentCount == 7;
 }

 int main(){
     string s = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";

     cout << (isValid(s) ? "true" : "false");

     return 0;
 }*/
