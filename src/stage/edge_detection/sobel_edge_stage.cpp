#include "sobel_edge_stage.h"


SobelEdgeStage::SobelEdgeStage()
:StageBase("Sobel Edge") {}

SobelEdgeStage::~SobelEdgeStage() = default;

void SobelEdgeStage::init() {
	createTrackbar("Order fo the derivative x", x_order);
	createTrackbar("Order fo the derivative y", y_order);
	createTrackbar("Kernel Size", kernel_size);
}

void SobelEdgeStage::setData(InitStream& values) {
	values.next().setTrackbarValue(x_order);
	values.next().setTrackbarValue(y_order);
	values.next().setTrackbarValue(kernel_size);
}

void SobelEdgeStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	cv::Mat output_image;

	int ksize = kernel_size.value * 2 + 1;
	cv::Sobel(input.get<cv::Mat>(), output_image, -1, x_order.value, y_order.value, ksize);
	showImage(output_image);

	output.set(output_image);
}
