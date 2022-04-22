#ifndef _UNISTD_H_
#define _UNISTD_H_

int write(int _fd, void* buf, int size);

int fork();
int getpid();

char* getcwd(char* __buf, int __size);
int chdir(char* __path);

#endif /* _UNISTD_H_ */