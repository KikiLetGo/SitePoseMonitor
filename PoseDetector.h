#include <openpose/headers.hpp>

class PoseDetector {
public:
	PoseDetector();
	~PoseDetector() {
		delete opWrapper;
	}

	op::Array<float> detectPose();

private:
	op::Wrapper* opWrapper;
	void configureWrapper(op::Wrapper* opWrapper);
	void printKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr);
	bool display(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr);


};