/*
 * client_robot.c
 *
 *  Created on: Aug 31, 2011
 *      Author: xwgou
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "packet.h"
#include "robot/client_robot.h"

#define BUFFLEN		512
#define SEND_FLAG	0
#define RECV_FLAG	MSG_WAITALL

/*variables globales*/
struct sockaddr_in _add;
struct sockaddr _myserver;
int _mysocket;/*socet para conectarse al servidor*/

int _niceOrFast = FAST;/*indica si se usa o no barra de porcentaje*/

int _protocol = TCP;/*indica que protocolo se usa TCP o UDP*/

char BUFFER[BUFFLEN];/*buffer para enviar y recibir*/

char *_username;/*usuario logueado*/
char *_password;/*password del usuario logueado*/

static int toDESlength(int  len);

int
connectServer(char *argv[])
{
/*	if(argc<=2)
		return PARAM;
*/
	_add.sin_family = AF_INET;
	_add.sin_port = htons(atoi(argv[1]));
	_add.sin_addr.s_addr = inet_addr(argv[0]);


	_username = NULL;
	_password = NULL;
	return OK;
}


int
startConnection(int proto)
{
	memset(BUFFER, 0, BUFFLEN);
	if(proto == TCP)
	{
		_mysocket = socket(PF_INET, SOCK_STREAM, 0);
		if(connect(_mysocket,(struct sockaddr*)&_add,
		           sizeof(struct sockaddr_in)) < 0)
			return CONEXION;
	}
	else
		_mysocket = socket(PF_INET, SOCK_DGRAM, 0);

	if(_mysocket == -1)
		return CONEXION;

	return OK;
}

int
login(char * user, char *password)
{
	int q=0;
	socklen_t socketLen; /* value-result parametro de la funcion recvfrom*/
	packetCodeT code;
	byteT len1, len2;
	char * passEncriptado;

	if(user==NULL || password==NULL || (len1=strlen(user))<=0 ||
	   (len2=strlen(password))<=0)
		return PARAM;

	_username = strdup(user);
	if(_username == NULL)
		return MEMORY;
	if( (_password = strdup(password)) == NULL)
		return MEMORY;
/**
	if( (passEncriptado=encriptar(password, password)) == NULL)
	{
		free(_username);
		return MEMORY;
	}
*/
	if(startConnection(TCP)<0)
		return CONEXION;

	code = CS_LOGIN;
	len1++;
	len2++;

	BUFFER[q++] = CS_LOGIN;
	BUFFER[q++] = (byteT)len1;
	strcpy(BUFFER+q, user);
	q+=len1;
	BUFFER[q++]= (byteT)len2;
	strcpy(BUFFER+q, passEncriptado);
	q+=toDESlength(len2);

	socketLen = sizeof(struct sockaddr_in);
	send(_mysocket, BUFFER, q, SEND_FLAG);

	free(passEncriptado);

	recv(_mysocket, &code, sizeof(packetCodeT), RECV_FLAG);

	if(code==SC_ERROR)
		recv(_mysocket, &code, sizeof(packetCodeT), RECV_FLAG);

	close(_mysocket);
	return code;
}

int
toDESlength(int  len)
{
	while( len%8 !=0)
		len++;

	return len;
}
