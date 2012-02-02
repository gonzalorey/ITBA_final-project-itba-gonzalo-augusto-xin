#include <stdio.h>
#include <string.h>

#include "cv.h"
#include "highgui.h"
#include "../include/tpl.h"

extern tpl_hook_t tpl_hook;

// typedef printf("_IplImage
// {
//     int  nSize;
//     int  ID;
//     int  nChannels;
//     int  alphaChannel;
//     int  depth;
//     char colorModel[4];
//     char channelSeq[4];
//     int  dataOrder;
//     int  origin;
//     int  align;
//     int  width;
//     int  height;
//     printf("_IplROI *roi;
//     printf("_IplImage *maskROI;
//     void  *imageId;
//     printf("_IplTileInfo *tileInfo;
//     int  imageSize;
//     char *imageData;
//     int  widthStep;
//     int  BorderMode[4];
//     int  BorderConst[4];
//     char *imageDataOrigin;
// }
// IplImage;

void compare(char* a, char* b, int size) {
    long i;
    printf("%s\n", a);
    for (i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            printf("different value at index: %ld\n", i);
            break;
        }
    }
    return;
}


void packingImg(IplImage* img, char* pattern);
IplImage* unpackingImg(char* pattern);
void showIplImage(IplImage* img);

int main(int args, char** argv) {
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);
	if (!capture) {
		fprintf(stderr, "ERROR: capture is NULL \n");
		getchar();
		return -1;
	}
	//Create a window in which the captured images will be presented
	cvNamedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	
	//Get one frame
	IplImage* originalFrame = cvQueryFrame(capture);


    showIplImage(originalFrame);
    char* d = malloc(originalFrame->imageSize);
    

    IplImage* newFrame = cvCreateImage(cvSize(originalFrame->width, originalFrame->height), originalFrame->depth, originalFrame->nChannels);
    printf("--------------------------------------------\n");
    printf("after cvCreateImage\n");
    showIplImage(newFrame);
    printf("--------------------------------------------\n");



    cvSetData(newFrame, d, originalFrame->widthStep);
    printf("after cvSetData\n");
    showIplImage(newFrame);
    printf("--------------------------------------------\n");
    
    
    memcpy(d, originalFrame->imageData, originalFrame->imageSize);
    cvSetData(newFrame, d, originalFrame->widthStep);
    printf("after memcpy and cvSetData\n");
    showIplImage(newFrame);
    printf("--------------------------------------------\n");
    
    // char* p = "S(iiiiic#c#iiiiiIIIIisii#i#s)";
 //    char* p = "iiiiiic#";
 //    printf("before packing: \n");
 //    showIplImage(originalFrame);
 //    printf("--------------------------------------------\n");
	// packingImg(originalFrame, p);
	// printf("after packing: \n");
	// IplImage* newFrame = unpackingImg(p);
	// showIplImage(newFrame);

    cvSaveImage("newFrame.jpg", newFrame, 0);
    cvSaveImage("originalFrame.jpg", originalFrame, 0);
	
    //compare(originalFrame->imageData, newFrame->imageData, originalFrame->imageSize);
	FILE* fileOriginal = fopen("imgData.dat", "a");
	FILE* fileNew = fopen("imgDataNew.dat", "a");
	fprintf(fileOriginal, "%s", originalFrame->imageData);
	fprintf(fileNew, "%s", newFrame->imageData);

	fclose(fileOriginal);
	fclose(fileNew);
     // Do not release the frame!
     //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
     //remove higher bits using AND operator

     

    // IplImage* mmm = cvCreateImage(cvSize(originalFrame->width, originalFrame->height), IPL_DEPTH_8U, 3);
    // cvZero(mmm);
    // cvSetData(mmm, originalFrame->imageData, originalFrame->widthStep);


     // cvShowImage( "mywindow", newFrame);
     // while (1) {
     // 	if ( (cvWaitKey(10) & 255) == 27 ) break;
     // }

     cvReleaseCapture(&capture);
     cvDestroyWindow("mywindow");

     return 0;
}

void packingImg(IplImage* img, char* pattern) {
	tpl_node *tn;
    int imageSize = img->imageSize;
	char ch[3686400] = {0};
    printf("%d\n\n\n", img->imageSize);
	long i;
	

	// for (i = 0; i < img->imageSize; i++) {
	// 	ch[i] = img->imageData[i];
	// }

	memcpy(ch, img->imageData, img->imageSize);

	tn = tpl_map(pattern, &img->imageSize, &img->width, &img->height, &img->depth, &img->nChannels, &img->widthStep, &ch, img->imageSize);
	tpl_pack(tn, 0);

	tpl_dump(tn, TPL_FILE, "ci_img.tpl");
    tpl_free(tn);


	return;
}

IplImage* unpackingImg(char* pattern) {
	tpl_node *tn;
	IplImage* result;
	char imgChar = 'p';
	int size;
	int w;
	int h;
	int d;
	int ch;
	int ws;
	long i = 0;
    char imageData[3686400] = {0};
	tn = tpl_map(pattern, &size, &w, &h, &d, &ch, &ws, &imageData, 3686400);
	tpl_load(tn, TPL_FILE, "ci_img.tpl");
    tpl_unpack(tn,0);

    tpl_free(tn);

    result = cvCreateImage(cvSize(w, h), d, ch);
    cvSetData(result, imageData, ws);
    // result->imageData = imageData;
    result->imageDataOrigin = NULL;
	return result;
}


// void packingImg(IplImage* img, char* pattern) {
// 	tpl_node *tn;
// 	char ch = img->imageData[0];
// 	long i;
	

// 	tn = tpl_map(pattern, &img->imageSize, &img->width, &img->height, &img->depth, &img->nChannels, &img->widthStep, &ch);
// 	tpl_pack(tn, 0);

// 	for (i = 1; i < img->imageSize; i++) {
// 		ch = img->imageData[i];
// 		tpl_pack(tn, 1);
// 	}

// 	tpl_dump(tn, TPL_FILE, "ci_img.tpl");
//     tpl_free(tn);


// 	return;
// }

// IplImage* unpackingImg(char* pattern) {
// 	tpl_node *tn;
// 	IplImage* result;
// 	char imgChar = 'p';
// 	int size;
// 	int w;
// 	int h;
// 	int d;
// 	int ch;
// 	int ws;
// 	tn = tpl_map(pattern, &size, &w, &h, &d, &ch, &ws, &imgChar);
// 	tpl_load(tn, TPL_FILE, "ci_img.tpl");
//     tpl_unpack(tn,0);

    
//     long i = 0;
//     char imageData[size];
//     imageData[0] = imgChar;
// 	for (i = 1; i < size; i++) {
// 		tpl_unpack(tn, 1);
// 		imageData[i] = imgChar;
// 	}
//     tpl_free(tn);

//     result = cvCreateImage(cvSize(w, h), d, ch);
//     cvZero(result);
//     cvSetData(result, imageData, ws);
//     result->imageDataOrigin = NULL;
// 	return result;
// }

// void packingImg(IplImage* img, char* pattern) {
// 	tpl_node *tn;
// 	tn = tpl_map(pattern, img, 4, 4, 4, 4);
// 	tpl_pack(tn, 0);
// 	tpl_dump(tn, TPL_FILE, "ci_img.tpl");
//     tpl_free(tn);


// 	return;
// }

// IplImage* unpackingImg(char* pattern) {
// 	tpl_node *tn;
// 	IplImage* result = cvCreateImage(cvSize(1280, 720), 8, 3);
// 	tn = tpl_map(pattern, result, 4, 4, 4, 4);
// 	tpl_load(tn, TPL_FILE, "ci_img.tpl");
//     tpl_unpack(tn,0);
//     tpl_free(tn);

// 	return result;
// }

void showIplImage(IplImage* img) {
	printf("nSize: %d\n", img->nSize);
    printf("ID: %d\n", img->ID);
    printf("nChannels: %d\n", img->nChannels);
    printf("alphaChannel: %d\n", img->alphaChannel);
    printf("depth: %d\n", img->depth);

    if (img->colorModel != NULL) {
    	printf("colorModel: [%c %c %c %c]\n", img->colorModel[0], img->colorModel[1], img->colorModel[2], img->colorModel[3]);
    } else {
    	printf("colorModel: NULL\n");
    }

    if (img->channelSeq != NULL) {
    	printf("channelSeq: [%c %c %c %c]\n", img->channelSeq[0], img->channelSeq[1], img->channelSeq[2], img->channelSeq[3]);
    } else {
    	printf("channelSeq: NULL\n");
    }
    
    printf("dataOrder: %d\n", img->dataOrder);
    printf("origin: %d\n", img->origin);
    printf("align: %d\n", img->align);
    printf("width: %d\n", img->width);
    printf("height: %d\n", img->height);
    printf("roi: %s\n", img->roi != NULL ? "NOT NULL" : "NULL");
    printf("_IplImage *maskROI: %s\n", img->maskROI != NULL ? "NOT NULL" : "NULL");
    printf("imageId: %s\n", (char*)img->imageId);
    printf("_IplTileInfo *tileInfo: %s\n", img->tileInfo != NULL ? "NOT NULL" : "NULL");
    printf("imageSize: %d\n", img->imageSize);
    printf("imageData: %s\n", img->imageData != NULL ? "NOT NULL" : "NULL");
    printf("widthStep: %d\n", img->widthStep);
    
    if (img->BorderMode != NULL) {
    	printf("BorderMode: [%d %d %d %d]\n", img->BorderMode[0], img->BorderMode[1], img->BorderMode[2], img->BorderMode[3]);
    } else {
    	printf("BorderMode: NULL\n");
    }
    
    if (img->BorderConst != NULL) {
    	printf("BorderConst: [%d %d %d %d]\n", img->BorderConst[0], img->BorderConst[1], img->BorderConst[2], img->BorderConst[3]);
    } else {
    	printf("BorderConst: NULL\n");
    }
    printf("imageDataOrigin: %s\n", img->imageDataOrigin);
    
}









