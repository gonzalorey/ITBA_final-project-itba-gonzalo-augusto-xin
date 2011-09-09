/* _DEFS_H_ */

#ifndef _DEFS_H_
#define _DEFS_H_

/* codigos de error del servidor*/
#define OK					0
#define EC_LOGIN_INCORRECT 	1
#define EC_PARAM_INCORRECT	2
#define EC_NO_MORE_DOWNS	3
#define EC_WRONG_IP_PORT	4
#define EC_WRONG_TICKET		5
#define EC_TICKET_X			6
#define EC_TICKET_Z			7
#define EC_TICKET_TRIES		8
#define EC_WRONG_PASS1		9
#define EC_DUP_FILE			10
#define EC_NO_CAT			11
#define EC_TICKET_IN_USE	12
#define EC_RECV_FILE		13
#define EC_MD5				14
#define EC_SERVER_ERR		15
#define EC_INV_OPCODE		16
#define EC_NOT_LOGGED		17
#define EC_ALREADY_LOGGED	18
#define EC_WRONG_USERNAME	19
#define EC_NO_FILE_FOUND	20

/* cantidad de codigos de error*/
#define CANT_EC				21

/* strings de error para los codigos*/
#define STR_OK				"\nOK\n"
#define ES_LOGIN_INCORRECT	"\nUser/password incorrecto\n"
#define ES_PARAM_INCORRECT	"\nLos parametros son incorrectos\n"
#define ES_NO_MORE_DOWNS	"\nNo puede seguir bajando archivos por hoy\n"
#define ES_WRONG_IP_PORT	"\nEl IP no coincide con el original\n"
#define ES_WRONG_TICKET		"\nEl numero de Ticket es invalido\n"
#define ES_TICKET_X			"\nEl ticket todavia no esta habilitado. Espere!\n"
#define ES_TICKET_Z			"\nEl ticket esta vencido\n"
#define ES_TICKET_TRIES		"\nEl ticket tuvo demasiados intentos antes de estar habilitado\n"
#define ES_WRONG_PASS1		"\nEl password es invalido\n"
#define ES_DUP_FILE			"\nEl arhivo que intenta subir ya existe en esa categoria\n"
#define ES_NO_CAT			"\nLa categoria no existe. Intente nuevamente\n"
#define ES_TICKET_IN_USE	"\nNo puede adquirir otro ticket hasta no bajar el que ya tiene\n"
#define ES_RECV_FILE		"\nError al recibir el archivo\n"
#define ES_MD5				"\nError, el archivo esta corrupto\n"
#define ES_SERVER_ERR		"\nError en el servidor, intente mas tarde\n"
#define ES_INV_OPCODE		"\nLa operacion que intenta realizar es invalida\n"
#define ES_NOT_LOGGED		"\nError, usted no esta logueado\n"
#define ES_ALREADY_LOGGED	"\nUsted ya esta logueado\n"
#define ES_WRONG_USERNAME	"\nNombre de usuario invalido\n"
#define ES_NO_FILE_FOUND	"\nEl archivo no existe en el servidor. Compruebe la ortografia\n"

/* longitudes de los strings de los archivos*/
#define MAX_FILE_NAME		126+1
#define MAX_FILE_DESC		255+1
#define MAX_FILE_CAT		60+1

/* longitudes de los strings de los usuarios*/
#define MAX_NAME	25+1
#define MAX_DESC	254+1
#define MAX_PASS	25+1
#define MAX_MAIL	126+1

/* estructura de ticket para el cliente*/
typedef struct ticketT{
	unsigned int id;
	int time_x;
	int time_z;
}ticketT;


#endif

