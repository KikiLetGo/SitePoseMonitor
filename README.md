# SitePoseMonitor
基于OpenPose的做坐姿提醒

这里只上传源码部分
逻辑很简单,如下：
SitePoseMonitor是主程序入口，PoseDetector通过调用OpenPose做姿态检测，PoseAnalyzer用来分析检测结果数据和提示策略，Camera是用来拍照的工具
参考main函数中的代码：
 ```cpp
int main(int argc, char* argv[])
{
    PoseDetector poseDetector;
    PoseAnalyzer poseAnalyzer;
    Camera camera;
    lastRestTime = getTimestamp();

    while (true) {
       
        camera.takePicture();//拍照
        op::Array<float> poseKeypoints = poseDetector.detectPose();//检测
        int result = poseAnalyzer.analyse(poseKeypoints);//分析
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
```
