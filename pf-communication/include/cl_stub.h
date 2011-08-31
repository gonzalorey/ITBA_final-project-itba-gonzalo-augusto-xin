#ifndef __CL_STUB_H
#define __CL_STUB_H

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


/* chpass
 * Cambia el password del usuario (pass1) por pass2
 * Retorna:
 * 		0 si pudo cambiarlo
 * 		>0 en caso de error
 * El usuario debe estar logueado
 */
int chpass(char *pass1, char *pass2);

/* getFilesFromCat
 * Recibe:
 * 	el nombre de una categoria (entrada)
 * 	un puntero a un arreglo de strings (entrada/salida)
 *  un puntero donde se dejara la cantidad de archivos que se obtuvieron
 * Retorna:
 * 		OK si no hubo errores
 * 		codigo de error (definido en defs.h) en caso de error
 *		cant con la cantidad de archivos que hay en names
 * 		names con todos los nombres
 */
int getFilesFromCat(char *category, char ***names, int *cant);


/* downloadRQ
 * Recibe:
 * 	nombre del archivo a bajar (entrada)
 * 	direccion donde dejar el ticket (entrada/salida)
 * Retorna:
 * 		0 si no hubo errores
 * 		>0 en caso de error
 */
int downloadRQ(char *category, char *filename, ticketT *ticket);


/* downloadFile
 * Recibe:
 * 	ticket del archivo a bajar
 *  el nombre del archivo que hay que crear
 * Retorna:
 * 		0 si no hubo errores
 * 		>0 en caso de error
 */
int downloadFile(int ticketID, char *file);


/* uploadRQ
 * Recibe:
 * 	nombre del archivo a subir (hasta 126 caracteres)
 * 	descripcion del archivo (hasta 255 caracteres)
 *	categoria (hasta 60 caracteres)
 *	MD5 del archivo
 * En caso de que todos los parametros sean validos, se empieza a subir el archivo,
 * sino se retorna error.
 * Retorna:
 *		0 si no hubo errores
 * 		>0 en caso de error
 */
int uploadRQ(char *filename, char *desc, char *cat, char *MD5);

/* sin comentarios
*/
int uploadFile(char *filename, char *category);

/* getUsersList
 * Recibe:
 * 	la direccion de un arreglo de strings (entrada/salida)
 *  la direccion de un int para dejar la cantidad de usuarios
 * Retorna:
 * 		0 si no hubo errores
 * 		>0 en caso de error
 * 	deja en names el arreglo de strings con los nombres de los usuarios, terminado en NULL
 */
int getUsersList(char ***names, int *cant);

/* getCats
 * Recibe:
 * 	la direccion de un arreglo de strings (entrada/salida)
 *  un puntero donde se dejaran la cantidad de categorias leidas
 * Retorna:
 * 	0 si no hubo errores
 * 	>0 en caso de error
 *	deja en cats los nombres de las categorias, terminado en NULL.
 */
int getCats(char ***cats, int *cant);

/* logout
 * Retorna:
 * 		0 si no hubo errores
 * 		>0 en caso de error
 */
int logout(void);

/* getProcess
 * Recibe:
 *		un puntero a un vector de chars (entrada/salida)
 * 		la cantidad de procesos (entrada/salida)
 * Retorna:
 *		en el puntero recibido todos los procesos que el usuario
 *			esta usando en el servidor
 * 		en cant, la cantidad de procesos
 *		0 si no hubo errores
 *		>0 en caso de error
 */
int getProcess(char ***processes, int * cant);


#endif


