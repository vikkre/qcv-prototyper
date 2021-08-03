#include "harris_corner_stage.h"

#include <iostream>


HarrisCornerStage::HarrisCornerStage()
:StageBase("Harris Corner") {}

HarrisCornerStage::~HarrisCornerStage() = default;

void HarrisCornerStage::init() {
	createTrackbar("Block Size", block_size);
	createTrackbar("K Size", k_size);
	createTrackbar("K (Percent)", k_percent);
}

void HarrisCornerStage::setData(InitStream& values) {
	values.next().setTrackbarValue(block_size);
	values.next().setTrackbarValue(k_size);
	values.next().setTrackbarValue(k_percent);
}

void HarrisCornerStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat harris_img;
	cv::cornerHarris(input.get<cv::Mat>(), harris_img, block_size.value + 2, k_size.value * 2 + 1, double(k_percent.value) / 100.0);

	cv::Mat output_image;
	harris_img.convertTo(output_image, CV_8U);

	showImage(output_image);

	output.set(harris_img);
}
