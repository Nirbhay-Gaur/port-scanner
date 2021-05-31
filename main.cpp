#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

// Check if port is open or close
static bool isPortOpen(const string& addr, int port) {
    return (TcpSocket().connect(addr, port) == Socket::Done);
}

// Splits a string into tokens around a delimiter (default: " "), optionally allowing empty tokens
static vector<string> split(const string& str, char del, bool allow_empty = false) {
    vector<string> tokens;
    stringstream sstream(str);
    string token;
    while (getline(sstream, token, del)) {
        if(allow_empty || token.size() > 0) 
            tokens.push_back(token);
    }
    return tokens;
}

// Convert string to int
static int stoi(const string& str) {
    stringstream sstream(str);
    int i;
    sstream >> i;
    return i;
}

int main() {
   string address;
   int port;
   
   // Get Address
   cout << "Address: ";
   getline(cin, address);

   // Get Port
   cout << "Port: ";
   cin >> port;
   cout << "Scanning " << address << endl;
   //for(int i = 40; i <= 100; i++) {
     //  port = i;
   

   // Scan
   cout << "Port " << port << " : ";
   if(isPortOpen(address, port))
        cout << "OPEN" << endl;
   else 
       cout << "CLOSED" << endl;
   //}
   return -2;
}
