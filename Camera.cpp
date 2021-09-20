#include "Camera.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void Camera::takePicture()
{
    VideoCapture cap(0);			 //用于打开摄像头
    char pic_Name[128] = {};     //照片名称

    if (!cap.isOpened())
    {
        cout << "The camera open failed!" << endl;
    }
    Mat frame;
    cap >> frame;
    //imshow("Camera", frame);		//展示当前窗体
   // waitKey(30);
    imwrite("test.jpg", frame);	//将Mat数据写入文件
}
