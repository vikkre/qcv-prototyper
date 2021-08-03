#ifndef BILATERAL_FILTER_STAGE_H
#define BILATERAL_FILTER_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class BilateralFilterStage: public StageBase {
	public:
		TrackbarValue filter_size {3, 10};
		TrackbarValue sigma_color {10, 200};
		TrackbarValue sigma_space {10, 200};
		
		BilateralFilterStage();
		~BilateralFilterStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
