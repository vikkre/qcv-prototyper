#ifndef WINDOW_H
#define WINDOW_H

#include <algorithm>
#include <string>

#include <opencv2/highgui.hpp>


struct TrackbarValue {
	int value;
	int max_value;
};

class Window {
	private:
		std::string windowname;
		cv::TrackbarCallback callback;
		void* user_data;
		bool save_copy;

	public:
		explicit Window(cv::TrackbarCallback callback);
		Window(std::string  windowname, cv::TrackbarCallback callback, void* user_data);
		~Window();

		void init(const std::string& windowname, void* user_data, bool save_copy);
		void showImage(const cv::Mat& image);
		void createTrackbar(const std::string& trackbar_name, TrackbarValue& value);
};

#endif
