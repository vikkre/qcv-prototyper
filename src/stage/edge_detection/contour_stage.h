#ifndef CONTOUR_STAGE_H
#define CONTOUR_STAGE_H

#include <functional>

#include <opencv2/imgproc.hpp>

#include "../../stage_base.h"


class ContourStage: public StageBase {
	public:
		TrackbarValue retrieval_mode {cv::RetrievalModes::RETR_TREE, 3};
		TrackbarValue contour_approximation_mode {cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE - 1, 3};

		ContourStage();
		~ContourStage() override;

		void init() override;
		void setData(InitStream& values) override;
		void execute(const StageData& input, StageData& output, const cv::Mat& base_image) override;

		std::string retrievalModeToString() const;
		std::string contourApproximationModeToString() const;
};

#endif
