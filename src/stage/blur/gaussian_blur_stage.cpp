#include "gaussian_blur_stage.h"


GaussianBlurStage::GaussianBlurStage()
:StageBase("Gaussian Blur") {}

GaussianBlurStage::~GaussianBlurStage() = default;

void GaussianBlurStage::init() {
	createTrackbar("Sigma", sigma);
}

void GaussianBlurStage::setData(InitStream& values) {
	values.next().setTrackbarValue(sigma);
}

void GaussianBlurStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::GaussianBlur(input.get<cv::Mat>(), output_image, cv::Size(0, 0), sigma.value + 1);
	showImage(output_image);

	output.set(output_image);
}
