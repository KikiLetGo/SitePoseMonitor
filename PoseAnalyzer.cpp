#include "PoseAnalyzer.h"
#include <iostream>

int PoseAnalyzer::analyse(op::Array<float> poseKeypoints) {
    Result result = Result::OKAY;

    if (poseKeypoints.empty()) {
        std::cout << "no person found" << std::endl;
        return Result::NO_PERSON;
    }
	float pt0_x = poseKeypoints[3 * 0];
    float pt0_y = poseKeypoints[3 * 0 + 1];

    float pt1_x = poseKeypoints[3 * 1];
    float pt1_y = poseKeypoints[3 * 1 + 1];

    float pt8_x = poseKeypoints[3 * 8];
    float pt8_y = poseKeypoints[3 * 8 + 1];



    double angle1 = getAngle(pt0_x, pt0_y, pt8_x, pt8_y, pt1_x, pt1_y);
    double angle12 = getAngle(pt1_x, pt1_y, pt8_x + 1, pt8_y, pt8_x, pt8_y);

    op::opLog("angle1: " + std::to_string(angle1), op::Priority::High);
    op::opLog("angle12: " + std::to_string(angle12), op::Priority::High);

    if ( angle1 <120) {
        op::opLog("颈部姿势不正确 " , op::Priority::High);
        result = Result::NECK_WRONG;
        wrongCounter++;

    }
    if (angle12 < 90 ) {
        op::opLog("背部姿势不正确 ", op::Priority::High);
        result = Result::BACK_WRONG;
        wrongCounter++;
    }

    //连续采样3次
    sampleCounter++;
    if (sampleCounter >= 3) {
        op::opLog("采样结束 ", op::Priority::High);
        if (wrongCounter < 2) {//如果3次采样中错误姿势未累积到2个
            result = Result::OKAY;
        }
        wrongCounter = 0;
        sampleCounter = 0;
    }
    else {
        op::opLog("采样中，次数： " + std::to_string(sampleCounter), op::Priority::High);
        result = Result::SAMPLEING;

    }

    return result;
}


#include <cmath>
#define M_PI       3.14159265358979323846   // pi
double PoseAnalyzer::getAngle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double theta = atan2(x1 - x3, y1 - y3) - atan2(x2 - x3, y2 - y3);
    if (theta > M_PI)
        theta -= 2 * M_PI;
    if (theta < -M_PI)
        theta += 2 * M_PI;

    theta = abs(theta * 180.0 / M_PI);
    return theta;
}

int PoseAnalyzer::wrongCounter = 0;
int PoseAnalyzer::sampleCounter = 0;

