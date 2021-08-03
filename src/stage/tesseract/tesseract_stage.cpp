#include "tesseract_stage.h"

TesseractStage::TesseractStage()
:StageBase("Extract Rectangles"), tess_api(tesseract::TessBaseAPI()) {
	tess_api.Init(nullptr, "deu");
}

TesseractStage::~TesseractStage() = default;

void TesseractStage::execute(const StageData &input, StageData &output, const cv::Mat &base_image) {
	const std::vector<BoundingData>& input_bounds = input.get<std::vector<BoundingData>>();

	std::vector<TextRect> detectedText;

	detectedText.reserve(input_bounds.size());

	for(const BoundingData& bound: input_bounds) {
		cv::Rect roi = bound.rect.boundingRect();
		const cv::Mat &m = base_image;

		if (0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= m.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= m.rows) {
			const cv::Mat &text_img = base_image(roi);
			tess_api.SetImage(text_img.data, text_img.cols, text_img.rows, 3, text_img.step);

			std::string text(tess_api.GetUTF8Text());
			text = text.substr(0, text.size()-1);
			detectedText.emplace_back(roi, text);
		}
	}

	std::sort(detectedText.begin(), detectedText.end(), [](const TextRect& a, const TextRect& b){
		return a.rect.x > b.rect.x;
	});

	int text_scale = 2;
	int text_thickness = 7;

	cv::Mat tmp_image;
	base_image.copyTo(tmp_image);
	for (const TextRect& tr: detectedText) {
		cv::rectangle(tmp_image, tr.rect, cv::Scalar(255, 255, 255), cv::LineTypes::FILLED);
	}
	for (const TextRect& tr: detectedText) {
		cv::Point pos(tr.rect.tl().x, tr.rect.br().y);
		cv::putText(tmp_image, tr.text, pos, cv::HersheyFonts::FONT_HERSHEY_SIMPLEX, (double) text_scale, cv::Scalar(0, 0, 0), text_thickness);
	}
	showImage(tmp_image);

	output.set(detectedText);
}
