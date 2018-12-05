#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd;char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl (STDIN_FILENO, F_SETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, F_SETFL, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if(c != EOF)
	{
		ungetc (c, stdin);
		result = getchar();
	}
	return result;
}
char moveplayer()
{
	char player = 1;
	char key;
	int x = 0, y = 0;
	while(1)
	{
		key = key_pressed();
		switch(key)
		{
			case 'A':
				y-=1;
				break;
			case 'B':
				y+=1;
				break;
			case 'C':
				x+=1;
				break;
			case 'D':
				x-=1;
				break;
		}
		printf("\033[%d;%dH%c", y,x,player);
	}
}
int main()
{
	moveplayer();
	return(0);
}






