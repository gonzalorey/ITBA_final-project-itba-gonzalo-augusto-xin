/**
 * stream_client.c:
 * OpenCV video streaming client
 *
 * Author  Nash <me_at_nashruddin.com>
 *
 * See the tutorial at 
 * http://nashruddin.com/StrEAMinG_oPENcv_vIdEos_ovER_tHe_nEtWoRk
 */
 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "cv.h"
#include "highgui.h"

#include "../include/client.h"
 
IplImage* img;
int       is_data_ready = 0;
int       sock;
char*     server_ip;
int       server_port;
int     width;
int     height;
int     key;
int     depth;
int     nChannels;
int     widthStep;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
void* streamClient(void* arg);
void  quit(char* msg, int retval);
 
int main(int argc, char** argv)
{
    pthread_t thread_c;
 
    if (argc != 8) {
        quit(USAGE, 0);
    }
 
    /* get the parameters */
    server_ip   = argv[1];
    server_port = atoi(argv[2]);
    width       = atoi(argv[3]);
    height      = atoi(argv[4]);
    depth       = atoi(argv[5]);
    nChannels   = atoi(argv[6]);
    widthStep   = atoi(argv[7]);
 
    /* create image */
    img = cvCreateImage(cvSize(width, height), depth, nChannels);
    img->widthStep = widthStep;
    
 
    /* run the streaming client as a separate thread */
    if (pthread_create(&thread_c, NULL, streamClient, NULL)) {
        quit(PTHREAD_CREATE_FAILED, 1);
    }
 
    fprintf(stdout, "Press 'q' to quit.\n\n");
    cvNamedWindow(STREAM_CLIENT, CV_WINDOW_AUTOSIZE);
 
    while(key != 'q') {
        /**
         * Display the received image, make it thread safe
         * by enclosing it using pthread_mutex_lock
         */
        pthread_mutex_lock(&mutex);
        if (is_data_ready) {
            cvShowImage(STREAM_CLIENT, img);
            is_data_ready = 0;
        }
        pthread_mutex_unlock(&mutex);
 
        key = cvWaitKey(10);
    }
 
    /* user has pressed 'q', terminate the streaming client */
    if (pthread_cancel(thread_c)) {
        quit(PTHREAD_CANCEL_FAILED, 1);
    }
 
    /* free memory */
    cvDestroyWindow(STREAM_CLIENT);
    quit(NULL, 0);
}
 
/**
 * This is the streaming client, run as separate thread
 */
void* streamClient(void* arg)
{
    struct  sockaddr_in server;
 
    /* make this thread cancellable using pthread_cancel() */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
 
    /* create socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        quit(SOCKET_FAILED, 1);
    }
 
    /* setup server parameters */
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(server_port);
 
    /* connect to server */
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        quit(CONNECT_FAILED, 1);
    }
 
    

    char* sockdata = (char*)malloc(width*height*4);

    int  i, j, k, bytes;
    
    cvSetData(img, sockdata, widthStep);
    int  imgsize = img->imageSize;
    /* start receiving images */
    while(1) 
    {
        /* get raw data */
        for (i = 0; i < imgsize; i += bytes) {
            if ((bytes = recv(sock, sockdata + i, imgsize - i, 0)) == -1) {
                quit(RECEIVE_FAILED	, 1);
            } 
        }
 
        /* convert the received data to OpenCV's IplImage format, thread safe */
        pthread_mutex_lock(&mutex);
 
        // for (i = 0, k = 0; i < img->height; i++) {
        //     for (j = 0; j < img->width; j++) {
        //         ((uchar*)(img->imageData + i * img->widthStep))[j] = sockdata[k++];
        //     }
        // }

        cvSetData(img, sockdata, widthStep);
 
        is_data_ready = 1;
        pthread_mutex_unlock(&mutex);
 
        /* have we terminated yet? */
        pthread_testcancel();
 
        /* no, take a rest for a while */
        usleep(1000);
    }
}
 
/**
 * This function provides a way to exit nicely from the system
 */
void quit(char* msg, int retval)
{
    if (retval == 0) {
        fprintf(stdout, "%s\n", (msg == NULL ? "" : msg));
        fprintf(stdout, "\n");
    } else {
        fprintf(stderr, "%s\n", (msg == NULL ? "" : msg));
        fprintf(stderr, "\n");
    }
 
    if (sock) close(sock);
    if (img) cvReleaseImage(&img);
 
    pthread_mutex_destroy(&mutex);
 
    exit(retval);
}