#include "stage_base.h"

#include <utility>


void InitValue::setTrackbarValue(TrackbarValue& trackbar_value) const {
	if (this->present) {
		trackbar_value.value = this->value;

		if (this->max_value_present) {
			trackbar_value.max_value = this->max_value;
		}
	}
}


StageBase::StageBase(const std::string& stage_name)
:stage_name(std::move(stage_name)), window(callback), stage_program(), add_line_color(false), override_original(false) {}

StageBase::~StageBase() = default;

void StageBase::setAddLineColor() {
	add_line_color = true;
}

void StageBase::setOverrideOriginal() {
	override_original = true;
}

bool StageBase::isOverrideOriginal() const {
	return override_original;
}

void StageBase::createTrackbar(const std::string& trackbar_name, TrackbarValue& trackbar_value) {
	window.createTrackbar(trackbar_name, trackbar_value);
}

void StageBase::writeText(cv::Mat& img, const unsigned int i, const std::string& text) const {
	cv::rectangle(img, cv::Point2i(0, 100 * i), cv::Point2i(2000, 100 * i + 125), text_bg_color, -1);
	cv::putText(img, text, cv::Point2i(25, 100 * i + 75), text_font, text_scale, text_color, text_thickness);
}

void StageBase::showImage(const cv::Mat& image) {
	window.showImage(image);
}

cv::Scalar StageBase::getLineColor(unsigned int i) const {
	cv::Scalar base_color(0, 0, 0);
	cv::Scalar add_color(0, 0, 0);

	base_color[(line_color_primary.value + 2) % 3] = 255;
	add_color[(line_color_secondary.value + 2) % 3] = i * 50 % 255;

	return base_color + add_color;
}

unsigned int StageBase::getLineThickness() const {
	return line_thickness.value + 1;
}

void StageBase::init(const std::string& file_name, Program* program, const unsigned int stage, bool save_stage) {
	stage_program.program = program;
	stage_program.stage = stage;

	window.init(file_name + " - Stage " + std::to_string(stage + 1) + " - " + stage_name, (void*) &stage_program, save_stage);

	this->init();
	if (add_line_color) {
		window.createTrackbar("Primary Line Color (red=0, blue=1, green=2)", line_color_primary);
		window.createTrackbar("Secondary Line Color (red=0, blue=1, green=2)", line_color_secondary);
		window.createTrackbar("Line thickness", line_thickness);
	}
}

void StageBase::setStageData(InitStream& values) {
	this->setData(values);
	if (add_line_color) {
		values.next().setTrackbarValue(line_color_primary);
		values.next().setTrackbarValue(line_color_secondary);
		values.next().setTrackbarValue(line_thickness);
	}
}

void StageBase::callback(int, void* stage) {
	auto* stage_program = (StageProgram*) stage;
	stage_program->program->update(stage_program->stage);
}
