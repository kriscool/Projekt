#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

CvPoint tL, tR, bL, bR;
int length;

void cornerHarris_demo( int, void*, Mat src,  Mat src_gray )
{

  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;

  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );
      
  Point temp;
  Point minX = Point(700,700);
  Point minY = Point(700,700);
  Point maxX = Point(100,100);
  Point maxY = Point(100,100);
      
  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > 120 )
              {
                   //circle( dst_norm_scaled, Point( i,j ), 5,  Scalar(0), 2, 8, 0 );
                temp = Point( i, j );
                
              if(j == 0 && i == 0) {
                    cout<<"TEMP 1:"<<temp.x<<" "<<temp.y;
                    minX = temp;
                    minY = temp;
                    maxX = temp;
                    maxY = temp;
                }
                else{
                    if (temp.x < minX.x)
                        minX = temp;
                    if (temp.x > maxX.x)
                        maxX = temp;
                    if (temp.y < minY.y)
                        minY = temp;
                    if (temp.y > maxY.y && temp.y < 1300)
                        maxY = temp;
                }
            }
          }
     }
     
    tL = CvPoint(minX.x, maxY.y);
    tR = CvPoint(maxX.x, maxY.y);
    bL = CvPoint(minX.x, minY.y);
    bR = CvPoint(maxX.x, minY.y);
    length = maxX.x - minX.x;
}

void drawLine(Vec2f line, Mat &img, Scalar rgb = CV_RGB(0,0,255))
{
    if(line[1]!=0)
    {
        float m = -1/tan(line[1]);

        float c = line[0]/sin(line[1]);

        cv::line(img, Point(0, c), Point(img.size().width, m*img.size().width+c), rgb);
    }
    else
    {
        cv::line(img, Point(line[0], 0), Point(line[0], img.size().height), rgb);
    }

}

void mergeRelatedLines(vector<Vec2f> *lines, Mat &img)
{
    vector<Vec2f>::iterator current;
    for(current=lines->begin();current!=lines->end();current++)
    {
        if((*current)[0]==0 && (*current)[1]==-100) continue;
        float p1 = (*current)[0];
        float theta1 = (*current)[1];
        
        Point pt1current, pt2current;
        if(theta1>CV_PI*45/180 && theta1<CV_PI*135/180)
        {
            pt1current.x=0;
            pt1current.y = p1/sin(theta1);
            pt2current.x=img.size().width;
            pt2current.y=-pt2current.x/tan(theta1) + p1/sin(theta1);
        }
        else
        {
            pt1current.y=0;

            pt1current.x=p1/cos(theta1);

            pt2current.y=img.size().height;
            pt2current.x=-pt2current.y/tan(theta1) + p1/cos(theta1);

        }
        
        vector<Vec2f>::iterator    pos;
        for(pos=lines->begin();pos!=lines->end();pos++)
        {
            if(*current==*pos) continue;

               if(fabs((*pos)[0]-(*current)[0])<20 && fabs((*pos)[1]-(*current)[1])<CV_PI*10/180)
            {
                float p = (*pos)[0];
                float theta = (*pos)[1];
                
                Point pt1, pt2;
                if((*pos)[1]>CV_PI*45/180 && (*pos)[1]<CV_PI*135/180)
                {
                    pt1.x=0;
                    pt1.y = p/sin(theta);
                    pt2.x=img.size().width;
                    pt2.y=-pt2.x/tan(theta) + p/sin(theta);
                }
                else
                {
                    pt1.y=0;
                    pt1.x=p/cos(theta);
                    pt2.y=img.size().height;
                    pt2.x=-pt2.y/tan(theta) + p/cos(theta);
                }
                
                if(((double)(pt1.x-pt1current.x)*(pt1.x-pt1current.x) + (pt1.y-pt1current.y)*(pt1.y-pt1current.y)<64*64) &&
((double)(pt2.x-pt2current.x)*(pt2.x-pt2current.x) + (pt2.y-pt2current.y)*(pt2.y-pt2current.y)<64*64))
                {
                    (*current)[0] = ((*current)[0]+(*pos)[0])/2;

                    (*current)[1] = ((*current)[1]+(*pos)[1])/2;

                    (*pos)[0]=0;
                    (*pos)[1]=-100;
                }
                
            }
        }
    }
}

String inttostr(int input)
{
       stringstream ss;
       ss << input;
       return ss.str();
}

int main()
{   
    Mat sudoku = imread("Materialy/Zdjecia/Najlepsza/Scan/sudoku4.jpg", 0);
    Mat zrodlo = imread("Materialy/Zdjecia/Najlepsza/Scan/sudoku4.jpg", 1 );
    Mat src_gray;
    cvtColor( zrodlo, src_gray, CV_BGR2GRAY );
   
    Mat outerBox = Mat(sudoku.size(), CV_8UC1);
    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
    GaussianBlur(sudoku, sudoku, Size(11, 11), 0, 0);
    adaptiveThreshold(sudoku, outerBox, 255, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV, 5, 2);
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
    
    vector<Vec2f> lines;
    HoughLines(outerBox, lines, 1, CV_PI/180,  300, 0, 0 );

    mergeRelatedLines(&lines, sudoku);

    Vec2f topEdge = Vec2f(1000,1000);    double topYIntercept=100000, topXIntercept=0;
    Vec2f bottomEdge = Vec2f(-1000,-1000);        double bottomYIntercept=0, bottomXIntercept=0;
    Vec2f leftEdge = Vec2f(1000,1000);    double leftXIntercept=100000, leftYIntercept=0;
    Vec2f rightEdge = Vec2f(-1000,-1000);        double rightXIntercept=0, rightYIntercept=0;

    for(int i=0;i<lines.size();i++)
    {
        Vec2f current = lines[i];

        float p=current[0];

        float theta=current[1];

        if(p==0 && theta==-100)
            continue;
    
        double xIntercept, yIntercept;
        xIntercept = p/cos(theta);
        yIntercept = p/(cos(theta)*sin(theta));
        
        if(theta>CV_PI*80/180 && theta<CV_PI*100/180)
        {
            if(p<topEdge[0])
                topEdge = current;

            if(p>bottomEdge[0])
                bottomEdge = current;
        }
    
     else if(theta<CV_PI*10/180 || theta>CV_PI*170/180)
        {
            if(xIntercept>rightXIntercept)
            {
                rightEdge = current;
                rightXIntercept = xIntercept;
            }
            else if(xIntercept<=leftXIntercept)
            {
                leftEdge = current;
                leftXIntercept = xIntercept;
            }
        }
    }
    
    drawLine(topEdge, sudoku, CV_RGB(0,0,0));
    drawLine(bottomEdge, sudoku, CV_RGB(0,0,0));
    drawLine(leftEdge, sudoku, CV_RGB(0,0,0));
    drawLine(rightEdge, sudoku, CV_RGB(0,0,0));

    Point left1, left2, right1, right2, bottom1, bottom2, top1, top2;

    int height=outerBox.size().height;
    int width=outerBox.size().width;

    if(leftEdge[1]!=0)
    {
        left1.x=0;        left1.y=leftEdge[0]/sin(leftEdge[1]);
        left2.x=width;    left2.y=-left2.x/tan(leftEdge[1]) + left1.y;
    }
    else
    {
        left1.y=0;        left1.x=leftEdge[0]/cos(leftEdge[1]);
        left2.y=height;    left2.x=left1.x - height*tan(leftEdge[1]);
    }

    if(rightEdge[1]!=0)
    {
        right1.x=0;        right1.y=rightEdge[0]/sin(rightEdge[1]);
        right2.x=width;    right2.y=-right2.x/tan(rightEdge[1]) + right1.y;
    }
    else
    {
        right1.y=0;        right1.x=rightEdge[0]/cos(rightEdge[1]);
        right2.y=height;    right2.x=right1.x - height*tan(rightEdge[1]);
    }

    bottom1.x=0;    bottom1.y=bottomEdge[0]/sin(bottomEdge[1]);
    bottom2.x=width;bottom2.y=-bottom2.x/tan(bottomEdge[1]) + bottom1.y;

    top1.x=0;        top1.y=topEdge[0]/sin(topEdge[1]);
    top2.x=width;    top2.y=-top2.x/tan(topEdge[1]) + top1.y;
        
    double leftA = left2.y-left1.y;
    double leftB = left1.x-left2.x;

    double leftC = leftA*left1.x + leftB*left1.y;

    double rightA = right2.y-right1.y;
    double rightB = right1.x-right2.x;

    double rightC = rightA*right1.x + rightB*right1.y;

    double topA = top2.y-top1.y;
    double topB = top1.x-top2.x;

    double topC = topA*top1.x + topB*top1.y;

    double bottomA = bottom2.y-bottom1.y;
    double bottomB = bottom1.x-bottom2.x;

    double bottomC = bottomA*bottom1.x + bottomB*bottom1.y;

    double detTopLeft = leftA*topB - leftB*topA;

    CvPoint ptTopLeft = cvPoint((topB*leftC - leftB*topC)/detTopLeft, (leftA*topC - topA*leftC)/detTopLeft);

    double detTopRight = rightA*topB - rightB*topA;

    CvPoint ptTopRight = cvPoint((topB*rightC-rightB*topC)/detTopRight, (rightA*topC-topA*rightC)/detTopRight);

    double detBottomRight = rightA*bottomB - rightB*bottomA;
    CvPoint ptBottomRight = cvPoint((bottomB*rightC-rightB*bottomC)/detBottomRight, (rightA*bottomC-bottomA*rightC)/detBottomRight);// Intersection of bottom and left
    double detBottomLeft = leftA*bottomB-leftB*bottomA;
    CvPoint ptBottomLeft = cvPoint((bottomB*leftC-leftB*bottomC)/detBottomLeft, (leftA*bottomC-bottomA*leftC)/detBottomLeft);
    
    int maxLength = (ptBottomLeft.x-ptBottomRight.x)*(ptBottomLeft.x-ptBottomRight.x) + (ptBottomLeft.y-ptBottomRight.y)*(ptBottomLeft.y-ptBottomRight.y);
    int temp = (ptTopRight.x-ptBottomRight.x)*(ptTopRight.x-ptBottomRight.x) + (ptTopRight.y-ptBottomRight.y)*(ptTopRight.y-ptBottomRight.y);

    if(temp>maxLength) maxLength = temp;

    temp = (ptTopRight.x-ptTopLeft.x)*(ptTopRight.x-ptTopLeft.x) + (ptTopRight.y-ptTopLeft.y)*(ptTopRight.y-ptTopLeft.y);

    if(temp>maxLength) maxLength = temp;

    temp = (ptBottomLeft.x-ptTopLeft.x)*(ptBottomLeft.x-ptTopLeft.x) + (ptBottomLeft.y-ptTopLeft.y)*(ptBottomLeft.y-ptTopLeft.y);

    if(temp>maxLength) maxLength = temp;

    maxLength = sqrt((double)maxLength);
    
    cornerHarris_demo( 0, 0, zrodlo, src_gray );

    Point2f src[4], dst[4];
    
    if((tR.x - ptTopRight.x) > 10 ||  (ptTopRight.x - tR.x) > 10) {
        length = maxLength;
        
        src[3] = ptBottomLeft;  
        src[2] = ptBottomRight; 
        src[1] = ptTopRight;
        src[0] = ptTopLeft; 
        //cout<<"LINIE";
    }
    else {
        length = (length + maxLength)/2;
        src[0] = bL;
        src[1] = bR;
        src[2] = tR;
        src[3] = tL;
        //cout<<"ROGI";
    }
    
    dst[0] = Point2f(0,0);
    dst[1] = Point2f(length-1, 0);
    dst[2] = Point2f(length-1, length-1);
    dst[3] = Point2f(0, length-1);
    
    Mat undistorted = Mat(Size(maxLength, maxLength), CV_8UC1);

    cv::warpPerspective(sudoku, undistorted, cv::getPerspectiveTransform(src, dst), Size(maxLength, maxLength));

    Mat undistortedThreshed = undistorted.clone();
    adaptiveThreshold(undistorted, undistortedThreshed, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101, 1);
    
    int dist = ceil((double)length/9)-1;    
    Mat currentCell = Mat(dist , dist, CV_8UC1);
    
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);
    int photocount = 0;
    String imagename;
     
    for(int j=0;j<9;j++) {
       
       for(int i=0;i<9;i++) {
           for(int y=0;y<dist && j*dist+y<undistortedThreshed.cols;y++)
           {
               uchar* ptr = currentCell.ptr(y);
               for(int x=0;x<dist && i*dist+x<undistortedThreshed.rows;x++)
               {
                 ptr[x] = undistortedThreshed.at<uchar>(j*dist+y, i*dist+x);
               }
           }
           
           Moments m = cv::moments(currentCell, true);
           int area = m.m01;
           if(area > currentCell.rows*currentCell.cols/5)
           {
                photocount++;
                imagename = "digits/digit" + inttostr(photocount) + ".jpg"; //sciezka do zapisu pliku
                    
                for(int k=currentCell.rows-13; k<currentCell.rows; k++)
                    floodFill(currentCell, Point(k,k), CV_RGB(0,0,0));
                for(int k=currentCell.cols-13; k<currentCell.cols; k++)
                    floodFill(currentCell, Point(k,k), CV_RGB(0,0,0));
                for(int k=0; k<currentCell.rows-(currentCell.rows-14); k++)
                    floodFill(currentCell, Point(k,k), CV_RGB(0,0,0));
                for(int k=0; k<currentCell.cols-(currentCell.cols-14);k++)
                    floodFill(currentCell, Point(k,k), CV_RGB(0,0,0));
        
                imwrite(imagename, currentCell, compression_params);
                    
           }
        }      
    }
    
    imshow("thresholded", undistortedThreshed);
    waitKey(0);
    return 0;
}