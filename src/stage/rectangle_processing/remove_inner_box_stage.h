#ifndef REMOVE_INNER_BOX_STAGE_H
#define REMOVE_INNER_BOX_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class RemoveInnerBoxStage: public StageBase {
	public:
		RemoveInnerBoxStage();
		~RemoveInnerBoxStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;

		static bool isInside(const cv::Rect& outer, const cv::Rect& inner);
};

#endif
