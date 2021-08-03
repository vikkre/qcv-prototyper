#ifndef SOBEL_EDGE_STAGE_H
#define SOBEL_EDGE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class SobelEdgeStage: public StageBase {
	public:
		TrackbarValue x_order {1, 5};
		TrackbarValue y_order {0, 5};
		TrackbarValue kernel_size {0, 3};
		
		SobelEdgeStage();
		~SobelEdgeStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
