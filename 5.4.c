# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<fcntl.h>
# include<sys/wait.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO);
        // 只写方式 文件不存在就创建文件 将文件截断为空文件(文件内容清空)  设置了文件所有者读写执行的权限
        int fd = open("../newfile.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        // fflush(stdout);
        // printf("fd = %d\n",fd);
        dprintf(fd, "fd = %d\n",fd);
        dprintf(fd, "Some additional information ...\n");
        // running "wc"
        char *myargv[3];
        // program name wc (word count)
        myargv[0] = strdup("wc");
        myargv[1] = strdup("../5.4.c");
        myargv[2] = NULL;
        execvp(myargv[0],myargv);
    }
    else
    {
        int wc = wait(NULL);
    }
    return 0;
}