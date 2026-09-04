main函数

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "epoll_server.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "use: ./server [port] \n");
        return -1;
    }

    char *end = NULL;
    uint16_t port = strtol(argv[1], &end, 10);  // 将字符串端口号转换成2字节的数据
    if(*end){
        fprintf(stderr, "port error \n");
        return -1;
    }

    /* 创建tcp socket */
    int tcp_socket = initTcpServer(port);
    if(tcp_socket == -1){
        return -1;
    }

    /* 创建epoll */
    int epfd = epollCreate();
    if(epfd == -1){
        close(tcp_socket);
        return -1;
    }

    serverLoop(tcp_socket, epfd);

    close(tcp_socket);
    close(epfd);
    return 0;
}
```

服务器函数：主要用于集中监听所有socketfd

```c
#ifndef __EPOLL_SERVER_H__
#define __EPOLL_SERVER_H__

#include <stdint.h>

/* epoll服务端 */
int initTcpServer(uint16_t port);

int epollCreate();

void serverLoop(int tcp_socket, int epfd);

#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include "task.h"
#include "epoll_server.h"
#include "task_listen.h"


int initTcpServer(uint16_t port){
    /* 创建tcp的socket文件描述符 */
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket == -1){
        fprintf(stderr, "socket:%s\n", strerror(errno));
        return -1;
    }

    /* 处理2MSL问题, 端口复用 */
    int val = 1;
    int ret = setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if(ret == -1){
        fprintf(stderr, "socket:%s\n", strerror(errno));
        return -1;
    }
    
    /* 非阻塞 防止epoll边沿触发时，全部将连接取完后阻塞到listen处理函数中的accpct上，导致epoll_wait无法接收数据 */
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        DEBUG(RED, "[server.c] fcntl :%s\n", strerror(errno));
        return -1;
    }

    /* 将tcp的文件描述符与实际的IP端口进行绑定 */
    struct sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   // 设置成0.0.0.0

    ret = bind(tcp_socket, (const struct sockaddr *)&addr,  sizeof(addr));
    if(ret == -1){
        fprintf(stderr, "bind:%s\n", strerror(errno));
        close(tcp_socket);
        return -1;
    }

    /* 将当前的socket设置成监听状态 */
    ret = listen(tcp_socket, 5);      // 待连接的队列最大为5条
    if(ret == -1){
        fprintf(stderr, "listen:%s\n", strerror(errno));
        close(tcp_socket);
        return -1;
    }

    fprintf(stdout, "suecss\n");

    return tcp_socket;
}

int epollCreate(){
    /* epoll创建 */
    int epfd = epoll_create(1);
    if(epfd == -1){
        fprintf(stderr, "epoll_create:%s\n", strerror(errno));
        return -1;
    }

    return epfd;
}


void serverLoop(int tcp_socket, int epfd){
    /* 将监听socket上树 */
    int ret = listenTask(tcp_socket, epfd);
    if(ret == -1){
        return;
    }

    /* epoll_wait 等待事件触发 */
    struct epoll_event events[5];
    int num = 0;
    while (1) {
        memset(events, 0, sizeof(events));
        num = 0;
        num = epoll_wait(epfd, events, sizeof(events) / sizeof(events[0]), -1);
        if(num == -1){
            fprintf(stderr, "epoll_wait:%s\n", strerror(errno));
            return;
        }

        for(int i = 0; i < num; ++i){
            struct task_s *task = events[i].data.ptr;
            if(task){
                if(task->handler(task) == -1){
                    fprintf(stderr, "fd error:%d\n", task->fd);
                    continue;
                }
            }
        }
    }
}
```

任务体结构：模板类型，封装上树和下树的操作

```c
#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>

typedef int (*fun_t)(void *arg);

/* 任务结构体 */
struct task_s{
    int fd;				// 该任务操作的IO对象对应文件描述符
	int epollfd;		// 该任务最终靠epoll对象进行 ADD DEL
	uint8_t *data;		// 该任务维护的缓存区首地址
	int len;			// 该任务维护的缓存区的长度
	int pos;			// 该任务维护的缓存区的当前索引号
	fun_t handler;		// 该任务一旦触发，应该执行哪个函数 
};

int addTask(int fd, int epfd, struct task_s *task);
int delTask(int fd,int epfd);

#endif


#include <sys/epoll.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "task.h"

int addTask(int fd, int epfd, struct task_s *task){
    /* 将socket上树 */
    struct epoll_event event;
    event.events   = EPOLLIN;         // 读事件
    event.data.ptr = task;            // 对应的任务体
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    if(ret == -1){
        fprintf(stderr, "epoll_ctl:%s\n", strerror(errno));
        return -1;
    }

    return 0;
}

int delTask(int fd,int epfd){
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    if(ret == -1){
        fprintf(stderr, "epoll_ctl:%s\n", strerror(errno));
        return -1;
    }

    return 0;
}
```

事件对应的函数任务结构

监听任务

```c
#ifndef __TASK_LISTEN_H__
#define __TASK_LISTEN_H__

#include <stdint.h>

/* 监听socket任务 */
int listenTask(int tcp_socket, int epfd);

#endif

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "task.h"
#include "task_oddNumber.h"
#include "task_evenNumber.h"

int listenHandler(struct task_s *task){
    /* 监听socket */
    int new_sockfd = accept(task->fd, NULL, NULL);
    if(new_sockfd < 0){
        fprintf(stderr, "accept:%s\n", strerror(errno));
        // delTask(task->fd, task->epollfd);
        // free(task);
        return -1;
    }

    /* 将新的socket上树 */
    /* epoll优势 1 + x + y 能处理三类事件（监听、奇数、偶数） */
    if(new_sockfd % 2){
        int ret = oddNumberTask(new_sockfd, task->epollfd);
        if(ret == -1){
            close(new_sockfd);
            return -1;
        }
    }else{
        int ret = evenNumberTask(new_sockfd, task->epollfd);
        if(ret == -1){
            close(new_sockfd);
            return -1;
        }
    }
    fprintf(stdout, "new socketc\n");

    return 0;
}

int listenTask(int tcp_socket, int epfd){
    struct task_s *task = malloc(sizeof(struct task_s));
    if(!task) { return -1; }
    memset(task, 0, sizeof(struct task_s));
    task->fd      = tcp_socket;
    task->epollfd = epfd;
    task->handler = (fun_t)listenHandler;

    int ret = addTask(tcp_socket, epfd, task);
    if(ret == -1){
        return -1;
    }
    return 0;
}
```

奇数任务

```c
#ifndef __TASK_ODD_NUMBER_H__
#define __TASK_ODD_NUMBER_H__

#include <stdint.h>

/* 奇数任务 */
int oddNumberTask(int tcp_socket, int epfd);

#endif

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "task.h"

int oddNumberHandler(struct task_s *task){
    /* 奇数socket */
    /* 接收数据 */
    char buf[1024] = {0};
    ssize_t r_len = recv(task->fd, buf, sizeof(buf) - 1, 0);
    if(r_len < 0){
        fprintf(stderr, "recv:%s\n", strerror(errno));
        delTask(task->fd, task->epollfd);
        free(task);
        return -1;
    }else if(r_len == 0){
        delTask(task->fd, task->epollfd);
        free(task);
        return 0;
    }else{
        buf[r_len] = 0;
        fprintf(stdout, "recv:%s\n", buf);
        buf[0] = 'A';
		send(task->fd, buf, r_len, 0);
    }

    return 0;
}

int oddNumberTask(int socket, int epfd){
    struct task_s *task = malloc(sizeof(struct task_s));
    if(!task) { return -1; }
    memset(task, 0, sizeof(struct task_s));
    task->fd      = socket;
    task->epollfd = epfd;
    task->handler = (fun_t)oddNumberHandler;

    int ret = addTask(socket, epfd, task);
    if(ret == -1){
        return -1;
    }
    return 0;
}
```

偶数任务

```c
#ifndef __TASK_EVEN_NUMBER_H__
#define __TASK_EVEN_NUMBER_H__

#include <stdint.h>

/* 偶数任务 */
int evenNumberTask(int socket, int epfd);
#endif

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "task.h"

int evenNumberHandler(struct task_s *task){
    /* 偶数socket */
    /* 接收数据 */
    char buf[1024] = {0};
    ssize_t r_len = recv(task->fd, buf, sizeof(buf) - 1, 0);
    if(r_len < 0){
        fprintf(stderr, "recv:%s\n", strerror(errno));
        delTask(task->fd, task->epollfd);
        free(task);
        return -1;
    }else if(r_len == 0){
        delTask(task->fd, task->epollfd);
        free(task);
        return 0;
    }else {
        buf[r_len] = 0;
        fprintf(stdout, "**recv**:%s\n", buf);
        buf[0] = 'A';
		send(task->fd, buf, r_len, 0);
    }

    return 0;
}

int evenNumberTask(int socket, int epfd){
    struct task_s *task = malloc(sizeof(struct task_s));
    if(!task) { return -1; }
    memset(task, 0, sizeof(struct task_s));
    task->fd      = socket;
    task->epollfd = epfd;
    task->handler = (fun_t)evenNumberHandler;

    int ret = addTask(socket, epfd, task);
    if(ret == -1){
        return -1;
    }
    return 0;
}
```

Makefile

```makefile
CC = gcc
CFLAGS = -Wall -g -pthread
TARGET_SERVER = server

OBJS_COMMON = main.o epoll_server.o task_evenNumber.o task_listen.o task_oddNumber.o task.o

all: $(TARGET_SERVER)

$(TARGET_SERVER): $(OBJS_COMMON)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET_SERVER) 

.PHONY: all clean
```



epoll相关的封装库：`libevent`
