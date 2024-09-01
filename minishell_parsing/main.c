
#include "minishell.h"

int main()
{
	static char buf[100]; // why this static
	
	while(getcmd(buf, sizeof(buf)) >= 0) // readline
	{ 
	    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
	    {
	      buf[strlen(buf)-1] = 0;
	      if(chdir(buf+3) < 0)
	        printf("cannot cd %s\n", buf+3);
	      continue;
	    }
	    if (fork1() == 0)
	      runcmd(parsecmd(buf));
	    wait(NULL);
    }
  exit(0);
}

// test it and fix it
// add herdocs to the logic
// integrated into our program (kt_minishell)
// make it work for builtins as well
// test it again