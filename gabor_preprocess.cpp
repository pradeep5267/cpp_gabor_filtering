#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <iterator>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat GaborFiltering(Mat src)
{
    Mat greyMat, colorMat, floatMat, dest, viz, kern, kernel1;
    double s;
    using std::list;
    list<Mat> kernelList;

    src.convertTo(floatMat,CV_32F);

        for (int i=0;i<16;i++){
            kernel1 = cv::getGaborKernel(Size(13,13), 4.0, 1.37446, 10.0, 0.5, 0, CV_32F);
            s = cv::sum( kernel1 )[0];

            kern = (kernel1)/(1.5*s);
            kernelList.push_back(kern);
        }
        std::list<Mat>::iterator it = kernelList.begin();
        for (int i =0;i<8;i++){
            std::advance(it, 1);
            kernel1 = *it;
            filter2D(floatMat, dest, CV_8UC3, kernel1);
            dest.convertTo(viz,CV_8UC3);
        }

    return viz;
}


Mat Preprocess(Mat src){

int s1=src.rows;
int s2=src.cols;

Mat centers, blured1, blured2, erode1, erode2, dilate1, dilate2, canny1;
std::vector<Vec4i> hierarchy;
std::vector<Point> approx;
std::vector<std::vector<Point> > contours1;

    GaussianBlur( src, blured1, Size( 13,13 ), 0, 0, 2 );


    Mat erode1_element = getStructuringElement(MORPH_RECT, Size( 7,7),Point( 0,0 ) );
    erode( blured1, erode1, erode1_element );


    Canny( erode1, canny1, 50, 70);


    Mat dilate1_element = getStructuringElement(MORPH_RECT, Size( 5,5),Point( 0,0) );
    dilate( canny1, dilate1, dilate1_element );

    findContours( dilate1, contours1, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);


std::vector<std::vector<Point> > contours_poly( contours1.size() );
std::vector<Rect> boundRect( contours1.size() );
Scalar color( 0,0,0 );
double img_area = s1*s2;
double area_thres = img_area/850;

    for (unsigned int i = 0;  i < contours1.size();  i++)
    {

        for (unsigned int j=0;  j<contours1[i].size();  j++)
        {
            if (contourArea(contours1[i])<area_thres){
                boundRect[i] = boundingRect( Mat(contours1[i]) );
                rectangle( dilate1, boundRect[i].tl(), boundRect[i].br(), color, -1 );
            }
        }
    }
return dilate1;
}


int main( int argc, char** argv )
{
    Mat gabor_d,stage_2,preprocess_d;
    Mat src = imread( argv[1], IMREAD_COLOR );

    gabor_d = GaborFiltering(src);

    GaussianBlur(gabor_d,stage_2,Size(13,13),0,0,2);

    preprocess_d = Preprocess(stage_2);

    imshow( "final image", preprocess_d );
    waitKey( 0 );

}

