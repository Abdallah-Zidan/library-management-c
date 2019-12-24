#include <unistd.h>
#include <termios.h>
#include <ctype.h>

// colors codes
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KBRED  "\x1B[1;31m"
#define KGRN  "\x1B[32m"
#define KBGRN  "\x1B[1;32m"
#define KYEL  "\x1B[33m"
#define KBYEL  "\x1B[1;33m"
#define KBLU  "\x1B[34m"
#define KBBLU  "\x1B[1;34m"
#define KMAG  "\x1B[35m"
#define KBMAG  "\x1B[1;35m"
#define KCYN  "\x1B[36m"
#define KBCYN  "\x1B[1;36m"
#define KWHT  "\x1B[37m"

// convert a string to lower case
void tolowercase(char string[]){
    int i =0;
    while(string[i]){
        string[i] = tolower(string[i]);
        i++;
    }
}


//getch
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
   // printf("%c\n", buf); 
    return buf;
 }


 void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }


