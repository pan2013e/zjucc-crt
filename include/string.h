#ifndef _STRING_H_
#define _STRING_H_

void* memset(void* __dst, int __c, long __size);
void memcpy(void* __dst, void* __src, long __size);

int strlen(char* __s);
char* strchr(char* __s, int c);
int strcmp(char* __s1, char* __s2);

char* strerror(int errnum);

#endif /* _STRING_H_ */