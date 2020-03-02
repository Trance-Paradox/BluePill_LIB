#ifndef printMsg_h_
#define printMsg_h_
 
extern int len;
extern char buff[];
 
void usart_1_enable(void);
void printMsg(char *msg, ...);
int readMsg(void);
 
#endif