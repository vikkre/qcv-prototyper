#include "median_blur_stage.h"


MedianBlurStage::MedianBlurStage()
:StageBase("Median Blur") {}

MedianBlurStage::~MedianBlurStage() = default;

void MedianBlurStage::init() {
	createTrackbar("Kernel Size (0=3, 1=5, ...)", ksize);
}

void MedianBlurStage::setData(InitStream& values) {
	values.next().setTrackbarValue(ksize);
}

void MedianBlurStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::medianBlur(input.get<cv::Mat>(), output_image, 2 * ksize.value + 3);
	showImage(output_image);

	output.set(output_image);
}
