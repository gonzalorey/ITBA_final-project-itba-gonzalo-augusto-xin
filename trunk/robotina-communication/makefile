INCLUDEDIR = include
OBJDIR = obj
SRCDIR = src

CFLAGS = -Wall --ansi --pedantic -g  -I$(INCLUDEDIR)

CLIENT_OBJ	=		$(OBJDIR)/client.o $(OBJDIR)/client_robot.o\
					$(CLIENT_STUB_OBJ)
SERVER_OBJ	=		$(OBJDIR)/server.o 

all: client server
	gcc $(CFLAGS) $(CLIENT_OBJ) -lm -o client

client: $(CLIENT_OBJ)
	gcc $(CFLAGS) $(CLIENT_OBJ) -lm -o client

server: $(SERVER_OBJ)
	gcc $(CFLAGS) $(SERVER_OBJ) -lm -o server
	
clean:
	rm -f *~
	rm -f $(OBJDIR)/*.o
	rm -f client
	
$(OBJDIR)/client_robot.o: $(SRCDIR)/robot/client_robot.c
	gcc $(CFLAGS) -c $(SRCDIR)/robot/client_robot.c -o $(OBJDIR)/client_robot.o
	
$(OBJDIR)/client.o: $(SRCDIR)/client.c
	gcc $(CFLAGS) -c $(SRCDIR)/client.c -o $(OBJDIR)/client.o

$(OBJDIR)/server.o: $(SRCDIR)/server.c
	gcc $(CFLAGS) -c $(SRCDIR)/server.c -o $(OBJDIR)/server.o	
