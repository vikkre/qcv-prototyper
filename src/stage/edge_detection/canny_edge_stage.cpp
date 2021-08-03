#include "canny_edge_stage.h"


CannyEdgeStage::CannyEdgeStage()
:StageBase("Canny Edge") {}

CannyEdgeStage::~CannyEdgeStage() = default;

void CannyEdgeStage::init() {
	createTrackbar("Threshold 1", threshold1);
	createTrackbar("Threshold 2", threshold2);
	createTrackbar("Aperture Size", aperture_size);
}

void CannyEdgeStage::setData(InitStream& values) {
	values.next().setTrackbarValue(threshold1);
	values.next().setTrackbarValue(threshold2);
	values.next().setTrackbarValue(aperture_size);
}

void CannyEdgeStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	int tmp = 3 + aperture_size.value * 2; // Only odd between 3 and 7 allowed
	cv::Canny(input.get<cv::Mat>(), output_image, threshold1.value, threshold2.value, tmp);
	showImage(output_image);

	output.set(output_image);
}
