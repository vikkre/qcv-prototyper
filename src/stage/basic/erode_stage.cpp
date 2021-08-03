#include "erode_stage.h"


ErodeStage::ErodeStage()
:StageBase("Erode") {}

ErodeStage::~ErodeStage() = default;

void ErodeStage::init() {
	createTrackbar("Size", size);
	createTrackbar("Iterations", iterations);
	createTrackbar("Morph Shape", morph_shape);
}

void ErodeStage::setData(InitStream& values) {
	values.next().setTrackbarValue(size);
	values.next().setTrackbarValue(iterations);
	values.next().setTrackbarValue(morph_shape);
}

void ErodeStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::Size kernel_size(2 * size.value + 1, 2 * size.value + 1);
	cv::Point kernel_point(size.value, size.value);
	cv::Mat kernel = cv::getStructuringElement(morph_shape.value, kernel_size, kernel_point);

	cv::erode(input.get<cv::Mat>(), output_image, kernel, cv::Point(-1, -1), iterations.value);

	cv::Mat tmp_image;
	output_image.copyTo(tmp_image);
	writeText(tmp_image, 0, "Morph Shape: " + morphShapeToString());
	showImage(tmp_image);

	output.set(output_image);
}

std::string ErodeStage::morphShapeToString() const {
	switch (morph_shape.value) {
		case cv::MorphShapes::MORPH_RECT: return "MORPH_RECT";
		case cv::MorphShapes::MORPH_CROSS: return "MORPH_CROSS";
		case cv::MorphShapes::MORPH_ELLIPSE: return "MORPH_ELLIPSE";
		default: return "";
	}
}
