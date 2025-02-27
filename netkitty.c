#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 64
#define PORT "6942"
#define GETWHATINPUT what = getInput(ip, filename)

int getInput(char *ip, char *filename) {
  int what;

  do {
    printf("\n\n0) Quit\n1) Send Files\n2) Recieve Files\n3) Send Folders\n4) "
           "Recieve Folders\n\n>>");
    scanf("%d", &what);

    if (what < 0 || what > 4)
      printf("input error... try again\n\n");
  } while (what < 0 || what > 4);

  switch (what) {
  case 0:
    return 0;
  case 1:
  case 3:
    printf("insert destination ip >> ");
    scanf("%s", ip);
  case 4:
  case 2:
    printf("insert name of file or directory (with relative or absolute path, "
           "no / at the end) "
           ">> ");
    scanf("%s", filename);
    break;
  }

  return what;
}

int main() {
  int what;
  char ip[BUFFER] = {'\0'};
  char filename[BUFFER] = {'\0'};
  char helper[BUFFER] = {'\0'};
  char command[BUFFER * 4] = {'\0'};

  GETWHATINPUT;

  while (what != 0) {
    switch (what) {
    case 3:
      sprintf(helper, "%s%s", filename, "/");
      sprintf(filename, "%s%s", filename, ".zip");

      sprintf(command, "%s%s%s%s", "zip -r ", filename, " ", helper);
      system(command);
    case 1:
      sprintf(command, "%s%s%s%s%s%s", "nc -c ", ip, " ", PORT, " < ",
              filename);
      break;
    case 4:
      sprintf(helper, "%s", filename);
      sprintf(filename, "%s%s", filename, ".zip");
    case 2:
      sprintf(command, "%s%s%s%s", "nc -l -p ", PORT, " > ", filename);
      break;
    }

    system(command);
    if (what == 3) {
      sprintf(command, "%s%s", "rm ", filename);
      system(command);
    }
    if (what == 4) {
      sprintf(command, "%s%s", "unzip ", filename);
      system(command);

      sprintf(command, "%s%s", "rm ", filename);
      system(command);
    }

    GETWHATINPUT;
  }

  return 0;
}
