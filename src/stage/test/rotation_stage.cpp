#include "rotation_stage.h"


RotationStage::RotationStage()
:StageBase("Rotation") {
	setOverrideOriginal();
}

RotationStage::~RotationStage() = default;

void RotationStage::init() {
	createTrackbar("Angle (degree)", angle);
	createTrackbar("Fit image to new size", fit_to_size);
}

void RotationStage::setData(InitStream& values) {
	values.next().setTrackbarValue(angle);
	values.next().setTrackbarValue(fit_to_size);
}

void RotationStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	cv::Mat input_image = input.get<cv::Mat>();
	cv::Mat output_image;

	cv::Size image_size = input_image.size();
	cv::Point center(image_size.width / 2, image_size.height / 2);
	cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, angle.value, 1.0);
	cv::warpAffine(input_image, output_image, rotation_matrix, image_size);

	showImage(output_image);

	output.set(output_image);
}
