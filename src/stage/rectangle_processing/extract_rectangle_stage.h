#ifndef EXTRACT_RECTANGLE_STAGE_H
#define EXTRACT_RECTANGLE_STAGE_H

#include <opencv2/opencv.hpp>
#include "../../stage_base.h"

class ExtractRectangleStage: public StageBase {
public:
	TrackbarValue boundIndex {0, 100};

	ExtractRectangleStage();
	~ExtractRectangleStage() override;

	void init() override;
	void setData(InitStream& values) override;
	void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;
};


#endif
