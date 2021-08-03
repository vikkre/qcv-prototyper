#ifndef RECTANGLE_SIZE_FILTER_STAGE_H
#define RECTANGLE_SIZE_FILTER_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RectangleSizeFilterStage: public StageBase {
	public:
		TrackbarValue min_height {30, 10000};
		TrackbarValue min_width  {30, 10000};
		TrackbarValue max_height {80, 10000};
		TrackbarValue max_width  {80, 10000};

		RectangleSizeFilterStage();
		~RectangleSizeFilterStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
