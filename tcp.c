//
// TCP连接并传输信息的功能。
// 此应用专门为旧版梦鸿打造，可能无法正常运行。
//

#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void tcp_send_recv(char* host_name, char* port) {
    int sockfd, n;
    struct addrinfo hints, *servinfo, *rp;
    char buffer[256];

    if (strlen(host_name) == 0 || strlen(port) == 0) {
        fprintf(stderr, "输入对方的主机地址和端口号，请。\n");
        exit(EXIT_FAILURE);
    }

    // 造地址出来
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // 得到服务器地址信息
    if ((getaddrinfo(host_name, port, &hints, &servinfo)) < 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    // 弄一个套接字，并连接上
    for (rp = servinfo; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; // success

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "客户端：没连上，都事用户的错。\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 干活
        printf("输入信息，请: ");
        memset(buffer, 0, 256);
        if (fgets(buffer, 255, stdin) == NULL) {
            exit(EXIT_SUCCESS);
        }

        // 发送给对面儿
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "再见，请。", 17) == 0)
            break;

        // 读对面儿的回复
        memset(buffer, 0, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("%s\n", buffer);
    }

    close(sockfd);
    freeaddrinfo(servinfo);
}
