#include "init_values.h"

const InitValue InitStream::default_value {false, false, 0, 0};

InitStream::InitStream()
:index(0), values() {}

InitStream::~InitStream() {}

void InitStream::push(const InitValue& value) {
	values.push_back(value);
}

InitValue InitStream::next() {
	if (values.size() > index) {
		return values.at(index++);
	} else {
		return default_value;
	}
}
