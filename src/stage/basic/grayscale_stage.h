#ifndef GRAYSCALE_STAGE_H
#define GRAYSCALE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class GrayscaleStage: public StageBase {
	public:
		GrayscaleStage();
		~GrayscaleStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
