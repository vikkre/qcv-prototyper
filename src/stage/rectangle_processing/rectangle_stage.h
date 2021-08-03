#ifndef RECTANGLE_STAGE_H
#define RECTANGLE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RectangleStage: public StageBase {
	public:
		RectangleStage();
		~RectangleStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
