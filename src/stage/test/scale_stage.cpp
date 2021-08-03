#include "scale_stage.h"


ScaleStage::ScaleStage()
:StageBase("Scale") {
	setOverrideOriginal();
}

ScaleStage::~ScaleStage() = default;

void ScaleStage::init() {
	createTrackbar("Factor X (Percent)", factor_x);
	createTrackbar("Factor Y (Percent)", factor_y);
}

void ScaleStage::setData(InitStream& values) {
	values.next().setTrackbarValue(factor_x);
	values.next().setTrackbarValue(factor_y);
}

void ScaleStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	cv::Mat input_image = input.get<cv::Mat>();
	cv::Mat output_image;

	float fx = float(factor_x.value) / 100.0;
	float fy = float(factor_y.value) / 100.0;
	cv::resize(input_image, output_image, cv::Size(0, 0), fx, fy);

	showImage(output_image);

	output.set(output_image);
}
