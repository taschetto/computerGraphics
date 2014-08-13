/*************************************************************************************************************
   Finding contours based on a trackbar's location; the contours are updated whenever the trackbar is moved
**************************************************************************************************************/

#include <C:\OpenCV2.2\include\opencv\cv.h>
#include <C:\OpenCV2.2\include\opencv\highgui.h>


IplImage*      g_image    = NULL;
IplImage*      g_gray    = NULL;
int            g_thresh  = 206;
CvMemStorage*  g_storage  = NULL;


void on_trackbar(int)
{
	if( g_storage==NULL )
	{
		g_gray = cvCreateImage( cvGetSize(g_image), 8, 1 );
		g_storage = cvCreateMemStorage(0);
    }
	else {
		cvClearMemStorage( g_storage );
	}

	CvSeq* contours = 0;
	cvCvtColor( g_image, g_gray, CV_BGR2GRAY );

	cvShowImage("GrayScale", g_gray);

	// void cvThreshold( const CvArr* src, CvArr* dst, double threshold, double max_value, int threshold_type );
	cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_BINARY );
	//cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_BINARY_INV );
	//cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_TOZERO );
	//cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_TOZERO_INV );
	//cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_TRUNC );

	cvFindContours( g_gray, g_storage, &contours );
	cvZero( g_gray );

	if( contours )
		cvDrawContours( g_gray, contours, cvScalarAll(255), cvScalarAll(255), 100 );

	cvShowImage( "Contours", g_gray );
}


int main( int argc, char** argv )
{
	IplImage* image = cvLoadImage("supermoon.jpg", 1);
	g_image = cvLoadImage("supermoon.jpg", 1);
	cvNamedWindow( "GrayScale", 1 );
	cvNamedWindow( "Contours", 1 );
	cvNamedWindow( "Original", 1 );
	cvShowImage( "Original", image );

	// int cvCreateTrackbar( const char* trackbar_name, const char* window_name, int* value, int count, CvTrackbarCallback on_change );
	cvCreateTrackbar( "Threshold", "Contours", &g_thresh, 255, on_trackbar );

	on_trackbar(0);
	cvWaitKey();
	return 0;
}
