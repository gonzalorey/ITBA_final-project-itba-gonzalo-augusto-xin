INCLUDEDIR = include
OBJDIR = obj
SRCDIR = src

CFLAGS = -Wall --ansi --pedantic -g  -I$(INCLUDEDIR)

CLIENT_OBJ	=		$(OBJDIR)/client.o $(OBJDIR)/client_robot.o\
					$(CLIENT_STUB_OBJ)

all: client
	gcc $(CFLAGS) $(CLIENT_OBJ) -lm -o client

client: $(CLIENT_OBJ)
	gcc $(CFLAGS) $(CLIENT_OBJ) -lm -o client

clean:
	rm -f *~
	rm -f $(OBJDIR)/*.o
	rm -f client
	
$(OBJDIR)/client_robot.o: $(SRCDIR)/robot/client_robot.c
	gcc $(CFLAGS) -c $(SRCDIR)/robot/client_robot.c -o $(OBJDIR)/client_robot.o
	
$(OBJDIR)/client.o: $(SRCDIR)/client.c
	gcc $(CFLAGS) -c $(SRCDIR)/client.c -o $(OBJDIR)/client.o
	
