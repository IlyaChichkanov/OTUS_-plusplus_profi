#include <iostream>

#include "bulk.hpp"

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    std::cout << "require block size as argument\n";
    return 1;
  }

  int n = 0;
  if(!sscanf(argv[1], "%d", &n))
  {
    std::cout << "argument should be int\n";
    return 1;
  }
  
  std::string cmd;
  Bulk Bulk(n);

  while(std::cin >> cmd)
    Bulk.push(cmd);

  Bulk.display();

  return 0;
}
