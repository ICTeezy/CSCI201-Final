#include <iostream>
#include <string.h>
#include <errno.h>

#include "TCPSocket.hpp"

int main()
{
  TCPSocket listeningSocket = TCPSocket::Create();

  if (listeningSocket.bind(IPEndpoint("", 25567)) == -1)
  {
      std::cout << strerror(errno) << '\n';
  }
  else
  {
    std::cout << "Server bound on port 25567\n";
  }

  listeningSocket.listen();
  listeningSocket.setBlocking(false);

  while (true);
}