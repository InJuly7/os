# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<sys/wait.h>

int main(int argc,char *argv[])
{
    for(int i = 0; argv[i]!= NULL;i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("child process pid:%d\n",(int)getpid());
        char *myargv[3];
        myargv[0] = strdup("wc");
        myargv[1] = strdup("../5.3-exec.c");
        myargv[2] = NULL;
        execvp(myargv[0],myargv);
        // 执行完execvp 不会返回 后面的代码段不会执行
        printf("this should not print out\n");
        
    }
    else
    {
        int wc = wait(NULL);
        printf("Parent of %d process wc:%d pid:%d\n",rc,wc,(int)getpid());
    }
    return 0;    
}