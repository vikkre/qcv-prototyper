#ifndef TRANSLATION_STAGE_H
#define TRANSLATION_STAGE_H

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class TranslationStage: public StageBase {
	public:
		TrackbarValue offsetX {0, 1000};
		TrackbarValue offsetY {0, 1000};
		TrackbarValue xNegative {0, 1};
		TrackbarValue yNegative {0, 1};

		TranslationStage();
		~TranslationStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;

		static int getOffsetMultiplier(int negativeFlag);
};

#endif
