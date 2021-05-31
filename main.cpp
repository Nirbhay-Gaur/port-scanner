#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <iomanip>
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
static int stringToInt(const string& str) {
    stringstream sstream(str);
    int i;
    sstream >> i;
    return i;
}

// Generate a vector containing a range of values
template <typename T>
static vector<T> range(T min, T max) {
    if(min > max) 
        swap(min, max); 
    if(min == max)
        return vector<T> (1, min);
    vector<T> values;
    for(; min <= max; min++) {
        values.push_back(min);
    }
    return values;
}

// Parsing a list of ports containing numbers and ranges
static vector<int> parsePortsList(const string& list) {
    vector<int> ports;
    for(const string& token : split(list, ',')) {
        vector<string> strrange = split(token, '-');
        switch (strrange.size()) {
            case 0: 
                ports.push_back(stringToInt(token));   break;
            case 1: 
                ports.push_back(stringToInt(strrange[0]));   break;
            case 2: 
                    {
                        int min = stringToInt(strrange[0]),
                            max = stringToInt(strrange[1]);
                        for(int port : range(min, max))
                            ports.push_back(port);
                        break;
                    }
            default:
                break;
        }
    }
    return ports;
}

// Get maximum value in a vector
template <typename T>
static T maximum(const vector<T>& values) {
    T max = values[0];
    for(T value : values) {
        if(value > max) 
            max = value;
    }
    return max;
}

// Counts digits in a number
template <typename T>
static size_t digits(T value) {
    size_t count = (value < 0) ? 1 : 0;
    if(value == 0)
        return 0;
    while (value) {
        value /= 10;
        ++count;
    };
    return count;
}

int main(int argc, char* argv[]) {
   string address;
   string portList;
   vector<int> ports;
   bool openPort = false; 

   if(argc == 2 && !strcmp(argv[1], "-h")) {
        cerr << "Usage: " << argv[0] << " address port(s)\n"
                  << "Examples:\n"
                  << "\t" << argv[0] << " 192.0.43.10 80\n"
                  << "\t" << argv[0] << " example.com 80,443\n"
                  << "\t" << argv[0] << " 127.0.0.1 0-65535\n"
                  << "\t" << argv[0] << " localhost 0-21,80,8080"
                  << std::endl;
        exit(EXIT_SUCCESS);
   } else if (argc == 3) {
        address = argv[1];
        ports = parsePortsList(std::string(argv[2]));
    } else {
        std::string port_list;
        std::cout << "Address: " << std::flush;
        std::getline(std::cin, address);
        std::cout << "Port: " << std::flush;
        std::getline(std::cin, port_list);
        ports = parsePortsList(port_list);
    }

   cout << "Scanning for open ports..." << endl;
   size_t width = digits(maximum(ports));
   for(int port : ports) {
       if(isPortOpen(address, port)) {
            openPort = true; 
            cout << "Port " << setw(width) << port << " : OPEN\n"; 
       }
   }
   if(openPort == false) 
       cout << "No open port available\n";

    cout << flush;
    return 0;
}
