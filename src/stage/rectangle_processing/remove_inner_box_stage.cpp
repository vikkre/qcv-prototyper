#include "remove_inner_box_stage.h"


RemoveInnerBoxStage::RemoveInnerBoxStage()
:StageBase("Remove inner Boxes") {
	setAddLineColor();
}

RemoveInnerBoxStage::~RemoveInnerBoxStage() = default;

void RemoveInnerBoxStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	const std::vector<BoundingData>& input_bounds = input.get<std::vector<BoundingData>>();
	std::vector<BoundingData> output_bounds;
	output_bounds.reserve(input_bounds.size());

	bool ok = true;
	for (const BoundingData& inner: input_bounds) {
		ok = true;

		for (const BoundingData& outer: input_bounds) {
			if (isInside(outer.rect.boundingRect(), inner.rect.boundingRect())) {
				ok = false;
				break;
			}
		}

		if (ok) {
			output_bounds.push_back(inner);
		}
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (unsigned int i = 0; i < output_bounds.size(); ++i) {
		output_bounds.at(i).drawRect(tmp_image, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(output_bounds);
}

bool RemoveInnerBoxStage::isInside(const cv::Rect& outer, const cv::Rect& inner) {
	cv::Point obr = outer.br(), otl = outer.tl();
	cv::Point ibr = inner.br(), itl = inner.tl();

	return obr.x > ibr.x
	    && obr.y > ibr.y
	    && otl.x < itl.x
	    && otl.y < itl.y;
}
