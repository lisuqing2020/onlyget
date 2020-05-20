#include "tcp.h"
#include "http.h"
#include <memory>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

void* Working(void* arg) {
    TcpSocket* sock = (TcpSocket*)arg;
    string recv = sock->Recv(0);

    Http http(recv);

    if(http.Method() == RT_GET) {
        if(http.Path() == "404") {
            string s = "";
            s += "HTTP/1.1 404 Not Found\r\n";
            s += "content-type:text/html\r\n";
            s += "content-length:-1\r\n\r\n";
            s += "<html><head><title>404 Not Found</title></head><body><center><h1>404 Not Found</h1></center><hr><center>onlyget</center></body></html>";
            sock->Send(s, 0);
        } else {
            string s = "";
            s += "HTTP/1.1 200 OK\r\n";
            s += "content-type:text/html\r\n";
            s += "content-length:-1\r\n\r\n";
            ifstream ifs(http.Path());
            stringstream ss;
            ss << ifs.rdbuf();
            s += ss.str();
            sock->Send(s, 0);
        }
    } else {
        string s = "";
        s += "HTTP/1.1 403 Forbidden\r\n";
        s += "content-type:text/html\r\n";
        s += "content-length:-1\r\n\r\n";
        s += "<html><head><title>403 Forbidden</title></head><body><center><h1>403 Forbidden</h1></center><hr><center>onlyget</center></body></html>";
        sock->Send(s, 0);
    }

    delete sock;
}

int main() {
    TcpServer server;
    server.Listen(8080);
    while(1) {
        int ret = 0;
        TcpSocket* sock = server.Accept(ret, 3);
        if(ret != -1) {
            pthread_t tid;
            pthread_create(&tid, NULL, Working, sock);
            pthread_detach(tid);
        }
    }
}