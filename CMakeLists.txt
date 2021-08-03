cmake_minimum_required(VERSION 3.16)
project(qcv_prototyper)
set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package( PkgConfig REQUIRED )
pkg_search_module( TESSERACT REQUIRED tesseract)
include_directories( ${TESSERACT_INCLUDE_DIRS})

file( GLOB_RECURSE PROJECT_SRC
	"src/*.h"
	"src/*.cpp"
)

add_executable( qcv_prototyper ${PROJECT_SRC} )

target_link_libraries( qcv_prototyper ${OpenCV_LIBS} ${TESSERACT_LIBRARIES} )
