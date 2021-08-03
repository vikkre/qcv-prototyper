#include "convex_hull_stage.h"


ConvexHullStage::ConvexHullStage()
:StageBase("Convex Hull") {}

ConvexHullStage::~ConvexHullStage() = default;

void ConvexHullStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	PointMatrix input_contours = input.get<PointMatrix>();
	PointMatrix output_hull(input_contours.size());
	for (unsigned int i = 0; i < input_contours.size(); ++i) {
		cv::convexHull(input_contours.at(i), output_hull.at(i));
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < output_hull.size(); ++i) {
		cv::drawContours(tmp_image, output_hull, i, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(output_hull);
}
