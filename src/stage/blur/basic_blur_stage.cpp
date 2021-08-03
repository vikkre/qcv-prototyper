#include "basic_blur_stage.h"


BasicBlurStage::BasicBlurStage()
:StageBase("Basic Blur") {}

BasicBlurStage::~BasicBlurStage() = default;

void BasicBlurStage::init() {
	createTrackbar("Kernel Size X", ksize_x);
	createTrackbar("Kernel Size Y", ksize_y);
}

void BasicBlurStage::setData(InitStream& values) {
	values.next().setTrackbarValue(ksize_x);
	values.next().setTrackbarValue(ksize_y);
}

void BasicBlurStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::Size ksize(ksize_x.value, ksize_y.value);
	cv::blur(input.get<cv::Mat>(), output_image, ksize);
	showImage(output_image);

	output.set(output_image);
}
