#include <iostream>
#include <string>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

static bool isPortOpen(const string& addr, int port) {
    return (TcpSocket().connect(addr, port) == Socket::Done);
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

   // Scan
   cout << "Scanning " << address << endl << "Port " << port << " : ";
   if(isPortOpen(address, port))
        cout << "OPEN" << endl;
   else 
       cout << "CLOSE" << endl;

   return 0;
}
