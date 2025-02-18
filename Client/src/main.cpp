#include <iostream>

#include "TCPSocket.hpp"

int main()
{
   TCPSocket clientSocket = TCPSocket::Create(); 
   if (clientSocket.connect(IPEndpoint("", 25567)) == -1)
   {
      std::cout << "Unable to connect.\n";
   }
   else
   {
      std::cout << "Connected!\n";
   }

   char message[] = "Hey!\n";
   clientSocket.send(message, sizeof(message));
}