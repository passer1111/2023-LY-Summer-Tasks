#include <iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<string>

using namespace cv;
using namespace std;

int main()
{
   /*int sum=0;
   int num=0;
   string name;
   ifstream fin("base.txt");
   Mat per_image;
   Mat grey_image;
   Size chess_size=Size(9,6);
   vector<Point2f> per_ipoint;
   vector<vector<Point2f>> all_ipoint;
   Size image_size;
	while(getline(fin,name))
   {
	 sum++;
	 per_image=imread(name);
	 image_size.height=per_image.rows;
	 image_size.width=per_image.cols;
	 cvtColor(per_image,grey_image, COLOR_BGR2GRAY);
	 bool a=findChessboardCorners(grey_image,chess_size,per_ipoint);
	 if(a!=0)
	 {
	 find4QuadCornerSubpix(grey_image,per_ipoint,Size(5,5));
	 all_ipoint.push_back(per_ipoint);
	 num++;
	 }
   }
   vector<Point3f> per_wpoint;
   vector<vector<Point3f>> all_wpoint;
   for(int i=0;i<chess_size.height;i++)
   {
	for(int j=0;j<chess_size.width;j++)
	{
		per_wpoint.push_back(Point3f(j*24,i*24,0));
	}
   }
   all_wpoint.assign(num,per_wpoint);
   Mat cameramatrix(3, 3, CV_32FC1, cv::Scalar::all(0));
   Mat discoffs(1,5,CV_32FC1, cv::Scalar::all(0));
   vector<Mat> r;
   vector<Mat> t;
   calibrateCamera(all_wpoint,all_ipoint,image_size,cameramatrix,discoffs,r,t,0);
   cout<<cameramatrix<<endl;
   cout<<discoffs<<endl;*/
   float a[9]={3480.263884460313, 0, 1677.738069974295,
         0, 3475.009280890325, 2320.780927772835,
         0, 0, 1};
    float b[5]={0.2345565833264627, -2.424071535886444, -0.001801843403034916, -0.007990045412143456, 3.733574338590679};

   Mat cameramatrix(3, 3, CV_32FC1);
   cameramatrix =(Mat_<double>(3,3)<<3480.263884460313, 0, 1677.738069974295,
         0, 3475.009280890325, 2320.780927772835,
         0, 0, 1);

   
   Mat discoffs(1,5,CV_32FC1);
   discoffs =(Mat_<double>(1,5)<<0.2345565833264627, -2.424071535886444, -0.001801843403034916, -0.007990045412143456, 3.733574338590679);
   

	VideoCapture cap;
	cap.open(0);
	Mat img;
	vector<Point2d> qr_point;
	vector<Point3d> real_point={{0.0f,0.0f,0.0f},{100.0f,0.0f,0.0f},{100.0f,100.0f,0.0f},{0.0f,100.0f,0.0f}};
    Mat R;
	Mat T;
	QRCodeDetector qr;
	while(1)
	{
		cap.read(img);
		bool c=qr.detect(img,qr_point);
		
		
		
		if(c!=0)
		{
			for(int i=0;i<qr_point.size();i++)
		  {
			cout<<qr_point[i]<<endl;
		  }
		  solvePnP(real_point,qr_point,cameramatrix,discoffs,R,T);
           cout<<"平移矩阵"<<T<<"旋转矩阵"<<R<<endl;
		}
		cout<<"***"<<endl;
		imshow("123",img);
		if(waitKey(5)>=0)
		{
		break;
        }
	}
	cap.release();
	return 0;
}
