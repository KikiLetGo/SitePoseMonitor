#pragma once
#include <openpose/headers.hpp>

enum Result
{
	NO_PERSON = -1,
	OKAY = 0,
	NECK_WRONG = 1,
	BACK_WRONG = 2,
	LEG_WRONG = 3,
	SAMPLEING = 4


};
class PoseAnalyzer
{
public:
	int analyse(op::Array<float> poseKeypoints);

private:
	double getAngle(double x1, double y1, double x2, double y2, double x3, double y3);
	static int wrongCounter;
	static int sampleCounter;

};

