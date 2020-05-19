#include "tcp.h"

int main() {
    TcpSocket sock;
    sock.Connect("127.0.0.1", 8080, 0);
    sock.Send("hello server!", 0);
}