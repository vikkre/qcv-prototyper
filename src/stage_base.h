#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <exception>
#include <string>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "stage_data.h"
#include "program.h"
#include "window.h"
#include "init_values.h"


class Program;

struct StageProgram {
	unsigned int stage;
	Program* program;
};

class StageBase {
	private:
		const std::string stage_name;

		Window window;
		StageProgram stage_program;

		int text_font = cv::HersheyFonts::FONT_HERSHEY_SIMPLEX;
		double text_scale = 2;
		cv::Scalar text_bg_color = cv::Scalar(0, 0, 0);
		cv::Scalar text_color = cv::Scalar(255, 255, 255);
		int text_thickness = 7;

		bool add_line_color;
		bool override_original;
		TrackbarValue line_color_primary {0, 2};
		TrackbarValue line_color_secondary {1, 2};
		TrackbarValue line_thickness {3, 20};

	public:
		explicit StageBase(const std::string& stage_name);
		virtual ~StageBase();

		void setAddLineColor();
		void setOverrideOriginal();

		bool isOverrideOriginal() const;

		void createTrackbar(const std::string& trackbar_name, TrackbarValue& trackbar_value);
		void writeText(cv::Mat& img, unsigned int i, const std::string& text) const;
		void showImage(const cv::Mat& image);
		cv::Scalar getLineColor(unsigned int i) const;
		unsigned int getLineThickness() const;

		void init(const std::string& file_name, Program* program, unsigned int stage, bool save_stage);
		void setStageData(InitStream& values);
		virtual void init() {}
		virtual void execute(const StageData& input, StageData& output, const cv::Mat& base_image)=0;
		virtual void setData(InitStream& values) {}

		static void callback(int, void* stage);
};

#endif
