CC=clang
CFLAGS=-Wall -g

SERVER_OBJS = fourSServer.o serverManager.o database.o gameData.o
CLIENT_OBJS = client_main.o client.o client_network.o TCPClientUtility.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $?

all: client server

server: $(SERVER_OBJS)
	@g++ -Wall -o server -g $(SERVER_OBJS) -lpthread

client: $(CLIENT_OBJS)
	@g++ -Wall -o client -g $(CLIENT_OBJS) -lpthread -lncurses

clean:
	@rm -f *.o
	@rm -f client
	@rm -f server
