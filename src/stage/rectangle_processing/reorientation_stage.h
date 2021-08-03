#ifndef REORIENTATION_STAGE_H
#define REORIENTATION_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class ReorientationStage: public StageBase {
	public:
		ReorientationStage();
		~ReorientationStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
