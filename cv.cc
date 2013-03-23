//å£°æIplImageæé  
#include <opencv/opencv.h>
IplImage* pFrame = NULL;   
IplImage* pFrImg = NULL;  
IplImage* pBkImg = NULL;  
CvMat* pFrameMat = NULL;  
CvMat* pFrMat = NULL;  
CvMat* pBkMat = NULL;  
CvCapture* pCapture = NULL;  
int nFrmNum = 0;  
//åå»ºçªå£  
cvNamedWindow("video", 1);  
cvNamedWindow("background",1);  
cvNamedWindow("foreground",1);  
//ä½¿çªå£æåºæå  
cvMoveWindow("video", 30, 0);  
cvMoveWindow("background", 360, 0);  
cvMoveWindow("foreground", 690, 0);  
//pCapture = cvCaptureFromAVI("2.avi");   //è¯»å¥å·²æè§é¢ç¨æ­¤å¥  
pCapture = cvCaptureFromCAM(0);           //ä»æåå¤´è¯»å¥è§é¢ç¨æ­¤  
while(pFrame = cvQueryFrame( pCapture ))  
{  
    nFrmNum++;  
    //å¦ææ¯ç¬¬ä¸å¸§ï¼éè¦ç³è¯·åå­ï¼å¹¶åå§å  
    if(nFrmNum == 1)  
    {  
                pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),IPL_DEPTH_8U,1);  
                pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);  
        pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
        pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
        pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
        //è½¬åæåééå¾ååå¤ç  
        cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);  
        cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);  
        cvConvert(pFrImg, pFrameMat);  
        cvConvert(pFrImg, pFrMat);  
        cvConvert(pFrImg, pBkMat);  
    }  
    else  
    {  
        cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);  
        cvConvert(pFrImg, pFrameMat);  
        //ååé«æ¯æ»¤æ³¢ï¼ä»¥å¹³æ»å¾å  
        cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);  
        //å½åå¸§è·èæ¯å¾ç¸å  
        cvAbsDiff(pFrameMat, pBkMat, pFrMat);  
        //äºå¼ååæ¯å¾  
        cvThreshold(pFrMat, pFrImg, 10, 255.0, CV_THRESH_BINARY);  
        //æ´æ°èæ¯  
        cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);  
        //å°èæ¯è½¬åä¸ºå¾åæ ¼å¼ï¼ç¨ä»¥æ¾ç¤º  
        cvConvert(pBkMat, pBkImg);  
        pFrame->origin = IPL_ORIGIN_BL;  
        pFrImg->origin = IPL_ORIGIN_BL;  
        pBkImg->origin = IPL_ORIGIN_BL;  
        cvShowImage("video", pFrame);  
        cvShowImage("background", pBkImg);  
        cvShowImage("foreground", pFrImg);  
        //å¦æææé®äºä»¶ï¼åè·³åºå¾ªç¯  
        //æ­¤ç­å¾ä¹ä¸ºcvShowImageå½æ°æä¾æ¶é´å®ææ¾ç¤º  
        //ç­å¾æ¶é´å¯ä»¥æ ¹æ®CPUéåº¦è°æ´  
        if( cvWaitKey(2) >= 0 )  
            break;  
    }  
}  
//éæ¯çªå£  
cvDestroyWindow("video");  
cvDestroyWindow("background");  
cvDestroyWindow("foreground");  
//éæ¾å¾ååç©éµ  
cvReleaseImage(&pFrImg);  
cvReleaseImage(&pBkImg);  
cvReleaseMat(&pFrameMat);  
cvReleaseMat(&pFrMat);  
cvReleaseMat(&pBkMat);  
cvReleaseCapture(&pCapture);  

