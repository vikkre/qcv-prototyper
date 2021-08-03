#include "edge_binarization_stage.h"


EdgeBinarizationStage::EdgeBinarizationStage()
:StageBase("Edge Binarization") {}

EdgeBinarizationStage::~EdgeBinarizationStage() = default;

void EdgeBinarizationStage::init() {
	createTrackbar("Minimum", minimum);
	createTrackbar("Maximum", maximum);
}

void EdgeBinarizationStage::setData(InitStream& values) {
	values.next().setTrackbarValue(minimum);
	values.next().setTrackbarValue(maximum);
}

void EdgeBinarizationStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat intermediate, output_image;

	cv::threshold(input.get<cv::Mat>(), intermediate, maximum.value, 0,   cv::ThresholdTypes::THRESH_TOZERO_INV);
	cv::threshold(intermediate,         output_image, minimum.value, 255, cv::ThresholdTypes::THRESH_BINARY);

	showImage(output_image);

	output.set(output_image);
}
