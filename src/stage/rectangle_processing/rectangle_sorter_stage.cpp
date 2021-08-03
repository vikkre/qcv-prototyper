#include "rectangle_sorter_stage.h"


RectangleSorterStage::RectangleSorterStage()
:StageBase("Rectangle Sorting") {
	setAddLineColor();
}

RectangleSorterStage::~RectangleSorterStage() = default;

void RectangleSorterStage::init() {
	createTrackbar("Sorting Direction (x=0, y=1)", sorting_direction);
	createTrackbar("Sorting Order (descending=0, ascending=1)", sorting_order);
	createTrackbar("First Bound Color (red=0, blue=1, green=2)", first_bound_color);
}

void RectangleSorterStage::setData(InitStream& values) {
	values.next().setTrackbarValue(sorting_direction);
	values.next().setTrackbarValue(sorting_order);
	values.next().setTrackbarValue(first_bound_color);
}

void RectangleSorterStage::execute(const StageData& input, StageData& output, const cv::Mat& base_image) {
	std::vector<BoundingData> bounds = input.get<std::vector<BoundingData>>();

	bool sort_x = !bool(sorting_direction.value);
	bool sort_y = bool(sorting_direction.value);
	std::sort(bounds.begin(), bounds.end(), [sort_x, sort_y](const BoundingData& a, const BoundingData& b){
		return ((a.rect.center.x > b.rect.center.x) && sort_x) || ((a.rect.center.y > b.rect.center.y) && sort_y);
	});
	if ((bool) sorting_order.value) {
		std::reverse(bounds.begin(), bounds.end());
	}

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);

	cv::Scalar first_color(0, 0, 0);
	first_color[(first_bound_color.value + 2) % 3] = 255;
	if (bounds.size() > 0)
		bounds.at(0).drawRect(tmp_image, first_color, getLineThickness());

	for (unsigned int i = 1; i < bounds.size(); ++i) {
		bounds.at(i).drawRect(tmp_image, getLineColor(i), getLineThickness());
	}
	showImage(tmp_image);

	output.set(bounds);
}
