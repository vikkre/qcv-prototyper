#include "translation_stage.h"


TranslationStage::TranslationStage()
:StageBase("Translation") {
	setOverrideOriginal();
}

TranslationStage::~TranslationStage() = default;

void TranslationStage::init() {
	createTrackbar("X-Offset", offsetX);
	createTrackbar("Y-Offset", offsetY);
	createTrackbar("Invert X", xNegative);
	createTrackbar("Invert Y", yNegative);
}

void TranslationStage::setData(InitStream& values) {
	values.next().setTrackbarValue(offsetX);
	values.next().setTrackbarValue(offsetY);
	values.next().setTrackbarValue(xNegative);
	values.next().setTrackbarValue(yNegative);
}

void TranslationStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	cv::Mat input_image = input.get<cv::Mat>();
	cv::Mat output_image;

	float tx = offsetX.value * getOffsetMultiplier(xNegative.value);
	float ty = offsetY.value * getOffsetMultiplier(yNegative.value);
	float translation_values[] = {1.0f, 0.0f, tx, 0.0f, 1.0f, ty};
	cv::Mat translation_matrix(2, 3, CV_32F, translation_values);

	cv::warpAffine(input_image, output_image, translation_matrix, input_image.size());

	showImage(output_image);

	output.set(output_image);
}

int TranslationStage::getOffsetMultiplier(int negativeFlag) {
	return (negativeFlag ? -1 : 1);
}
