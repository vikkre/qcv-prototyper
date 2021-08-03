#ifndef DILATE_STAGE_H
#define DILATE_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class DilateStage: public StageBase {
	public:
		TrackbarValue size {3, 20};
		TrackbarValue iterations {1, 20};
		TrackbarValue morph_shape {0, 2};
		
		DilateStage();
		~DilateStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;

		std::string morphShapeToString() const;
};

#endif
