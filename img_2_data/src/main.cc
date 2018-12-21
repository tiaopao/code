#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: img_2_data <image path>" << endl;
        return -1;
    }

    char *imgName = argv[1];
    Mat image;

    image = imread(imgName, 0); // 0: gray, 1:origin
    if (!image.data)
    {
        cout << "No image data" << endl;
        return -1;
    }

    imshow("gray", image);
    Mat gray_img;

    cout << "rows:" << image.rows<< ", cols:" << image.cols
         << ", channels:" << image.channels() << endl;
    // data binay
    unsigned char *ptr = image.data;
    for(int i=0; i<image.rows; i++)
    {
        for(int j=0; j<image.cols; j++)
        {
            *ptr = ((*ptr) <= 1) ? 1 : 0;
            cout << (int)(*ptr) << ",";
            ptr++;
        }
        cout << endl;
    }
    cout << endl;
    // data code
    ptr = image.data;
    for(int i=0; i<image.rows; i++)
    {
        uchar code = 0;
        for(int j=0; j<image.cols; j++)
        {
            if(j < 24)
            {
                int mod = j%8;

                if((*ptr) == 1) code |= (1 << (7-mod));

                if(mod == 7)
                {
                    //cout << showbase << setw(4) << hex << (int)code << ",";
                    printf("0x%02x,", (int)code);
                    code = 0;
                }
            }
            ptr++;
        }
        cout << endl;
    }


    // cvtColor(image, gray_img, CV_BGR2GRAY);
    // //imwrite("images/result.jpg", gray_img);
    // imshow("gray", gray_img);


    waitKey(0);
    return 0;
}

