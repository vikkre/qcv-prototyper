#ifndef MEDIAN_BLUR_STAGE_H
#define MEDIAN_BLUR_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class MedianBlurStage: public StageBase {
	public:
		TrackbarValue ksize {0, 5};
		
		MedianBlurStage();
		~MedianBlurStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
