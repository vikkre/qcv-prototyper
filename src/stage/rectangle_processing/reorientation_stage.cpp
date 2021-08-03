#include "reorientation_stage.h"


ReorientationStage::ReorientationStage()
:StageBase("Reorientation") {
	setOverrideOriginal();
}

ReorientationStage::~ReorientationStage() = default;

void ReorientationStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	std::vector<BoundingData> bounds = input.get<std::vector<BoundingData>>();

	cv::Mat output_image;
	if (bounds.size() > 0) {
		cv::RotatedRect rr({0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f);
		for (const BoundingData& bound: bounds) {
			if (bound.rect.size.width > rr.size.width || bound.rect.size.height > rr.size.height) {
				rr = bound.rect;
			}
		}

		float angle = rr.angle;
		cv::Size rect_size = rr.size;

		cv::Mat intermediate, rotation = cv::getRotationMatrix2D(rr.center, angle, 1.0);
		cv::warpAffine(base_image, intermediate, rotation, base_image.size() * 5);
		cv::getRectSubPix(intermediate, rect_size, rr.center, output_image);
	} else {
		base_image.copyTo(output_image);
	}

	showImage(output_image);

	output.set(output_image);
}
