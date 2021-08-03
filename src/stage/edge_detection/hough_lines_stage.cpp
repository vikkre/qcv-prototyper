#include "hough_lines_stage.h"


HoughLinesStage::HoughLinesStage()
:StageBase("Hough Lines") {}

HoughLinesStage::~HoughLinesStage() = default;

void HoughLinesStage::init() {
	createTrackbar("Threshold", threshold);
	createTrackbar("Min Line Length", min_line_length);
	createTrackbar("Max Line Gap", max_line_gap);
}

void HoughLinesStage::setData(InitStream& values) {
	values.next().setTrackbarValue(threshold);
	values.next().setTrackbarValue(min_line_length);
	values.next().setTrackbarValue(max_line_gap);
}

void HoughLinesStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	PointList detected_lines;
	cv::HoughLinesP(input.get<cv::Mat>(), detected_lines, 1, M_PI/180, threshold.value, min_line_length.value, max_line_gap.value);

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for(unsigned int i = 0; i < detected_lines.size(); ++i) {
		const cv::Vec4i& line = detected_lines.at(i);
		cv::Point p1(line[0], line[1]);
		cv::Point p2(line[2], line[3]);

		cv::line(tmp_image, p1, p2, getLineColor(i), getLineThickness(), cv::LINE_AA);
	}
	showImage(tmp_image);

	output.set(detected_lines);
}
