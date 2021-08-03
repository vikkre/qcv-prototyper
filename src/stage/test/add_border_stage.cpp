#include "add_border_stage.h"


AddBorderStage::AddBorderStage()
:StageBase("Add Border") {
	setOverrideOriginal();
}

AddBorderStage::~AddBorderStage() = default;

void AddBorderStage::init() {
	createTrackbar("Border Thickness", border_thickness);
	createTrackbar("Border Type (0=Replicate,1=Black)", border_type);
}

void AddBorderStage::setData(InitStream& values) {
	values.next().setTrackbarValue(border_thickness);
	values.next().setTrackbarValue(border_type);
}

void AddBorderStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	cv::Mat input_image = input.get<cv::Mat>();
	cv::Mat output_image;

	unsigned int thickness = border_thickness.value;
	cv::Scalar border_color(0, 0, 0);
	int bt = ((bool) border_type.value ? cv::BORDER_CONSTANT : cv::BORDER_REPLICATE);
	cv::copyMakeBorder(input_image, output_image, thickness, thickness, thickness, thickness, bt, border_color);

	showImage(output_image);

	output.set(output_image);
}
