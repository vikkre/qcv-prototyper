#include "get_stage.h"

// basic
#include "stage/basic/binarization_stage.h"
#include "stage/basic/dilate_stage.h"
#include "stage/basic/edge_binarization_stage.h"
#include "stage/basic/erode_stage.h"
#include "stage/basic/grayscale_stage.h"
#include "stage/basic/morph_stage.h"

// blur
#include "stage/blur/basic_blur_stage.h"
#include "stage/blur/bilateral_filter_stage.h"
#include "stage/blur/gaussian_blur_stage.h"
#include "stage/blur/median_blur_stage.h"

// edge_detection
#include "stage/edge_detection/canny_edge_stage.h"
#include "stage/edge_detection/contour_stage.h"
#include "stage/edge_detection/convex_hull_stage.h"
#include "stage/edge_detection/harris_corner_stage.h"
#include "stage/edge_detection/hough_lines_stage.h"
#include "stage/edge_detection/sobel_edge_stage.h"

// rectangle_processing
#include "stage/rectangle_processing/extract_rectangle_stage.h"
#include "stage/rectangle_processing/rectangle_size_filter_stage.h"
#include "stage/rectangle_processing/rectangle_sorter_stage.h"
#include "stage/rectangle_processing/rectangle_stage.h"
#include "stage/rectangle_processing/remove_inner_box_stage.h"
#include "stage/rectangle_processing/reorientation_stage.h"
#include "stage/rectangle_processing/rotated_rectangle_stage.h"

// tesseract
#include "stage/tesseract/tesseract_stage.h"

// test
#include "stage/test/add_border_stage.h"
#include "stage/test/rotation_stage.h"
#include "stage/test/scale_stage.h"
#include "stage/test/translation_stage.h"


StageBase* getStageByName(const std::string& name) {
	if (false) {}

	// basic
	else if (name == "BinarizationStage")        return new BinarizationStage();
	else if (name == "DilateStage")              return new DilateStage();
	else if (name == "EdgeBinarizationStage")    return new EdgeBinarizationStage();
	else if (name == "ErodeStage")               return new ErodeStage();
	else if (name == "GrayscaleStage")           return new GrayscaleStage();
	else if (name == "MorphStage")               return new MorphStage();

	// blur
	else if (name == "BasicBlurStage")           return new BasicBlurStage();
	else if (name == "BilateralFilterStage")     return new BilateralFilterStage();
	else if (name == "GaussianBlurStage")        return new GaussianBlurStage();
	else if (name == "MedianBlurStage")          return new MedianBlurStage();

	// edge_detection
	else if (name == "CannyEdgeStage")           return new CannyEdgeStage();
	else if (name == "ContourStage")             return new ContourStage();
	else if (name == "ConvexHullStage")          return new ConvexHullStage();
	else if (name == "HarrisCornerStage")        return new HarrisCornerStage();
	else if (name == "HoughLinesStage")          return new HoughLinesStage();
	else if (name == "SobelEdgeStage")           return new SobelEdgeStage();

	// rectangle_processing
	else if (name == "ExtractRectangleStage")    return new ExtractRectangleStage();
	else if (name == "RectangleSizeFilterStage") return new RectangleSizeFilterStage();
	else if (name == "RectangleSorterStage")     return new RectangleSorterStage();
	else if (name == "RectangleStage")           return new RectangleStage();
	else if (name == "RemoveInnerBoxStage")      return new RemoveInnerBoxStage();
	else if (name == "ReorientationStage")       return new ReorientationStage();
	else if (name == "RotatedRectangleStage")    return new RotatedRectangleStage();

	// tesseract
	else if (name == "TesseractStage")           return new TesseractStage();

	// test
	else if (name == "AddBorderStage")           return new AddBorderStage();
	else if (name == "RotationStage")            return new RotationStage();
	else if (name == "ScaleStage")               return new ScaleStage();
	else if (name == "TranslationStage")         return new TranslationStage();

	else return nullptr;
}
