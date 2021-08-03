#include <iostream>
#include <string>

#include <opencv2/core/utility.hpp>

#include "program.h"
#include "program_parser.h"
#include "stage_base.h"


#define MISSING_PARAMTER (-1)
#define IMAGE_NOT_FOUND (-2)
#define PROGRAM_NOT_FOUND (-3)


const std::string keys =
	"{help h usage ?       |      | print this message        }"
	"{image file imagefile |<none>| image to use in program   }"
	"{program              |<none>| program to execute        }"
	"{save                 |      | save image of every stage }"
;


int main(int argc, char** argv) {
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Computer Vision Praktikum");

	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	std::string program_name = parser.get<std::string>("program");
	std::string image_filename = parser.get<std::string>("image");
	bool save_stages = parser.has("save");

	if (!parser.check()) {
		parser.printErrors();
		return MISSING_PARAMTER;
	}

	cv::Mat image = cv::imread(image_filename);
	if (!image.data) {
		std::cout << "No image data in " << image_filename << std::endl;
		return IMAGE_NOT_FOUND;
	}

	ProgramParser program_parser;
	Program* program = program_parser.get_program(program_name);
	if (program == nullptr) {
		std::cout << "Program \"" << program_name << "\" not found!" << std::endl;
		return PROGRAM_NOT_FOUND;
	}

	program->init(image, image_filename, save_stages);
	program->run();

	delete program;

	return 0;
}
