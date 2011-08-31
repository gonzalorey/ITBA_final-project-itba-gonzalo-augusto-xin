#ifndef _PACKET_H_
#define _PACKET_H_


/* codigos de paquetes
 * SC = server to client
 * CS = client to server
 */
#define SC_OK			0
#define SC_ERROR		1

#define CS_LOGIN		2

#define CS_CHPASS		3

#define CS_DOWN_RQ		4
#define SC_DOWN_RQ		5

#define CS_DOWN_F		6
#define SC_DOWN_F		7

#define CS_UP_RQ		8

#define CS_UP_F			9

#define CS_GET_CATF		10
#define SC_GET_CATF		11

#define CS_GET_USER		12
#define SC_GET_USER		13

#define CS_GET_CATS		14
#define SC_GET_CATS 	15

#define CS_GET_PROC		16
#define SC_GET_PROC		17

#define CS_LOGOUT		18

typedef unsigned char byteT;
typedef byteT packetCodeT;

#endif
