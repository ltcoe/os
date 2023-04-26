
#include <stdio.h>
// #include <stdlib.h>
int fork();
int getpid();
int getppid();
int main()
{
int pid=fork();
if (pid==0)
{
printf("this is child process. my pid is %d and my parent's id is %d \n",getpid(),getppid());
}
else
{
printf("this is parent process. my pid is %d and my id is %d. \n",getpid(),pid);
}
return 0;
}