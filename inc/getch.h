#ifndef UtilsH
#define UtilsH

void initTermios(int echo);

void resetTermios(void);
char getch_(int echo);

char getch(void);
char getche(void);

#endif
