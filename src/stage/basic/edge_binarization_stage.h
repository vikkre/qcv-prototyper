#ifndef EDGE_BINARIZATION_STAGE_H
#define EDGE_BINARIZATION_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class EdgeBinarizationStage: public StageBase {
	public:
		TrackbarValue minimum {100, 255};
		TrackbarValue maximum {150, 255};
		
		EdgeBinarizationStage();
		~EdgeBinarizationStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
