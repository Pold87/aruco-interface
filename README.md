Compile:

g++ relocalize_aruco_example.cpp relocalize_aruco.cpp -o aruco_example ``pkg-config --cflags --libs opencv`` -std=c++11


Create Board:

./create_board -o myboard.png -w 7 -h 7 -l 100 -s 20 -d  DICT_7x7_1000

Script at:

https://github.com/Itseez/opencv_contrib/tree/master/modules/aruco/samples
