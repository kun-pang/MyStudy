## 客户端 ——https协议（使用openssl）/http协议

```c
#include <asm-generic/socket.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "openssl/crypto.h"
#include "openssl/ssl.h"    // openssl第三方库
#include "openssl/err.h"

/* http/https的客户端 */
/* 编译：gcc -I/home/siguyuan/lib/openssl/include -L/home/siguyuan/lib/openssl/lib64 -o build  https_cliect.c -lcrypto -lssl  */
/* 网站测试: http://download.visualstudio.microsoft.com/download/pr/7afca223-55d2-470a-8edc-6a1739ae3252/abd170b4b0ec15ad0222a809b761a036/ndp48-x86-x64-allos-enu.exe
 */
/* https://www.oracle.com/mysql/technologies/mysql-enterprise-edition-downloads.html#license-lightbox */

/* 请求信息结构 */
typedef struct task_s{
    int      protocol;      // 协议 80为http协议,433为https协议 
    uint16_t port;          // 端口
    char     hostname[64];  // 域名
	char     res_path[256]; // 资源路径
	char     filename[64];  // 资源文件
} Task_t;

static Task_t *createTask(){
    /* 在内存申请请求信息的结构大小 */
    Task_t *task = malloc(sizeof(Task_t));
    if(!task) { return NULL; }
    memset(task, 0, sizeof(Task_t));
    return task;
}

static void freeTask(Task_t *task){
    if(task){ free(task); }
}

static long strtoLong(const char *portstr){
    errno = 0;
    char *end;
    long port = strtol(portstr, &end, 10);
    if ((port == LONG_MAX || port == LONG_MIN) && errno == ERANGE) {    // 转换溢出
        fprintf(stderr, "Error: Numeric overflow/underflow (out of long range)\n");
        return -1;
    }
    if (errno != 0 && port == 0) {                                      // 其他错误
        fprintf(stderr, "Error: Unknown conversion error occurred\n");
        return -1;
    }
    if (end == portstr) {                                               // 无效的端口字符串 (完全没有数字)
        fprintf(stderr, "Error: No valid digits found for conversion\n");
        return -1;
    }
    if (*end != '\0') {                                                 // 端口包含非法字符 (例如 '8080ab')
        fprintf(stderr, "Error: Trailing invalid characters found after number: '%s'\n", end);
        return -1;
    }
    return port;
}

static int analysisUrl2Task(const char *url, Task_t *task){
    /* 使用4个指针来解析域名 */
    char *protocol = NULL;  // 协议
    char *domain   = NULL;  // 域名
    char *port     = NULL;  // 端口
    char *path     = NULL;  // 路径

    /* 解析协议 */
    protocol = strstr(url, "http://");
    if(!protocol){      // 没有找到
        protocol = strstr(url, "https://");
        if(!protocol){
            fprintf(stderr, "analysisUrl2Task - strstr: No http or https protocol header!\n");
            return -1;
        }

        /* 设置端口 */
        task->protocol = 443;
        task->port     = 443;                      // 先暂时使用默认端口号
        protocol      += strlen("https://");    // 移动指针
    }else{
        task->protocol = 80;
        task->port     = 80;
        protocol      += strlen("http://");    
    }

    /* 解析域名和端口 */
    domain = strstr(protocol, "/");        // 匹配第一个/前面的字符
    if (!domain) {
        fprintf(stderr, "analysisUrl2Task - strstr: URL format invalid!\n");
        return -1;
    }else{
        /* 区分域名和端口 */
        *domain = 0;        // 形成字符串，与后面的路径进行隔断
        port = strstr(protocol, ":");
        if(port){
            /* 存在端口，更新端口 */
            int ret = strtoLong(port + 1);
            if(ret == -1){
                return -1;
            }
            task->port = ret;
        }
        snprintf(task->hostname, sizeof(task->hostname), "%s", protocol);   // 将域名存储起来
        *domain = '/';      // 恢复
    }

    /* 解析路径和文件名 */
    snprintf(task->res_path, sizeof(task->res_path), "%s", domain);

    // 过滤掉 URL 中的 # 锚点（防止其被发送到服务器）
    char *fragment = strchr(task->res_path, '#');
    if (fragment) {
        *fragment = '\0'; // 强行截断，去除 #license-lightbox
    }

    path = strrchr(domain, '/');;    // 找到后面路径中最后一个'/'
    if(*(path + 1) == '\0'){
        /* 以/结尾 */
		snprintf(task->filename, sizeof(task->filename), "index.html"); // 使用默认文件
    }else{
        char * temp = strstr(path + 1, "?");
        if(!temp){      // 不存在 ?
            snprintf(task->filename, sizeof(task->filename), "%s", path + 1);
        }else{
            *temp = '\0';
            snprintf(task->filename, sizeof(task->filename), "%s", path + 1);
            *temp = '?';
        }
    }
    return 0;
} 

static void show(Task_t *task){
    fprintf(stdout, "%d\n",task->protocol);
    fprintf(stdout, "%d\n",task->port);
    fprintf(stdout, "%s\n",task->hostname);
    fprintf(stdout, "%s\n",task->res_path);
    fprintf(stdout, "%s\n",task->filename);
}

int initTcpCliect(Task_t *task, SSL **ssl){
    int tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_fd == -1){
        fprintf(stderr, "initTcpCliect - socket: %s", strerror(errno));
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    struct hostent *h = gethostbyname(task->hostname);
    if(!h){
        fprintf(stderr, "get host name %d: %s\n", h_errno, hstrerror(h_errno));
        close(tcp_fd);
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(task->port);
    addr.sin_addr   =  *(struct in_addr *)h->h_addr;
    socklen_t len = sizeof(addr);
    int ret = connect(tcp_fd, (const struct sockaddr *)&addr, len);
    if(ret == -1){
        fprintf(stderr, "initTcpCliect - connect: %s", strerror(errno));
        close(tcp_fd);
        return -1;
    }

    /* 判断是http还是https判断是否使用ssl */
    if(task->protocol == 443 && ssl){
        SSL_library_init();                                       // 初始化加载 OpenSSL 内部的错误信息、加密算法
        SSL_CTX *ctx =  SSL_CTX_new(TLS_client_method());    // 一个全局的 SSL_CTX（上下文）对象，用于配置支持的 TLS 版本及证书验证规则。
        if(!ctx){
            fprintf(stderr, "SSL_CTX_new failed!\n");
            close(tcp_fd);
		    return -1;
        }

        *ssl = SSL_new(ctx);                  // 创建一个 SSL 对象
        if (*ssl == NULL) {
            fprintf(stderr, "SSL_new failed!\n");
            close(tcp_fd);
            return -1;
        }

        SSL_set_tlsext_host_name(*ssl, task->hostname);     // 告诉服务器这次连接想要访问的具体域名是什么。（一个服务器可能有多个网站）

        SSL_set_fd(*ssl, tcp_fd);       // TCP Socket 文件描述符绑定。
        ret = SSL_connect(*ssl);         // 与服务器进行 TLS 握手，协商密钥并验证服务器证书。
        if (ret != 1) {
            fprintf(stderr, "SSL_connect failed!\n");
            SSL_free(*ssl);
            close(tcp_fd);
            return -1;
        }
        SSL_CTX_free(ctx);  // 释放CTX
    }   
    fprintf(stdout, "success!\n");
    return tcp_fd;
}

/* ------------------ 消息头 -------------------- */
typedef struct msgHead_s{
    char *head_buf;     // 指向空间的指针
    int   pos;          // 已经填充了数据的指针位置
    int   capacity;     // 整个空间的大小
} MsgHead_t;

static MsgHead_t *createMsgHead(size_t size){
    MsgHead_t *msg_head = malloc(sizeof(MsgHead_t));
    if(!msg_head){ return NULL; }

    memset(msg_head, 0, sizeof(MsgHead_t));
    msg_head->head_buf = malloc(sizeof(char) * size);
    if(!msg_head->head_buf){
        free(msg_head);
        return NULL;
    }
    msg_head->capacity = size;
    return msg_head;
}

static void releaseMsgHead(MsgHead_t *msg_head){
    if(msg_head){
        if(msg_head->head_buf){
            free(msg_head->head_buf);
        }
        free(msg_head);
    }
}

static int safeAppend(MsgHead_t *msg_head, const char *format, ...){
    if(!msg_head || !msg_head->head_buf){ return -1; }

    /* 空间已经满 */
    if(msg_head->pos >= msg_head->capacity){
        fprintf(stderr, "Warning: MsgHead buffer is fully depleted!\n");
        return -1;
    }

    /* 进行添加 */
    int remaining = msg_head->capacity - msg_head->pos;     // 计算剩下空间
    va_list args;
    va_start(args, format);
    int written = vsnprintf(msg_head->head_buf + msg_head->pos, remaining, format, args);      // 写入剩余空间
    va_end(args);

    if (written < 0) {
        fprintf(stderr, "Format error!\n"); // 格式错误
        return 0;
    }

    msg_head->pos += written;
    return written;
}

static void addRequestLine(MsgHead_t *msg_head, char *method, char *path){
    safeAppend(msg_head, "%s %s HTTP/1.1\r\n", method, path);   // 构建请求行
}

static void addRequestHead(MsgHead_t *msg_head, char *key, char *value){
    safeAppend(msg_head, "%s: %s\r\n", key, value);     // 构建请求头
}

static void addRequestEnd(MsgHead_t *msg_head){
    safeAppend(msg_head, "\r\n");   // 构建请求结束标志
}

/* ------------------ ===== -------------------- */

/* ------------------ 请求消息 -------------------- */
#define MAX_REQUEST_SIZE 8192
static MsgHead_t *requestMsg(Task_t *task){
    MsgHead_t *msg_head = createMsgHead(MAX_REQUEST_SIZE);
    if(!msg_head){ return NULL; }

    addRequestLine(msg_head, "GET", task->res_path);
	addRequestHead(msg_head, "Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
	addRequestHead(msg_head, "Host", task->hostname);
    addRequestHead(msg_head, "Connection", "close");
	// addRequestHead(msg_head, "Referer", "http://www.http2demo.io/"); // 有些服务器需要这个参数
	addRequestHead(msg_head, "User-Agent",
					   "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 "
					   "Safari/537.36 Edg/114.0.1823.37");
	addRequestEnd(msg_head);

    return msg_head;
}

static int sendRequestMsg(SSL *ssl, int tcp_fd, Task_t *task){
    /* 构建请求头 */
    MsgHead_t *msg_head = requestMsg(task);
    if(!msg_head){ return 0; }

    /* 发送消息 */
    ssize_t cnt = 0;
    ssize_t ret;
    if(task->protocol == 443){
        while(cnt < msg_head->pos){
            ret = SSL_write(ssl, msg_head->head_buf + cnt, msg_head->pos - cnt);
            if (ret < 0) {
                perror("send");
                break;
            }
            cnt += ret;
        }
    }else{
        while(cnt < msg_head->pos){
            ret = send(tcp_fd, msg_head->head_buf + cnt, msg_head->pos - cnt, 0);
            if (ret < 0) {
                perror("send");
                break;
            }
            cnt += ret;
        }
    }

    printf("send %ld/%d bytes!\n", cnt, msg_head->pos);
	if (cnt == msg_head->pos) {
        releaseMsgHead(msg_head);
		return 0;
	} else {
        releaseMsgHead(msg_head);
		return -1;
	}

    releaseMsgHead(msg_head);
}

/* ------------------ ===== -------------------- */


/* ------------------ 响应消息 -------------------- */
#define MAX_RESPONSE_SIZE 8192

static ssize_t myRecv(SSL *ssl, int tcp_fd, int protocol, char *buf, size_t len) { // 同一接收
    if (protocol == 443) {
        return SSL_read(ssl, buf, len);
    } else {
        return recv(tcp_fd, buf, len, 0);
    }
}

static int recvResponseMsgHead(SSL *ssl, int tcp_fd, int fd, Task_t *task){
    /* 接收响应头 */
    MsgHead_t *msg_head = createMsgHead(MAX_RESPONSE_SIZE);
    if(!msg_head){ return -1;}

    /* 边收边检查状态码以及\r\n头结束标志 */    
    int total_bytes = 0; // 累计收到的总字节数
    int content_len = -1; // 解析出来的 Body 长度
    int header_len = 0;  // 整个 HTTP Header 的长度

    while (1) {
        // 保证缓冲区留有至少 1 字节给 '\0'
        int room = msg_head->capacity - total_bytes - 1;
        if (room <= 0) {
            fprintf(stderr, "Header buffer overflow!\n");
            releaseMsgHead(msg_head);
            return -1;
        }

        // 1. 每次接收都追加到之前数据的末尾
        ssize_t ret = myRecv(ssl, tcp_fd, task->protocol, msg_head->head_buf + total_bytes, room);
        if (ret < 0) {
            perror("recv error");
            releaseMsgHead(msg_head);
            return -1;
        } else if (ret == 0) {
            // 服务器提前关闭了连接
            break;
        }

        total_bytes += ret;
        msg_head->head_buf[total_bytes] = '\0'; // 必须手动封口，保证 strstr 安全！

        // 2. 检查状态码是否是 200 (只需在第一次收到数据时检查一次)
        char *status_line = strstr(msg_head->head_buf, "HTTP/1.1 ");
        if (status_line) {
            char *status_code = status_line + strlen("HTTP/1.1 ");
            // 确保我们已经接收到了状态码后面的空格或换行，防止截断读取
            if (status_code < msg_head->head_buf + total_bytes - 3) {
                int code = atoi(status_code); // atoi 会自动在遇到非数字字符时停止
                if (code != 200) {
                    fprintf(stderr, "Server returned error code: %d\n", code);
                    releaseMsgHead(msg_head);
                    return -1;
                }
            }
        }

        // 3. 检测 HTTP 头部结束标志 "\r\n\r\n"
        char *header_end = strstr(msg_head->head_buf, "\r\n\r\n");
        if (header_end) {
            header_len = (header_end + 4) - msg_head->head_buf; // 计算头部总长度
            
            // 4. 解析 Content-Length
            char *cl_pos = strstr(msg_head->head_buf, "Content-Length: ");
            if (cl_pos) {
                cl_pos += strlen("Content-Length: ");
                content_len = atoi(cl_pos); // 安全解析数字
            } else {
                fprintf(stderr, "Warning: Content-Length not found!\n");
            }

            // 5. 把随头部一同接收进来的部分 Body 数据，先写入文件
            int body_received = total_bytes - header_len;
            if (body_received > 0) {
                ssize_t t = write(fd, header_end + 4, body_received);
                if (t == -1) {
                    perror("write body");
                    releaseMsgHead(msg_head);
                    return -1;
                }
            }

            // 成功收完并解析了 Header，主动跳出循环！
            break;
        }
    }

    releaseMsgHead(msg_head);
    return content_len; // 返回解析出来的真实 Body 长度
}

static int recvResponseMsg(SSL *ssl, int tcp_fd, int fd, Task_t *task){
    /* 接收消息 */
    MsgHead_t *msg_head = createMsgHead(MAX_RESPONSE_SIZE);
    if(!msg_head){ return -1;}

    int ret = myRecv(ssl, tcp_fd, task->protocol, msg_head->head_buf, msg_head->capacity);
    size_t cnt = 0;
    while(ret){
        if (ret < 0) {
            perror("recv error");
            releaseMsgHead(msg_head);
            return -1;
        }

        ssize_t write_len = write(fd, msg_head->head_buf, ret);
        if (write_len == -1) {
            perror("write body");
            releaseMsgHead(msg_head);
            return -1;
        }

        cnt += write_len;
        ret = myRecv(ssl, tcp_fd, task->protocol, msg_head->head_buf, msg_head->capacity);
    }
    releaseMsgHead(msg_head);
    return cnt;
}

/* ------------------ ===== -------------------- */

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "use: ./build [domain name]\n");
        return -1;
    }

    /* 初始化请求解决 */
    Task_t *task = createTask();
    if(!task){
        return -1;
    }

    int ret = analysisUrl2Task(argv[1], task);
    if(ret == -1){
        goto out1;
    }
    show(task);

    /* 初始化tcp连接 */
    SSL *ssl = NULL;
    int tcp_fd = initTcpCliect(task, &ssl);
    if(tcp_fd == -1){
        goto out1;
    }
    fprintf(stdout, "tcp_fd: %d\n", tcp_fd);
    

    /* 发送请求 */
    ret = sendRequestMsg(ssl, tcp_fd, task);
    if(ret == -1){
        goto out2;
    }

    /* 会议服务器的响应 */
    int fd = open(task->filename, O_CREAT | O_WRONLY, 0666);
    if(fd == -1){
        perror("open");
        goto out2;
    }
    int len = recvResponseMsgHead(ssl, tcp_fd, fd, task);
    if(len == -1){
        goto out3;
    }
    
    int r_len = recvResponseMsg(ssl, tcp_fd, fd, task);
    if(r_len == -1){
        goto out3;
    }
    
    fprintf(stdout, "byte:%d, recv: %d\n", len, r_len);
out3:
    close(fd);
out2:
    if(ssl){
        SSL_free(ssl);
    }
out1:
    freeTask(task);
    return 0;
}
```

