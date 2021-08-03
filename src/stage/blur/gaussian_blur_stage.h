#ifndef GAUSSIAN_BLUR_STAGE_H
#define GAUSSIAN_BLUR_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class GaussianBlurStage: public StageBase {
	public:
		TrackbarValue sigma {2, 10};
		
		GaussianBlurStage();
		~GaussianBlurStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
