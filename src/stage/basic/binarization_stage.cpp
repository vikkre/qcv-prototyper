#include "binarization_stage.h"


BinarizationStage::BinarizationStage()
:StageBase("Binarization") {}

BinarizationStage::~BinarizationStage() = default;

void BinarizationStage::init() {
	createTrackbar("Treshold", theshold);
	createTrackbar("Invert", invert);
}

void BinarizationStage::setData(InitStream& values) {
	values.next().setTrackbarValue(theshold);
	values.next().setTrackbarValue(invert);
}

void BinarizationStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	int type = ((bool) invert.value ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY);
	cv::threshold(input.get<cv::Mat>(), output_image, theshold.value, 255, type);
	showImage(output_image);

	output.set(output_image);
}
