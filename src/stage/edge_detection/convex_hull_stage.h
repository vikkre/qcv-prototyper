#ifndef CONVEX_HULL_STAGE_H
#define CONVEX_HULL_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class ConvexHullStage: public StageBase {
	public:
		ConvexHullStage();
		~ConvexHullStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
