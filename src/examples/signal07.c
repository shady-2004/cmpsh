#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

void handler(int signum);

int main()
{
  int n;
  char line[100] = "\nDEFAULT\n";
  /*
   * Set the signal handler for Alarm signal
   */

  signal(SIGALRM, handler);

  printf("\nEnter a text (timeout after 10 secs):");

  alarm(10); /* enable alarm */

  scanf("%s", line);

  alarm(0); /* disable alarm */

  printf("%s\n", line);

  exit(0);
}
/*
 * This the the signal handler for SIGALRM signal
 */

void handler(int signum)
{

  printf("\n\n TimeOut......\n");
  exit(-1);
}
