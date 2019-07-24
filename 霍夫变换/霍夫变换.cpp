#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("a.jpg");

	Mat midImage, dstImage;

	imshow("【原始图】", srcImage);

	//转为灰度图并进行图像平滑
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);

	//GaussianBlur(midImage, midImage, Size(9,9), 2, 2);

	//进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);//此中的midImage必须为单通道灰度图

	/*cout << circles.size() << endl;

	for(size_t i = 0; i < circles.size(); i++)
	{
	         cout << circles[i][0] <<' ';
			 cout << circles[i][1] <<' ';
			 cout << circles[i][2] << endl;
	}*/


	//依次在图中绘制出圆
	for(size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		//绘制圆心
		circle(midImage, center, 3, Scalar(0, 255, 0), -1, 8, 0 );

		//绘制圆轮廓
		circle(midImage, center, radius, Scalar(255, 0, 0), 3, 8, 0 );
	}

	imshow("【效果图】", midImage);

	waitKey(0);

	return 0;
}