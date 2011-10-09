/*
 * main.c
 *
 *  Created on: Aug 31, 2011
 *      Author: xwgou
 */



#include "client.h"
#include "robot/client_robot.h"


int main(int argc, char **argv) {
	char *ip_port[] = {"192.168.1.4", "9999"};

	int status;

	status = connectServer(ip_port);

	if (status != OK) {
		printf("%s", "connect error");
		exit(-1);
	}

	status = startConnection(TCP);

	if (status != OK) {
		printf("%s\n", strerror());
		exit(-1);
	}



	return 0;

}



