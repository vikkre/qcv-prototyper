#ifndef ADD_BORDER_STAGE_H
#define ADD_BORDER_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class AddBorderStage: public StageBase {
	public:
		TrackbarValue border_thickness {100, 500};
		TrackbarValue border_type {1, 1};

		AddBorderStage();
		~AddBorderStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};

#endif
