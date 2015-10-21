#include "snake.h"

int keyIsPressed()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
	 
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	
	ch = getchar();
	 
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	 
	if (ch != EOF) {
		ungetc(ch, stdin);
	    return 1;
	}
	 
	return 0;
}

int strtoint_n(char* str, int n)
{
    int sign = 1;
    int place = 1;
    int ret = 0;

    int i;
    for (i = n-1; i >= 0; i--, place *= 10) {
        int c = str[i];
        switch (c) {
            case '-':
                if (i == 0) sign = -1;
                else return -1;
                break;
            default:
                if (c >= '0' && c <= '9')   ret += (c - '0') * place;
                else return -1;
        }
    }

    return sign * ret;
}

int strtoint(char* str) 
{
    char* temp = str;
    int n = 0;
    while (*temp != '\0') {
        n++;
        temp++;
    }
    return strtoint_n(str, n);
}
