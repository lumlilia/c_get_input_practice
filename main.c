#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WIN_FLAG (defined(_WIN32) || defined(_WIN64))

#if WIN_FLAG
  #include <conio.h>
  const char CLEAR[] = "cls";

#else
  #include <termios.h>
  const char CLEAR[] = "clear";

#endif


int main(void){
  system(CLEAR);

  #if !WIN_FLAG
    struct termios term0, term1;

    tcgetattr(0, &term1);
    term0 = term1;
    term1.c_lflag &= ~(ICANON | ECHO);
    term1.c_cc[VMIN] = 1;
    term1.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term1);

  #endif

  char ch;
  char pigi[10] = "pigimongo";
  char i_log[10];
  memset(&i_log[0], 0, 10);

  while(1){
    #if WIN_FLAG
      if(_kbhit()){
        ch = _getch();
      }

      else{
        continue;
      }

    #else
      ch = getchar();

    #endif

    memcpy(&i_log[0], &i_log[1], 8);
    i_log[8] = ((ch > 64 && ch < 91) ? ch + 32 : ch);

    printf("%s key\n", &ch);

    if(memcmp(&pigi[0], &i_log[0], 9) == 0){
      break;
    }
  }

  #if WIN_FLAG
    puts("\nPIGIMONGO!!!!");

  #else
    puts("\n\x1b[1mPIGIMONGO!!!!\x1b[0m");
    tcsetattr(0, TCSANOW, &term0);

  #endif

  return 0;
}
