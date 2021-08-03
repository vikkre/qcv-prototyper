#include "stage_data.h"


// AbstractStageData

AbstractStageData::AbstractStageData() = default;
AbstractStageData::~AbstractStageData() = default;


// StageData

StageData::StageData()
:data(nullptr) {}

StageData::~StageData() {
	this->clear();
}

void StageData::clear() {
	if (data != nullptr) {
		delete data;
		data = nullptr;
	}
}
