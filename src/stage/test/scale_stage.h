#ifndef SCALE_STAGE_H
#define SCALE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class ScaleStage: public StageBase {
	public:
		TrackbarValue factor_x {100, 1000};
		TrackbarValue factor_y {100, 1000};

		ScaleStage();
		~ScaleStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
