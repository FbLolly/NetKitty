#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 64
#define PORT "6942"
#define GETWHATINPUT what = getInput(ip, filename)

int getInput(char *ip, char *filename) {
  int what;

  do {
    printf("\n\n0) Quit\n1) Send Files\n2) Recieve Files\n\n>>");
    scanf("%d", &what);

    if (what < 0 || what > 2)
      printf("input error... try again\n\n");
  } while (what < 0 || what > 2);

  switch (what) {
  case 0:
    return 0;
  case 1:
    printf("insert destination ip >> ");
    scanf("%s", ip);
  case 2:
    printf("insert name of file (with relative or absolute path) >> ");
    scanf("%s", filename);
    break;
  }

  return what;
}

int main() {
  int what;
  char ip[BUFFER] = {'\0'};
  char filename[BUFFER] = {'\0'};
  char command[BUFFER * 4] = {'\0'};

  GETWHATINPUT;

  while (what != 0) {
    switch (what) {
    case 1:
      sprintf(command, "%s%s%s%s%s%s", "nc -c ", ip, " ", PORT, " < ",
              filename);
      break;
    case 2:
      sprintf(command, "%s%s%s%s", "nc -l -p ", PORT, " > ", filename);
      break;
    }

    system(command);

    GETWHATINPUT;
  }

  return 0;
}
