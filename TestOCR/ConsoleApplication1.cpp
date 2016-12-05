#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/objdetect/objdetect.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/video/tracking.hpp" 
#include <opencv2/ml.hpp>

using namespace cv;
using namespace std;

int mouse_x = 0, mouse_y = 0;        //Pozycja myszki 
bool draw;                            //Zezwolenie na rysowanie ( gdy lewy klawisz myszy wcisniêty ) 
int img_x = 16, img_y = 16;            //Rozmiary danych trenujacych 
int img_size = img_x * img_y;        //Rozmiary wektora trenujacego 

String inttostr(int input)
{
	stringstream ss;
	ss << input;
	return ss.str();
}


void image_to_vector(Mat & vector, const Mat & img, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			vector.at<float>(0, i * rows + j) = img.at<uchar>(i, j) / 255.0;
		}
	}
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
	mouse_x = x;
	mouse_y = y;
	if (flags == CV_EVENT_FLAG_LBUTTON) draw = true;
	else draw = false;
}

void vector_to_image(const Mat & vector, Mat & img, int rows, int cols, unsigned index)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			img.at<uchar>(i, j) = 255 * uchar(vector.at<float>(index, i * rows + j));
		}
	}
}

int main()
{
	int tab[81];
	const string window_name = "Wczytywanie bazy danych, czekaj...";
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	Mat loading = Mat::zeros(Size(400, 100), CV_8UC3);
	putText(loading, "Baza danych wczytana poprawnie", Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(120, 40, 80), 1, 8);
	imshow(window_name, loading);

	/*Fragment odpowiadajacy ze wczytanie bazy danych z pliku*/
	const string file_name = "semeion.data";
	std::fstream file;
	file.open(file_name.c_str(), ios::in);

	if (!file.good())
	{
		cout << "Nie odnaleziono pliku " << file_name.c_str() << ".";
		return -1;
	}
	Mat trainingvector(1, img_size, CV_32FC1);
	Mat traininglabels(1, 1, CV_32FC1);
	float buf;
	unsigned char label_catch;
	float label;
	size_t index = -1;
	while (!file.eof())
	{
		index++;
		if (index != 0)
		{

			traininglabels.resize(index + 1);
			trainingvector.resize(index + 1);
		}
		for (int i = 0; i < img_size; i++)
		{
			file >> buf;
			trainingvector.at<float>(index, i) = buf;
		}
		for (int i = 0; i < 10; i++)
		{
			file >> label_catch;
			if (label_catch == '1') label = float(i);
		}
		traininglabels.at<float>(index, 0) = label;
	}
	traininglabels.resize(index);    //Obciêcie pustego wiersza 
	trainingvector.resize(index);    //który pojawia siê ze wzglêdu na konstrukcjê pêtli 
									 /*Koniec wczytywania danych*/

	for (int i = 40; i < 50; i++)
	{
		Mat test(img_x, img_y, CV_8UC1);
		vector_to_image(trainingvector, test, img_x, img_y, i);
		imshow(window_name, test);
		string s;
		stringstream out;
		out << i;
		s = out.str();
		s += ".jpg";
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
		imwrite(s.c_str(), test, compression_params);
		waitKey();
	}

	/*Trenowanie klasyfikatora*/
	Ptr<ml::TrainData> traindata = ml::TrainData::create(trainingvector, 0, traininglabels);
	cv::Ptr<cv::ml::KNearest> KN = cv::ml::KNearest::create();
	KN->train(traindata);
	cout << "Max. k = " << KN->getDefaultK() << endl;

	const string window_name2 = "Narysuj myszka liczbe ( 0-9 ) jednym pociagnieciem. ESC - koniec ";
	namedWindow(window_name2, CV_WINDOW_AUTOSIZE);
	setMouseCallback(window_name2, my_mouse_callback);

	/*Pêtla g³ówna*/
	while (1)
	{
		/*Mat canvas = Mat::zeros(Size(600, 600), CV_8UC3);
		bool start = false;

		Pêtla rysuj¹ca liczbê
		while (waitKey(1))
		{
		if (draw)
		{
		circle(canvas, Point(mouse_x, mouse_y), 2, Scalar(255, 255, 255), 30, 8);
		start = true;
		}
		else if (start) break;
		imshow(window_name2, canvas);
		}*/

		for (int i = 1; i < 82; i++) {
			Mat src = Mat::zeros(Size(600, 600), CV_8UC3);
			src = imread("C:\\Users\\kriscool\\Desktop\\Lepsza\\" + inttostr(i) + ".png", 1);
			/*Fragment odpowiadaj¹cy z wykrycie konturu i obrysu narysowanej liczby*/
			vector<vector<Point> > contours;
			vector<Point> contours_poly;
			Rect boundRect, newRect;
			Mat cont, img_gary;
			Mat digit;
			cvtColor(src, cont, CV_BGR2GRAY);
			cvtColor(src, img_gary, CV_BGR2GRAY);
			findContours(cont, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
			for (unsigned i = 0; i < contours.size(); i++)
			{
				drawContours(src, contours, i, Scalar(125, 125, 250), 2);
			}
			approxPolyDP(Mat(contours[0]), contours_poly, 3, true);
			boundRect = boundingRect(Mat(contours_poly));
			rectangle(src, boundRect.tl(), boundRect.br(), Scalar(125, 250, 125), 2, 8, 0);

			/*Przeskalowanie liczby do rozmiarów danych ucz¹cych*/
			digit = img_gary(boundRect);
			resize(digit, digit, Size(img_x, img_y), 1.0, 1.0, INTER_CUBIC);
			threshold(digit, digit, 1, 255, CV_THRESH_BINARY);
			Mat testvector(1, img_size, CV_32FC1);
			Mat predictedlabels(1, 1, CV_32FC1);

			/*Przetworzenie obrazka na wektor*/
			image_to_vector(testvector, digit, img_x, img_y);

			/*Klasyfikacja wprowadzonej liczby*/
			KN->findNearest(testvector, KN->getDefaultK(), predictedlabels);

			/*Wyswietlenie odpowiedzi*/
			string s;
			tab[i] = atoi(s.c_str());
			if (waitKey() == 2) break;
		}
	}

	for (int i = 0; i < 81; i++) {
		printf("%d", tab[i]);
	}
	file.close();
	return 0;
}

