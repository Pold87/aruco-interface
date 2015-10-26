// Include standard libraries
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/aruco.hpp"
#include "opencv2/aruco/dictionary.hpp"


#include "relocalize_aruco.h"

using namespace std;
using namespace cv;
const double pi = 3.14159265358979323846;

/**
 */
static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs) {
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    return true;
}

RelocBoard::RelocBoard(int markersX, int markersY, float markerLength, float markerSeparation) {

    // int dictionaryId = atoi(getParam("-d", argc, argv).c_str());
  int dictionaryId = atoi("DICT_6x6_50=8");

  dictionary =
        aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));


  // create board object
  board = aruco::GridBoard::create(markersX, markersY,
                                   markerLength, markerSeparation,
                                   dictionary);

  bool readOk = readCameraParameters("cam_char.yml",
                                     camMatrix,
                                     distCoeffs);
  if(!readOk) {
    cerr << "Invalid camera file" << endl;
  }

  detectorParams.doCornerRefinement = true; // do corner refinement in markers



}

std::vector< cv::Point3f > RelocBoard::calcLocation(cv::Mat query_img) {

  vector< int > ids;
  vector< vector< Point2f > > corners, rejected;

  // Translation and rotation vectors of the marker board
  Mat rvec, tvec;

  // detect markers
  aruco::detectMarkers(query_img, dictionary,
                       corners, ids,
                       detectorParams, rejected);

  // refind strategy to detect more markers
  if(refindStrategy) {
    aruco::refineDetectedMarkers(query_img, board,
                                 corners, ids,
                                 rejected, camMatrix,
                                 distCoeffs);
  }

  // estimate board pose
  int markersOfBoardDetected = 0;

  Point3f coords, rots;

  if(ids.size() > 0) {
    markersOfBoardDetected =
        aruco::estimatePoseBoard(corners, ids,
                                 board, camMatrix,
                                 distCoeffs, rvec, tvec);


    aruco::drawDetectedMarkers(query_img, corners, ids);
    
    cv::Mat R;
    cv::Rodrigues(rvec, R);  // R is 3x3
    
    R = R.t();  // rotation of inverse
    
    cv::Mat tvec_cam, rvec_cam;

    // The rotation is coded in R, and after using Rodrigues also in rvec. I'm not sure if one has to use the translation of the inverse as well or just rvec and how it relates to roll, pitch, yaw.
    
    tvec_cam = - R * tvec; // translation of inverse
    rvec_cam = - R * rvec; // translation of inverse

    coords.x = tvec_cam.at<double>(0);
    coords.y = tvec_cam.at<double>(1);
    coords.z = tvec_cam.at<double>(2);

    rots.x = rvec_cam.at<double>(0);
    rots.y = rvec_cam.at<double>(1);
    rots.z = rvec_cam.at<double>(2);

    
  } else {
    
    coords.x = -1;
    coords.y = -1;
    coords.z = -1;

    rots.x = -1;
    rots.y = -1;
    rots.z = -1;

  }


  std::vector<Point3f> vals(2);

  vals[0] = coords;
  vals[1] = rots;
  
  return vals;
  
}
