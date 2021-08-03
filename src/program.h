#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include <opencv2/core/mat.hpp>

#include "stage_data.h"
#include "stage_base.h"
#include "window.h"


class StageBase;

class Program {
	private:
		cv::Mat image;
		std::string image_file_name;
		std::vector<cv::Mat> originals;

		std::vector<StageBase*> stages;
		std::vector<StageData*> stage_data;
		Window window;

		bool save_stages{};

	public:
		Program();
		~Program();
		void init(const cv::Mat& image, const std::string& image_file_name, bool save_stages);

		void addStage(StageBase* stage);

		void run();
		void update(unsigned int start_stage);
};

#endif
