#ifndef RELOCALIZE_ARUCO_H
#define RELOCALIZE_ARUCO_H

#include <string>

// Include OpenCV libraries
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"

#include "opencv2/aruco.hpp"
#include "opencv2/aruco/dictionary.hpp"


class RelocBoard {

  double widthArenaMeters;
  double heightArenaMeters;
  cv::Mat camMatrix;
  cv::Mat distCoeffs;
  cv::aruco::DetectorParameters detectorParams;
  cv::aruco::Dictionary dictionary;
  bool refindStrategy = false;
  cv::aruco::GridBoard board;

 public:
  RelocBoard(int markersX,
             int markersY,
             float markerLength,
             float markerSeparation, std::string cameraParametersFileName);
  std::vector< cv::Point3f > calcLocation(cv::Mat query_img);
  
};

#endif
