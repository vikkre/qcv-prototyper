#include "window.h"

#include <utility>

Window::Window(cv::TrackbarCallback callback)
:windowname("NO NAME"), callback(callback), user_data(nullptr) {}

Window::Window(std::string  windowname, cv::TrackbarCallback callback, void* user_data)
:windowname(std::move(windowname)), callback(callback), user_data(user_data) {}

Window::~Window() = default;

void Window::init(const std::string& windowname, void* user_data, bool save_copy) {
	this->windowname = windowname;
	this->user_data = user_data;
	this->save_copy = save_copy;

	cv::namedWindow(windowname, cv::WINDOW_NORMAL);
}

void Window::showImage(const cv::Mat& image) {
	cv::imshow(windowname, image);

	if (save_copy) {
		std::string windowfilename = windowname;
		std::replace(windowfilename.begin(), windowfilename.end(), '/', '_');
		std::replace(windowfilename.begin(), windowfilename.end(), '.', '_');
		std::replace(windowfilename.begin(), windowfilename.end(), ' ', '_');
		std::replace(windowfilename.begin(), windowfilename.end(), '-', '_');

		std::string filename = "out/";
		filename += windowfilename;
		filename += ".jpg";

		cv::imwrite(filename, image);
	}
}

void Window::createTrackbar(const std::string& trackbar_name, TrackbarValue& value) {
	cv::createTrackbar(trackbar_name, windowname, &value.value, value.max_value, callback, user_data);
}
