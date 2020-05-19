client:
	g++ -std=c++11 client.cc src/tcp_socket.cc -Iinclude -o build/client

server:
	g++ -std=c++11 server.cc src/tcp_socket.cc src/tcp_server.cc src/http.cc -Iinclude -lpthread -o build/server