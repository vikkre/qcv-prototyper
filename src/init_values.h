#ifndef INIT_VALUES_H
#define INIT_VALUES_H

#include <vector>

#include "window.h"


struct InitValue {
	bool present;
	bool max_value_present;

	int value;
	int max_value;

	void setTrackbarValue(TrackbarValue& trackbar_value) const;
};

class InitStream {
	public:
		InitStream();
		~InitStream();

		void push(const InitValue& value);
		InitValue next();

		static const InitValue default_value;

	private:
		unsigned int index;
		std::vector<InitValue> values;
};

#endif
