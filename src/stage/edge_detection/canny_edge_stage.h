#ifndef CANNY_EDGE_STAGE_H
#define CANNY_EDGE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class CannyEdgeStage: public StageBase {
	public:
		TrackbarValue threshold1 {25, 100};
		TrackbarValue threshold2 {25, 100};
		TrackbarValue aperture_size {0, 2};
		
		CannyEdgeStage();
		~CannyEdgeStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
