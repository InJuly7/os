#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
    // 只写方式 文件不存在就创建文件 将文件截断为空文件(文件内容清空)  设置了文件所有者读写执行的权限
    int fd = open("/home/tingshuo/os/2.4-io.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd > -1);
    int rc = write(fd, "hello world \n", 13);
    assert(rc == 13);
    close(fd);
    return 0;
}