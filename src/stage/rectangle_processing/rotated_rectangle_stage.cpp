#include "rotated_rectangle_stage.h"


RotatedRectangleStage::RotatedRectangleStage()
:StageBase("Rotated Rectangles") {
	setAddLineColor();
}

RotatedRectangleStage::~RotatedRectangleStage() = default;

void RotatedRectangleStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	PointMatrix input_contours = input.get<PointMatrix>();
	
	std::vector<BoundingData> bounds;
	bounds.reserve(input_contours.size());

	for (auto& input_contour: input_contours) {
		cv::RotatedRect rect;
		
		if(input_contour.size() > 5) {
			rect = cv::minAreaRect(input_contour);

			bounds.push_back({rect, cv::RotatedRect()});
		}
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < bounds.size(); ++i) {
		bounds.at(i).drawRect(tmp_image, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(bounds);
}
