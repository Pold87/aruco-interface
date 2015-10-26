#include <iostream>
#include <string>
#include "relocalize_aruco.h"

using namespace std;

int main() {

  // Construct relocalizer with reference image path
  RelocBoard reloc(6, 6, 0.2, 0.2);

  // Read in query image
  cv::Mat query_img = cv::imread("img/picboard.jpg");

  // Get estimation (x, y, z) in pixels from relocalizer
  cv::Point3f estimation = reloc.calcLocation(query_img);

  // Print estimations
  cout << estimation.x << " " << estimation.y << " " << estimation.z << endl;

  
}
