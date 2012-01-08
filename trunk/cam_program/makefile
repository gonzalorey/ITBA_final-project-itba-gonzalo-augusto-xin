INCLUDEDIR = include
OBJDIR = obj
SRCDIR = src
CC = g++

CFLAGS = -g -I$(INCLUDEDIR) `pkg-config --cflags opencv` `pkg-config --libs opencv` 

CLIENT_OBJ	=		$(OBJDIR)/client.o 
SERVER_OBJ	=		$(OBJDIR)/server.o 

all: client server
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -lm -o client
	$(CC) $(CFLAGS) $(SERVER_OBJ) -lm -o server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -lm -o client

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o server
	
clean:
	rm -f *~
	rm -f $(OBJDIR)/*.o
	rm -f client
	rm -f server
	
$(OBJDIR)/client.o: $(SRCDIR)/client.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/client.c -o $(OBJDIR)/client.o

$(OBJDIR)/server.o: $(SRCDIR)/server.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/server.c -o $(OBJDIR)/server.o	
