#ifndef ROTATED_RECTANGLE_STAGE_H
#define ROTATED_RECTANGLE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RotatedRectangleStage: public StageBase {
	public:
		RotatedRectangleStage();
		~RotatedRectangleStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
