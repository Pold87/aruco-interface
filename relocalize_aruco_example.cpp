#include <iostream>
#include <string>
#include "relocalize_aruco.h"

using namespace std;

int main() {

  // Construct relocalizer with reference image path
  RelocBoard reloc(6, 6, 0.2, 0.2,"cam_char.yml");

  // Read in query image
  cv::Mat query_img = cv::imread("img/picboard.jpg");

  // Get estimation (x, y, z) in pixels from relocalizer
  std::vector < cv::Point3f > estimations = reloc.calcLocation(query_img);

  // Print estimations
  cout << estimations[0].x << " " << estimations[0].y << " " << estimations[0].z << endl;

  cout << estimations[1].x << " " << estimations[1].y << " " << estimations[1].z << endl;

  
}
