#include "rectangle_size_filter_stage.h"


RectangleSizeFilterStage::RectangleSizeFilterStage()
:StageBase("Rectangle Size Filter") {
	setAddLineColor();
}

RectangleSizeFilterStage::~RectangleSizeFilterStage() = default;

void RectangleSizeFilterStage::init() {
	createTrackbar("Min Box Height", min_height);
	createTrackbar("Min Box Width", min_width);
	createTrackbar("Max Box Height", max_height);
	createTrackbar("Max Box Width", max_width);
}

void RectangleSizeFilterStage::setData(InitStream& values) {
	values.next().setTrackbarValue(min_height);
	values.next().setTrackbarValue(min_width);
	values.next().setTrackbarValue(max_height);
	values.next().setTrackbarValue(max_width);
}

void RectangleSizeFilterStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	const std::vector<BoundingData>& input_rects = input.get<std::vector<BoundingData>>();
	std::vector<BoundingData> output_rects;
	output_rects.reserve(input_rects.size());

	for (const BoundingData& bound: input_rects) {
		const cv::Size2f& size = bound.rect.size;
		bool height_ok = size.height >= min_height.value && size.height <= max_height.value;
		bool width_ok = size.width >= min_width.value && size.width <= max_width.value;
		if (height_ok && width_ok) {
			output_rects.push_back(bound);
		}
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < output_rects.size(); ++i) {
		output_rects.at(i).drawRect(tmp_image, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(output_rects);
}
