#ifndef __CLIENT_ROBOT_H
#define __CLIENT_ROBOT_H

#include "defs.h"

#define CANT_CL_ERR	9
#define TCP 1
#define UDP 2
#define NICE 8
#define FAST 10

#define PARAM		-1
#define S_PARAM		"\nParametros incorrectos\n"
#define MEMORY		-2
#define S_MEMORY	"\nNo hay memoria disponible\n"
#define CONEXION	-3
#define S_CONEXION	"\nNo se puede conectar al servidor\n"
#define SEND		-4
#define S_SEND		"\nNo se enviaron datos al servidor\n"
#define RECV		-5
#define S_RECV		"\nNo se recibieron los datos del servidor o los datos recibidos son invalidos\n"
#define FILE_ERR1	-6
#define S_FILE_ERR1	"\nNo se puede abrir el archivo. Verifique que la ruta sea valida\n"
#define FILE_ERR2	-7
#define S_FILE_ERR2	"\nNo se puede escribir el archivo\n"
#define FILE_ERR3	-8
#define S_FILE_ERR3	"\nEl archivo descargado esta corrupto\n"
#define LOGIN		-9
#define S_LOGIN		"\nUsted no esta logueado\n"

/*
 * invocar a esta funcion antes de realizar cualquier operacion sobre el servidor
 */
int connectServer(int argc, char *argv[]);


/* login
 * Recibe:
 * 	- nombre de usuario
 * 	- password
 * Retorna:
 * 		0 si pudo loguearse
 * 		>0 en caso de error
 */
int login(char * user, char *password);

/* logout
 * Retorna:
 * 		0 si no hubo errores
 * 		>0 en caso de error
 */
int logout(void);



#endif
