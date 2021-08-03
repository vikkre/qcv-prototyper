#ifndef TESSERACT_STAGE_H
#define TESSERACT_STAGE_H

#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

#include "../../stage_base.h"


class TesseractStage: public StageBase {
	public:
		TesseractStage();
		~TesseractStage() override;

		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;

	private:
		tesseract::TessBaseAPI tess_api;
};


#endif
