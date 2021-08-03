#include "morph_stage.h"


MorphStage::MorphStage()
:StageBase("Morphology") {}

MorphStage::~MorphStage() = default;

void MorphStage::init() {
	createTrackbar("Morph type (0=close, 1=open)", morph_type);
	createTrackbar("Kernel size x", ksize_x);
	createTrackbar("Kernel size y", ksize_y);
	createTrackbar("Iterations", iterations);
}

void MorphStage::setData(InitStream& values) {
	values.next().setTrackbarValue(morph_type);
	values.next().setTrackbarValue(ksize_x);
	values.next().setTrackbarValue(ksize_y);
	values.next().setTrackbarValue(iterations);
}

void MorphStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	int morph_op = ((bool) morph_type.value ? cv::MorphTypes::MORPH_OPEN : cv::MorphTypes::MORPH_CLOSE);
	cv::Mat structuring_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize_x.value, ksize_y.value));

	cv::morphologyEx(input.get<cv::Mat>(), output_image, morph_op, structuring_element, cv::Point(-1, -1), iterations.value);
	showImage(output_image);

	output.set(output_image);
}
