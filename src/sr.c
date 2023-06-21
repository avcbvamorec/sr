#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *line = NULL;
  size_t len = 0;
  ssize_t lineSize = 0;
  size_t sleepTime = 500;

  int option;
  while((option = getopt(argc, argv, ":hd:")) != -1)
  {
    switch(option)
    {
      case '?':
        printf("Unknown option: %c", optopt);
        exit(1);
        break;
      case ':':
        printf("Argument missing\n");
        exit(1);
        break;
      case 'h':
        printf("Usage:\n");
        printf("    %s -h : prints this message.\n",argv[0]);
        printf("    %s [-d <delay in µs>] : outputs stdin line by line with a delay between each line (500µs if not specified).\n",argv[0]);
        exit(0);
        break;
      case 'd':
        sleepTime = atoi(optarg);
        break;
    }
  }

  lineSize = getline(&line, &len, stdin);
  while (lineSize >= 0)
  {
    write(STDOUT_FILENO, line, lineSize);
    usleep(sleepTime);
    lineSize = getline(&line, &len, stdin);
  }

  free(line);
  return EXIT_SUCCESS;
}
