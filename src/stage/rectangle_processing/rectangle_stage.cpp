#include "rectangle_stage.h"


RectangleStage::RectangleStage()
:StageBase("Rectangles") {
	setAddLineColor();
}

RectangleStage::~RectangleStage() = default;

void RectangleStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	PointMatrix input_contours = input.get<PointMatrix>();
	
	PointMatrix contours_poly(input_contours.size());
	std::vector<BoundingData> bounds(input_contours.size());

	for (unsigned int i = 0; i < input_contours.size(); ++i) {
		cv::approxPolyDP(input_contours.at(i), contours_poly.at(i), 3, true);

		cv::Rect rect = cv::boundingRect(contours_poly.at(i));
		cv::Point2f center(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
		bounds.at(i).rect = cv::RotatedRect(center, cv::Size2f(rect.width, rect.height), 0.0f);
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < bounds.size(); ++i) {
		bounds.at(i).drawRect(tmp_image, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(bounds);
}
