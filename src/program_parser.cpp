#include "program_parser.h"

#include <utility>


ParseException::ParseException(std::string  text)
:text(std::move(text)) {}

const char* ParseException::what() const noexcept {
	return text.c_str();
}

ProgramParser::ProgramParser() = default;

ProgramParser::~ProgramParser() = default;

Program* ProgramParser::get_program(const std::string& filename) {
	std::ifstream file(filename);

	if (file.fail()) return nullptr;

	auto* program = new Program();
	std::string line;
	while (std::getline(file, line)) {
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

		if (!line.empty() && line.at(0) != '#') {
			program->addStage(parse_line(line));
		}
	}

	return program;
}

StageBase* ProgramParser::parse_line(const std::string& line) {
	std::stringstream stream(line);
	std::string stage_name, content;
	std::getline(stream, stage_name, '(');
	std::getline(stream, content, ')');
	StageBase* stage = getStageByName(stage_name);
	if (stage == nullptr) {
		std::string error = "No stage with name \"";
		error += stage_name;
		error += "\" found!";

		throw ParseException(error);
	}

	InitStream values;
	std::string value_pair;
	std::stringstream content_stream(content);

	while (std::getline(content_stream, value_pair, ',')) {
		InitValue value {false, false, 0, 0};
		size_t begining = value_pair.find('{');
		size_t middle = value_pair.find(';');
		size_t end = value_pair.find('}');

		if (value_pair.size() > 2) {
			if (strstr(value_pair.c_str(), ",")) {
				std::string s_value = value_pair.substr(begining + 1, middle - begining - 1);
				std::string s_max_value = value_pair.substr(middle + 1, end - middle - 1);

				value.present = true;
				value.max_value_present = true;

				value.value = std::atoi(s_value.c_str());
				value.max_value = std::atoi(s_max_value.c_str());
			} else {
				std::string s_value = value_pair.substr(begining + 1, end - begining - 1);

				value.present = true;

				value.value = std::atoi(s_value.c_str());
			}
		}

		values.push(value);
	}

	stage->setStageData(values);
	return stage;
}
