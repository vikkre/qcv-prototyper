#ifndef DATAS_H
#define DATAS_H

#include <vector>
#include <string>

#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>


struct BoundingData {
	cv::RotatedRect rect;
	cv::RotatedRect ellipse;

	void drawRect(cv::Mat& img, const cv::Scalar& line_color, const int line_thickness) const {
		cv::Point2f rect_points[4];
		rect.points(rect_points);
		for (int j = 0; j < 4; j++) {
			cv::line(img, rect_points[j], rect_points[(j+1)%4], line_color, line_thickness);
		}
	}
};

struct TextRect {
	cv::Rect rect;
	std::string text;

	TextRect(const cv::Rect& rect, const std::string& text)
	:rect(rect), text(text) {}
};

typedef std::vector<std::vector<cv::Point>> PointMatrix;
typedef std::vector<cv::Vec4i> PointList;

#endif
