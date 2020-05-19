#include "tcp.h"
#include "http.h"
#include <memory>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void* Working(void* arg) {
    TcpSocket* sock = (TcpSocket*)arg;
    string recv = sock->Recv(0);
    cout << recv << endl;

    Http http(recv);
}

int main() {
    TcpServer server;
    server.Listen(8080);
    while(1) {
        cout << "等待客户端连接...\n";
        int ret;
        TcpSocket* sock = server.Accept(ret, 3);
        if(ret != -1) {
            pthread_t tid;
            pthread_create(&tid, NULL, Working, sock);
            pthread_detach(tid);
        }
    }
}