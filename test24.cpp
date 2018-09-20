
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;
int test24(int argc, char *argv[])
{
	int classlabel = 17;

	/*string  labelpath = "I:/双个车牌放在一起/左右-plate_left_right_las17/0_text.txt";
	string imagepath = "I:/双个车牌放在一起/左右-plate_left_right_las17/0_all";
	string  labelalltxt = "I:/双个车牌放在一起/左右-plate_left_right_las17/0_all/0_one.txt";*/

	string  labelpath = "I:/双个车牌放在一起/左右-double_plate_lr/0_text.txt";
	string imagepath = "I:/双个车牌放在一起/左右-double_plate_lr/0_all";
	string  labelalltxt = "I:/双个车牌放在一起/左右-double_plate_lr/0_all/0_one.txt";

	fstream finRead;
	finRead.open(labelpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	fstream fin1Write;
	fin1Write.open(labelalltxt, ios::out);
	if (!fin1Write.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	
	string line; int num = 0;
	while (getline(finRead, line))
	{
		num++;
		if (line.empty())
		{
			break;
		}
		fstream fin1;
		fin1.open(line);
		cout << line.c_str() << endl;
		if (!fin1.is_open())
		{
			cout << "error" << endl;
			cout << line.c_str() << endl;
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		string line1;
		while (getline(fin1, line1))
		{
			int label; float cenx;  float ceny; float cenw; float cenh;
			stringstream str_s(line1);
			str_s >> label >> cenx >> ceny >> cenw >> cenh;
			if (label == classlabel)
			{
				string temp = line;
				temp.replace(line.find_last_of("."), 4, ".jpg");
				int npos = line.find_last_of('\\');
				int npos2 = line.find_last_of('.');
				//string name1 = line.substr(npos + 1, npos2 - npos - 1);
				Mat img = imread(temp.c_str());

				/*Rect rt; rt.x = (cenx - cenw / 2)*img.cols; rt.y = (ceny - cenh / 2)*img.rows;
				rt.width = cenw*img.cols; rt.height = cenh*img.rows;
				Mat srcROI(img,rt);
				string path12 = imagepath + name1+ ".jpg";
				imwrite(path12.c_str(), srcROI);*/
				char file[25];
				sprintf(file,"%04d",num);
				string path12 = imagepath+"/"+ file + ".jpg";
				imwrite(path12.c_str(), img);

				string  labeltxt = imagepath + "/" + file+".txt";

				fstream finWrite;
				finWrite.open(labeltxt, ios::out);
				if (!finWrite.is_open())
				{
					cout << "finRead 文件数据打开错误！" << endl;
					system("pause");
					return false;
				}

				int x1, y1, x2, y2;
				x1 = (cenx - cenw / 2)*img.cols;
				y1 = (ceny - cenh / 2)*img.rows;
				x2 = (cenx + cenw / 2)*img.cols;
				y2 = (ceny +cenh / 2)*img.rows;
				finWrite << "4" << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
				finWrite.close();

				fin1Write << path12 << " " << "4" << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;


			}
		}
		fin1.close();
	}

	finRead.close();
	fin1Write.close();

	return 0;
}
