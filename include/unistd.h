#ifndef _UNISTD_H_
#define _UNISTD_H_

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int write(int __fd, void* __buf, int __size);
int read(int __fd, void* __buf, int __size);
int close(int __fd);

int fork();
int getpid();

int wait(int* __wstatus);
int waitpid(int __pid, int* __wstatus, int __options);

char* getcwd(char* __buf, int __size);
int chdir(char* __path);

int sleep(int __seconds);

#endif /* _UNISTD_H_ */