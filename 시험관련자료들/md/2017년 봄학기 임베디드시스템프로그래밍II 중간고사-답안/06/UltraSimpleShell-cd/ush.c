
#include "ush.h"
#include "makeargv.h"
#define MAX_BUFFER 256


int main (int argc, char *argv[])
{
    char inbuf[MAX_BUFFER];
    char **chargv;
    int i;

    for(;;) {
	gets(inbuf);
	if (strcmp(inbuf, QUIT_STRING) == 0)
          break;
	if (strncmp(inbuf, CD_STRING BLANK_STRING, 3) == 0)
        {
          if (makeargv(inbuf, BLANK_STRING, &chargv) > 1)
          {
             if(chdir(chargv[1]) != 0)
                printf("%s: no such file or directory: %s\n", chargv[0], chargv[1]);
          }
        }
	else {
          if (fork() == 0) {
             if (makeargv(inbuf, BLANK_STRING, &chargv) > 0)
	     { 
                execvp(chargv[0], chargv);
	     }
          }
          wait(NULL);
       } 
    }   
    return 0;
}
