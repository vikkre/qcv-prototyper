#include "bilateral_filter_stage.h"


BilateralFilterStage::BilateralFilterStage()
:StageBase("Bilateral Filter") {}

BilateralFilterStage::~BilateralFilterStage() = default;

void BilateralFilterStage::init() {
	createTrackbar("Filter Sigma (0=computed from Space Sigma)", filter_size);
	createTrackbar("Color Sigma", sigma_color);
	createTrackbar("Space Sigma", sigma_space);
}

void BilateralFilterStage::setData(InitStream& values) {
	values.next().setTrackbarValue(filter_size);
	values.next().setTrackbarValue(sigma_color);
	values.next().setTrackbarValue(sigma_space);
}

void BilateralFilterStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::bilateralFilter(input.get<cv::Mat>(), output_image, filter_size.value, sigma_color.value, sigma_space.value);
	showImage(output_image);

	output.set(output_image);
}
