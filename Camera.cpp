#include "Camera.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void Camera::takePicture()
{
    VideoCapture cap(0);			 //���ڴ�����ͷ
    char pic_Name[128] = {};     //��Ƭ����

    if (!cap.isOpened())
    {
        cout << "The camera open failed!" << endl;
    }
    Mat frame;
    cap >> frame;
    //imshow("Camera", frame);		//չʾ��ǰ����
   // waitKey(30);
    imwrite("test.jpg", frame);	//��Mat����д���ļ�
}
