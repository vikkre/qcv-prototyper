#include "grayscale_stage.h"


GrayscaleStage::GrayscaleStage()
:StageBase("Grayscale") {}

GrayscaleStage::~GrayscaleStage() = default;

void GrayscaleStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	cv::cvtColor(input.get<cv::Mat>(), output_image, cv::COLOR_BGR2GRAY);
	showImage(output_image);

	output.set(output_image);
}
