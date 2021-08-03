#ifndef MORPH_STAGE_H
#define MORPH_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class MorphStage: public StageBase {
	public:
		TrackbarValue morph_type {0, 1};
		TrackbarValue ksize_x {3, 50};
		TrackbarValue ksize_y {3, 50};
		TrackbarValue iterations {1, 20};
		
		MorphStage();
		~MorphStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
