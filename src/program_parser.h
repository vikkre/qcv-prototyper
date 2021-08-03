#ifndef PROGRAM_PARSER_H
#define PROGRAM_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>

#include "get_stage.h"
#include "program.h"
#include "init_values.h"


class ParseException: public std::exception {
	public:
		const std::string text;

		explicit ParseException(std::string  text);
		const char* what() const noexcept override;
};

class ProgramParser {
	public:
		ProgramParser();
		~ProgramParser();

		Program* get_program(const std::string& filename);
		static StageBase* parse_line(const std::string& line);
};

#endif
