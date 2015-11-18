CC=clang
CFLAGS=-Wall -g

SERVER_OBJS = server.o
CLIENT_OBJS = client_main.o client.o client_network.o TCPClientUtility.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $?

server: $(SERVER_OBJS)
	@g++ -Wall -o server -g $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	@g++ -Wall -o client -g $(CLIENT_OBJS) -lpthread
	
clean:
	@rm -f *.o
	@rm -f client
	@rm -f server
