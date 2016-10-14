//tu jest źródło i wyjaśnienie http://rsrcv.blogspot.com/2015/03/opencv-camera-capture-and-save.html

#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

String inttostr(int input)
{
       stringstream ss;
       ss << input;
       return ss.str();
}

int main(void)
{
       Mat frame;
     
         vector<int> compression_params;
//vector that stores the compression parameters of the image
       compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//specify the compression technique
       compression_params.push_back(100); //specify the compression quality

       int photocount = 0; //initialize image counter
       String imagename;
       int key;
      
       VideoCapture cap(0); //open camera no.0  0=internal 1=external
       while ((key = waitKey(30)) != 27) //wait 30 milliseconds and check for esc key
       {
              cap >> frame; //save captured image to frame variable
              imshow("Camera", frame); //show image on window named Camera
              if (key == 'c')
              {
                     photocount++;// increment image number for each capture
                     imshow("Captured", frame);

                     imagename = "sudoku" + inttostr(photocount) + ".jpg";
                             //finalize imagename to save

                     imwrite(imagename, frame, compression_params);

              }

       }
}
