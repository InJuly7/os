#  进程API
**这个章节主要叙述进程相关的api,通过一些小的demo来辅助我们理解这些api**

## fork()
进程调用fork()系统调用,该进程会创建一个子进程,他们有不同的pid,而对于fork函数的返回值,
父进程返回子进程的pid,子进程返回0,这样就可以通过判断不同的返回值来让两个进程执行不同的代码段,
并且子进程不会从父进程的main()函数开始执行,而是从fork()系统调用返回的位置开始执行
父进程和子进程拥有各自的地址空间(物理内存,寄存器,程序计数器)

>GPT 对于父进程和子进程的虚拟内存和物理内存的解释:
在一般的情况下，父进程和子进程拥有相同的虚拟内存布局，但各自有独立的实际物理内存。这是通过使用进程的虚拟内存和操作系统的内存管理机制实现的。当一个新的子进程通过 fork 创建时，它会继承父进程的虚拟内存布局。这意味着，子进程在逻辑上会拥有与父进程相同的地址空间，包括代码段、数据段、堆、栈等。然而，虚拟内存中的内容是相互独立的。
关键的是，虽然两者共享相同的代码和数据（例如可执行程序的二进制代码），但它们在运行时的数据是相互独立的。例如，如果父进程在某个内存位置写入数据，这不会影响子进程在相同位置的数据，反之亦然。
需要注意的是，当父进程或子进程对其虚拟内存进行写操作时，操作系统会使用“写时复制”（Copy-on-Write）机制。这意味着在有写操作发生时，才会创建实际的物理内存拷贝，以确保各个进程的数据独立。
总之，虽然父进程和子进程在逻辑上共享相同的虚拟内存布局，但它们的实际物理内存是相互独立的，通过操作系统的内存管理机制保障了这种独立性。

## wait()

如果父进程调用了wait(NULL), 他会等待子进程运行结束,这会让我们显式的控制父进程和子进程的执行顺序,
因为他会延迟父进程执行,直到子进程执行结束

## exec()

exec() 该系统调用可以让子进程执行与父进程不同的程序,

调用execvp() 可以知道该文件有多少行,多少单词,多少字节
exec() 会从可执行程序中(当前进程)加载代码和静态数据,并用它覆写自己的代码段(以及静态数据),堆,栈,及其他内存空间也会被重新初始化
以前是和父进程相同的虚拟内存布局,子进程并没有创建新的进程,而是直接将当前运行的程序替换为不同的运行程序

执行完exec() 不会返回,后面的代码段不会执行

## 输出到屏幕的重定向
更改第一个可用的文件描述符指向的位置,
STDOUT_FILENO->Screen --->  STDOUT_FILENO->newfile.txt 
```
close(STDOUT_FILENO);
// 只写方式 文件不存在就创建文件 将文件截断为空文件(文件内容清空)  设置了文件所有者读写执行的权限
open("../newfile.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
```
先关闭标准输出文件描述符[1](屏幕),然后使用open打开一个文件 将其设置为新的标准输出,
由于open被调用时,会分配文件描述符,而关闭的文件描述符[1]会被重用,因此关闭标准输出后open将STDOUT_FILENO分配给新打开的文件




