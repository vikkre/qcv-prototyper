#ifndef RECTANGLE_SORTER_STAGE_H
#define RECTANGLE_SORTER_STAGE_H

#include <algorithm>

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RectangleSorterStage: public StageBase {
	public:
		TrackbarValue sorting_direction {0, 1};
		TrackbarValue sorting_order {1, 1};
		TrackbarValue first_bound_color {2, 2};

		RectangleSorterStage();
		~RectangleSorterStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
