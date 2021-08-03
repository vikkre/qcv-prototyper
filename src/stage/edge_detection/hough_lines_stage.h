#ifndef HOUGH_LINES_STAGE_H
#define HOUGH_LINES_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class HoughLinesStage: public StageBase {
	public:
		TrackbarValue threshold {50, 255};
		TrackbarValue min_line_length {50, 255};
		TrackbarValue max_line_gap {10, 100};

		HoughLinesStage();
		~HoughLinesStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
