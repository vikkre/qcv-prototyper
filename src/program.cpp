#include "program.h"


Program::Program()
:image(), image_file_name(), stages(), stage_data({new StageData()}), originals({cv::Mat()}), window(nullptr) {}

Program::~Program() {
	for (StageBase* stage: stages) delete stage;
	for (StageData* data: stage_data) delete data;
}

void Program::init(const cv::Mat& image, const std::string& image_file_name, bool save_stages) {
	this->image = image;
	this->image_file_name = image_file_name;
	this->save_stages = save_stages;

	window.init(image_file_name + " - Original", nullptr, false);
	window.showImage(image);

	stage_data.at(0)->set(image);
	originals.at(0) = image;

	for (unsigned int i = 0; i < stages.size(); ++i) {
		stages.at(i)->init(this->image_file_name, this, i, this->save_stages);
	}
}

void Program::addStage(StageBase* stage) {
	stages.push_back(stage);
	stage_data.push_back(new StageData());
	originals.push_back(cv::Mat());
}

void Program::run() {
	this->update(0);
	cv::waitKey(0);
}

void Program::update(const unsigned int start_stage) {
	StageData* input;
	StageData* output;
	cv::Mat& original = image;

	for (unsigned int stage = start_stage; stage < stages.size(); ++stage) {
		output = new StageData();
		input = stage_data.at(stage);
		original = originals.at(stage);
		
		stages.at(stage)->execute(*input, *output, original);

		if (stages.at(stage)->isOverrideOriginal()) {
			original = output->get<cv::Mat>();
		}

		delete stage_data.at(stage + 1);
		stage_data.at(stage + 1) = output;
		originals.at(stage + 1) = original;
	}
}
