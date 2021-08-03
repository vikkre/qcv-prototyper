#ifndef BASIC_BLUR_STAGE_H
#define BASIC_BLUR_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class BasicBlurStage: public StageBase {
	public:
		TrackbarValue ksize_x {3, 10};
		TrackbarValue ksize_y {3, 10};
		
		BasicBlurStage();
		~BasicBlurStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
