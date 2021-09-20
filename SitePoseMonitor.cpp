#include "PoseDetector.h"
#include "PoseAnalyzer.h"
#include "Camera.h"

#include<windows.h>
#include<cstdio>

long lastRestTime = 0;
long getTimestamp() {
    time_t t;
    time(&t);
    return t;

}
int main(int argc, char* argv[])
{
    PoseDetector poseDetector;
    PoseAnalyzer poseAnalyzer;
    Camera camera;
    lastRestTime = getTimestamp();

    while (true) {
       
        camera.takePicture();
        op::Array<float> poseKeypoints = poseDetector.detectPose();
        int result = poseAnalyzer.analyse(poseKeypoints);
        if (result == Result::NECK_WRONG) {
            MessageBox(GetForegroundWindow(), TEXT("注意颈部姿势"), TEXT("SitePoseMonitor"), 1);
        }
        if (result == Result::BACK_WRONG) {
            MessageBox(GetForegroundWindow(), TEXT("注意背部姿势"), TEXT("SitePoseMonitor"), 1);
        }
        if (result == Result::NO_PERSON) {
            lastRestTime = getTimestamp();
        }
        op::opLog("已工作时间:"+std::to_string(getTimestamp() - lastRestTime), op::Priority::High);

        if (getTimestamp() - lastRestTime >= 60*60) {//1小时休息一次
            MessageBox(GetForegroundWindow(), TEXT("注意休息，去活动一下吧~"), TEXT("SitePoseMonitor"), 1);
        }
        Sleep(1000*10);

    }
    

    return 1;
}
