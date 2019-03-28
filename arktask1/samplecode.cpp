#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/calib3d/calib3d.hpp"
#include <bits/stdc++.h>
using namespace cv;
using namespace std;
 VideoCapture vid("new.avi");
//VideoCapture vid(0);
Mat img;
int inix,iniy;
int limit =30;
//Mat img1(1080,1920,CV_8UC1,Scalar(0));
int main()
{
  //cout<<"a"<<endl;
  int flag=0;
  while(vid.isOpened())
  {
    //cout<<"b"<<endl;
    vid>>img;
    namedWindow("win2", WINDOW_NORMAL);
    imshow("win2", img);
    // int cx,cy;
    // int a,b;
    // int xi,yi;
    // for(int x=0 ;x<img.rows ;++x)
    // {
    //   for(int y=0 ;y<img.cols ;y++)
    //   {
    //     if( (img.at<Vec3b>(x,y)[0]<60) && (img.at<Vec3b>(x,y)[1]<60) && (img.at<Vec3b>(x,y)<60) )
    //     {
    //       xi = x;
    //       yi = y;
    //       break;
    //     }
    //   }
    // }
    // for(int x=0 ;x<img.rows ;++x)
    // {
    //   for(int y=0 ;y<img.cols ;y++)
    //   {
    //     if( (img.at<Vec3b>(x,y)[0]<60) && (img.at<Vec3b>(x,y)[1]<60) && (img.at<Vec3b>(x,y)[2]<60) )
    //     {
    //       a = x;
    //       b = y;   
    //     }
    //   }
    // }
    // cy = xi + (a-xi)/2 ;
    // cx = yi + (b-yi)*2/5;
    // cout<<cx;
    // cout<<cy;
    Size patternsize(5,8); //interior number of corners
    //Mat gray = img; //source image
    Mat img1(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

    vector<Point2f> corners; //this will be filled by the detected corners
    //CALIB_CB_FAST_CHECK saves a lot of time on images
    //that do not contain any chessboard corners
    bool patternfound = findChessboardCorners(img, patternsize, corners,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);
    if(patternfound)
      //cout<<"c"<<endl;
    //cornerSubPix(img, corners, Size(11, 11), Size(-1, -1),
    //TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
      drawChessboardCorners(img, patternsize, Mat(corners), patternfound);
      int max1 = 1,min1 = -1;
      int max2 = 1,min2 = -1;
      for(int k=0; k< corners.size(); ++k)
      {
        //cout<<corners[k].x<<endl;
        //cout<<corners[k].y<<endl;
        if(corners[k].x>max1)
          max1 = corners[k].x;
        if(corners[k].y>max2)
          max2 = corners[k].y;
        if(corners[k].x<min1)
          min1 = corners[k].x;
        if(corners[k].y<min2)
          min2 = corners[k].y;
      }
    int cenx,ceny;
    cenx = (max1+min1)/2;
    ceny = (max2+min2)/2;
    if(flag ==0)
    {
      inix = cenx;
      iniy = ceny;
    }
    flag++;
    if((cenx>(inix+limit))||(cenx<(inix-limit))||(ceny>(iniy+limit))||(ceny<(iniy-limit))||((cenx==0)&&(ceny==0)))
    {
      cout<<"pattern is out of limit"<<endl;
    }
    else
    {
      cout<<"x coordinate  "<<cenx<<"  y codinate   "<< ceny<<endl;
    }
    waitKey(250);
    namedWindow("win1", WINDOW_NORMAL);
    imshow("win1", img);
  }
  waitKey(0);
}
