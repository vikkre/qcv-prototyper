#include "extract_rectangle_stage.h"

ExtractRectangleStage::ExtractRectangleStage()
:StageBase("Extract Rectangles") {
	setOverrideOriginal();
}

ExtractRectangleStage::~ExtractRectangleStage() = default;

void ExtractRectangleStage::init() {
	createTrackbar("Bound Index", boundIndex);
}

void ExtractRectangleStage::setData(InitStream& values) {
	values.next().setTrackbarValue(boundIndex);
}

void ExtractRectangleStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	const auto& input_bounds = input.get<std::vector<BoundingData>>();
	std::vector<cv::Mat> extractedBounds;
	extractedBounds.reserve(input_bounds.size());

	for(const auto& bound: input_bounds) {
		auto roi = bound.rect.boundingRect();
		auto m = base_image;
		if (0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= m.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= m.rows) {
			extractedBounds.push_back(base_image(bound.rect.boundingRect()));
		}
	}

	unsigned int bound_index = boundIndex.value < extractedBounds.size() ? boundIndex.value : 0;
	cv::Mat extracted_bound = extractedBounds[bound_index];

	showImage(extracted_bound);
	output.set(extracted_bound);
}
