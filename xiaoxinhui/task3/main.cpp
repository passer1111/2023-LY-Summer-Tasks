#include <iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include"model.h"

using namespace cv;
using namespace std;

 KalmanFilter Filter(2,2,2);
 Model_a sport;
Mat measurement =(Mat_<float>(2,1)<<0,5);
Mat predictstate=Mat::zeros(2,1,CV_32F);
Mat ans =Mat::zeros(2,1,CV_32F);


void Initializekalman()
{
  Filter.transitionMatrix=(Mat_<float>(2,2)<<1,1,0,1);
  Filter.controlMatrix=(Mat_<float>(2,2)<<1,0,0,1);
  setIdentity(Filter.measurementMatrix);
  setIdentity(Filter.processNoiseCov,Scalar::all(1));
  setIdentity(Filter.measurementNoiseCov,Scalar::all(1));
  setIdentity(Filter.errorCovPost,Scalar::all(1));
}

void a_update(Mat control)
{
    measurement.at<float>(1)=sport.getv();
    measurement.at<float>(0)=sport.getx();
    predictstate=Filter.predict(control);
    ans=Filter.correct(measurement);
    sport.update(10);
   
}

int main()
{
  sport.setmodel(0,5,0,5,2,0);
  Initializekalman();
  Mat control=Mat::zeros(2,1,CV_32F);
  control.at<float>(0)=0.5*sport.geta();
  control.at<float>(1)=sport.geta();
  int x=1000;
  int y=800;
  Mat gragh(y,x,CV_8UC3,Scalar(255,255,255));
  a_update(control);
  Point lastkfpoint(ans.at<float>(1)*(x/105.0),y-ans.at<float>(0)*(y/2750.0));
  Point kfpoint(0,0);
  Point lastmeasurement(measurement.at<float>(1)*(x/105.0),y-measurement.at<float>(0)*(y/2750.0));
  Point measurementpoint(0.0);
  Point lastpredictpoint(predictstate.at<float>(1)*(x/105.0),y-predictstate.at<float>(0)*(y/2750.0));
  Point predictpoint(0,0);
  
  
  for(int i=1;i<50;i++)
  {
    lastkfpoint.x=ans.at<float>(1,0)*(x/105.0);
    lastkfpoint.y=y-ans.at<float>(0,0)*(y/2750.0);
    lastmeasurement.x=measurement.at<float>(1)*(x/105.0);
    lastmeasurement.y=y-measurement.at<float>(0)*(y/2750.0);
    lastpredictpoint.x=predictstate.at<float>(1)*(x/105.0);
    lastpredictpoint.y=y-predictstate.at<float>(0)*(y/2750.0);
    a_update(control);
    
    
    kfpoint.x=ans.at<float>(1)*(x/105.0);
    kfpoint.y=y-ans.at<float>(0)*(y/2750.0);
    measurementpoint.x=measurement.at<float>(1)*(x/105.0);
    measurementpoint.y=y-measurement.at<float>(0)*(y/2750.0);
    predictpoint.x=predictstate.at<float>(1)*(x/105.0);
    predictpoint.y=y-predictstate.at<float>(0)*(y/2750.0);
    line(gragh,lastkfpoint,kfpoint,Scalar(255,0,0));//blue
    line(gragh,lastmeasurement,measurementpoint,Scalar(0,255,0));//green
    line(gragh,lastpredictpoint,predictpoint,Scalar(0,0,255));//red
    
  }
  imshow("1",gragh);
  waitKey(0);
  return 0;
}