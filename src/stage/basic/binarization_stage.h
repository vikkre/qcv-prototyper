#ifndef BINARIZATION_STAGE_H
#define BINARIZATION_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class BinarizationStage: public StageBase {
	public:
		TrackbarValue theshold {100, 250};
		TrackbarValue invert {0, 1};
		
		BinarizationStage();
		~BinarizationStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
