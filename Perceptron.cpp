#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

const int num = 10;//���ݼ���С�����ƣ�
int count = 3;//���ݼ���С��ʵ�ʣ�
bool flag = true;//�Ƿ������

struct DataSet
{
	double x1;
	double x2;
	int y;
}data[num];

double eta = 0.5;//ѧϰ��
double w[2] = { 0.0, 0.0 }, b = 0.0;//�������

//���ļ��ж�ȡ����
void readData()
{
	data[0] = { 3, 3, 1 };
	data[1] = { 4, 3, 1 };
	data[2] = { 1, 1, -1 };
	data[3] = { 2, 2, -1 };
}

/*int main()
{
	clock_t start, end;
	int i;
	int n = 0;//��������
	readData();//��������
	int count = 4;
	//������ݼ�
	cout << "���ݼ�Ϊ��" << endl;
	for (i = 0; i < count; i++)
	{
		cout << data[i].x1 << "  " << data[i].x2 << "  " << data[i].y << endl;
	}
	start = clock();
	while (flag)
	{
		for (i = 0; i < count; i++)
		{
			flag = false;
			if (data[i].y * (w[0] * data[i].x1 + w[1] * data[i].x2 + b) <= 0)
			{
				flag = true;
				w[0] = w[0] + eta * data[i].y * data[i].x1;
				w[1] = w[1] + eta * data[i].y * data[i].x2;
				b = b + eta * data[i].y;
				n++;
				cout << "����������" << n << endl;
				cout << "w = " << w[0] << ", " << w[1] << " " << "b=" << b << endl;
				break;
			}
		}
	}
	end = clock();
	cout << endl << "�����" << endl;
	cout << "w = " << w[0] << ", " << w[1] << " " << "b=" << b << endl;
	cout << "����������" << n << endl;
	cout <<"����ʱ�䣺"<< (end - start) / CLOCKS_PER_SEC << "(s)" << endl;
	system("pause");

	return 0;
}*/