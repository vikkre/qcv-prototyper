#ifndef ROTATION_STAGE_H
#define ROTATION_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RotationStage: public StageBase {
	public:
		TrackbarValue angle {0, 360};
		TrackbarValue fit_to_size {1, 1};

		RotationStage();
		~RotationStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
