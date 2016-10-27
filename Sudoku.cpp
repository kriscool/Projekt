#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>


using namespace cv;
using namespace std;

int main()
{

    Mat sudoku = imread("zdjecia/sudoku4.jpg", 0);
    Mat outerBox = Mat(sudoku.size(), CV_8UC1);
 
    GaussianBlur(sudoku, sudoku, Size(11, 11), 0, 0);
    adaptiveThreshold(sudoku, outerBox, 255, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV, 5, 2);
    // bitwise_not(outerBox, outerBox); //whithe or black
    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
    dilate(outerBox, outerBox, kernel);
    
    int count=0;
    int max=-1;

    Point maxPt;

    for(int y=0;y<outerBox.size().height;y++)
    {
        uchar *row = outerBox.ptr(y);
        for(int x=0;x<outerBox.size().width;x++)
        {
            if(row[x]>=128)
            {

                 int area = floodFill(outerBox, Point(x,y), CV_RGB(0,0,64));

                 if(area>max)
                 {
                     maxPt = Point(x,y);
                     max = area;
                 }
            }
        }

    }

    floodFill(outerBox, maxPt, CV_RGB(255,255,255));
    for(int y=0;y<outerBox.size().height;y++)
    {
        uchar *row = outerBox.ptr(y);
        for(int x=0;x<outerBox.size().width;x++)
        {
            if(row[x]==64 && x!=maxPt.x && y!=maxPt.y)
            {
                int area = floodFill(outerBox, Point(x,y), CV_RGB(0,0,0));
            }
        }
    }
    
    erode(outerBox, outerBox, kernel);
    imshow("Sudoku", outerBox);

    
    waitKey(0); 
    return 0;
}
