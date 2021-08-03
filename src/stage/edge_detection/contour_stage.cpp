#include "contour_stage.h"


ContourStage::ContourStage()
:StageBase("Contour") {
	setAddLineColor();
}

ContourStage::~ContourStage() = default;

void ContourStage::init() {
	createTrackbar("Retrieval Mode", retrieval_mode);
	createTrackbar("Contour Approximation Mode", contour_approximation_mode);
}

void ContourStage::setData(InitStream& values) {
	values.next().setTrackbarValue(retrieval_mode);
	values.next().setTrackbarValue(contour_approximation_mode);
}

void ContourStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	PointMatrix output_contours;
	cv::findContours(input.get<cv::Mat>(), output_contours, retrieval_mode.value, contour_approximation_mode.value + 1);

	std::sort(output_contours.begin(), output_contours.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b){
		return a.at(0).x < b.at(0).x;
	});

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < output_contours.size(); ++i) {
		cv::drawContours(tmp_image, output_contours, i, getLineColor(i), getLineThickness());
	}
	writeText(tmp_image, 0, "Retrieval Mode: " + retrievalModeToString());
	writeText(tmp_image, 1, "Contour Approximation Mode: " + contourApproximationModeToString());
	showImage(tmp_image);

	output.set(output_contours);
}

std::string ContourStage::retrievalModeToString() const {
	switch (retrieval_mode.value) {
		case cv::RetrievalModes::RETR_EXTERNAL: return "RETR_EXTERNAL";
		case cv::RetrievalModes::RETR_LIST: return "RETR_LIST";
		case cv::RetrievalModes::RETR_CCOMP: return "RETR_CCOMP";
		case cv::RetrievalModes::RETR_TREE: return "RETR_TREE";
		default: return "";
	}
}

std::string ContourStage::contourApproximationModeToString() const {
	switch (contour_approximation_mode.value + 1) {
		case cv::ContourApproximationModes::CHAIN_APPROX_NONE: return "CHAIN_APPROX_NONE";
		case cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE: return "CHAIN_APPROX_SIMPLE";
		case cv::ContourApproximationModes::CHAIN_APPROX_TC89_L1: return "CHAIN_APPROX_TC89_L1";
		case cv::ContourApproximationModes::CHAIN_APPROX_TC89_KCOS: return "CHAIN_APPROX_TC89_KCOS";
		default: return "";
	}
}
