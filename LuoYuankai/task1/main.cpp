#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int length=10;
vector<Point3f>obj=vector<Point3f>{
        Point3f(0, 0, 0),
        Point3f(0, length, 0),
        Point3f(length, 0, 0),
        Point3f(length, length, 0)
};
vector<Point2f>points=vector<Point2f>{
        Point2f(0, 0),
        Point2f(0, 0),
        Point2f( 0, 0),
        Point2f(0, 0)
};
Mat camera=(Mat_<double>(3,3)<<511.246638444332,0,0,0,510.951006801711,0,
        316.910083508333,238.170857302231,1);
Mat dis=(Mat_<double>(1,5)<<-0.0468419499777550,	1.21568506806090,	-5.74923687394028,0,0);


int main(){
    VideoCapture capture(0);
    while(true){
        Mat frame;
        capture >> frame;
        QRCodeDetector qr_detector;
        string qr_code_found = qr_detector.detectAndDecode(frame,  points);

        // 检查是否成功检测到二维码

            // 提取四个角点
            if (points.size()==4) {
                cv::Point pt1 = points[0];
                cv::Point pt2 = points[1];
                cv::Point pt3 = points[2];
                cv::Point pt4 = points[3];

                // 在图像上绘制四个角点
                cv::circle(frame, pt1, 5, cv::Scalar(0, 0, 255), -1);
                cv::circle(frame, pt2, 5, cv::Scalar(0, 255, 0), -1);
                cv::circle(frame, pt3, 5, cv::Scalar(255, 0, 0), -1);
                cv::circle(frame, pt4, 5, cv::Scalar(255, 255, 0), -1);

                // 保存结果图像
                cv::imwrite("result_image.jpg", frame);
                Mat rVec=  Mat::zeros(3,1,CV_64FC1);
                Mat tVec=  Mat::zeros(3,1,CV_64FC1);
                solvePnP(obj,points,camera,dis,rVec,tVec,false);
                cout<<rVec<<endl;
                cout<<tVec<<endl;
            }


        imshow("QR",frame);
            waitKey(1);




    }


}
