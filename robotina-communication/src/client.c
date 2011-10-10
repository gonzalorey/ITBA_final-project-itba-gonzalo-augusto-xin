/*
 * main.c
 *
 *  Created on: Aug 31, 2011
 *      Author: xwgou
 */


#include "client.h"
#include "robot/client_robot.h"
//#include <string.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char **argv) {
	char *ip_port[] = {"192.168.1.4", "9999"};

	int status;

	status = connectServer(ip_port);

	if (status != OK) {
		printf("%s\n", "could not connect to the server");
		exit(-1);
	}

	status = startConnection(TCP);

	if (status != OK) {
		printf("%s\n", "could not start the connection");
		exit(-1);
	}
/**
 *
 * 	 start OpenCV
	 while (true) {

		 img = OpenCV.getImage
		 send(img)
	 }
 *
 */


	while (1) {
		/**
		 * Obtein image
		 * img = OpenCv.getImage
		 * send(img)
		 */

	}





	return 0;

}



