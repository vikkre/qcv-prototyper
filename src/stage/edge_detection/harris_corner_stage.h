#ifndef HARRIS_CORNER_STAGE_H
#define HARRIS_CORNER_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class HarrisCornerStage: public StageBase {
	public:
		TrackbarValue block_size {0, 1};
		TrackbarValue k_size {1, 10};
		TrackbarValue k_percent {4, 100};
		
		HarrisCornerStage();
		~HarrisCornerStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
