#ifndef STAGE_DATA_H
#define STAGE_DATA_H

#include <exception> 
#include <string>

#include "datas.h"


class AbstractStageData {
	public:
		AbstractStageData();
		virtual ~AbstractStageData();

		virtual const char* get_name() const=0;
};

template<typename Wanted>
class StageDataTypeException: public std::exception {
	public:
		std::string text;

		explicit StageDataTypeException(AbstractStageData* data)
		:text(std::string("StageDataTypeException: Cannot get wanted data type: \"") + typeid(Wanted).name() + "\", received type: \"" + data->get_name() + "\"") {}

		const char* what() const noexcept override {
			return text.c_str();
		}
};

template<typename T>
class SpecificStageData: public AbstractStageData {
	public:
		const T value;

		explicit SpecificStageData(const T& value)
		:AbstractStageData(), value(value) {}

		~SpecificStageData() override = default;

		const char* get_name() const override {
			return typeid(T).name();
		}
};

class StageData {
	private:
		AbstractStageData* data;

	public:
		StageData();
		~StageData();

		StageData(const StageData&) = delete;
		StageData& operator=(StageData const&) = delete;

		template<typename T>
		const T& get() const {
			auto* value = dynamic_cast<SpecificStageData<T>*>(data);
			if (value == nullptr) {
				throw StageDataTypeException<T>(data);
			}
			return value->value;
		}

		template<typename T>
		void set(const T& value) {
			this->clear();
			data = new SpecificStageData<T>(value);
		}

		void clear();
};

#endif
