#include <iostream>
#include "configCollector.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorrect command line argument" << '\n';
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  try
  {
    data::configCollector data(file);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }
}
