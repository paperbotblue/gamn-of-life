#include <stdio.h>
#include "./Main.hpp"

void exitcode(int return_code);

int main()
{
  Main main;
  exitcode(main.run());
  return 0;
}

void exitcode(int return_code)
{

  switch(return_code)
  {
    case 0:
      printf("Exited successfully\n");
      break;
    default:
      break;
  }

}

