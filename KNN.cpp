#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
class sample
{
public:
	vector<double> X;//特征
	int label;
	double dis;//其它样本点到该样本的距离
	int result;
};
bool cmp(sample &s1, sample&s2)
{
	return s1.dis < s2.dis;
}
void knn(sample newx, vector<sample> &traindata, vector<sample> &nearestsample)
{
	int m = traindata.size();
	int n = traindata[0].X.size();
	double distance = 0;
	for (int i = 0; i < m; i++)
	{
		distance = 0;
		for (int j = 0; j < n; j++)
		{
			distance += (newx.X[j] - traindata[i].X[j])*(newx.X[j] - traindata[i].X[j]);
		}
		traindata[i].dis = sqrt(distance);//欧氏距离
	}
	sort(traindata.begin(), traindata.end(), cmp);
	int k = nearestsample.size();
	for (int i = 0; i < k; i++)
		nearestsample[i] = traindata[i];
}

int max(int a[], int n)
{
	int maximum = a[0];
	int maxindex = 0;
	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i]>maximum)
		{
			maximum = a[i];
			maxindex = i;
		}
	}
	return maxindex;
}
/*int main()
{
	ifstream indata;
	vector<sample> traindata, testdata;
	sample rowdata;
	double temp;
	int fea = 4;//特征数
	indata.open("C:/Users/Administrator/Documents/Visual Studio 2013/Projects/Project1/traindata.txt");
	while (!indata.eof())
	{
		for (int i = 0; i < fea + 1; i++)
		{
			indata >> temp;
			if (i < fea)
				rowdata.X.push_back(temp);
			else
				rowdata.label = temp;
		}
		traindata.push_back(rowdata);
		rowdata.X.erase(rowdata.X.begin(), rowdata.X.end());
	}
	indata.close();
	indata.open("C:/Users/Administrator/Documents/Visual Studio 2013/Projects/Project1/testdata.txt");
	while (!indata.eof())
	{
		for (int i = 0; i < fea + 1; i++)
		{
			indata >> temp;
			if (i < fea)
				rowdata.X.push_back(temp);
			else
				rowdata.label = temp;
		}
		testdata.push_back(rowdata);
		rowdata.X.erase(rowdata.X.begin(), rowdata.X.end());
	}
	indata.close();
	int N = testdata.size();
	//cout << N << endl;
	vector<sample> nearestsample(5);
	int label[3] = { 0 };
	int resultlabel[3] = { 1, 2, 3 };
	for (int i = 0; i < N; i++)
	{
		knn(testdata[i], traindata, nearestsample);
		label[0] = label[1] = label[2] = 0;
		for (int j = 0; j < 5; j++)
		{
			if (nearestsample[j].label == 1)
				label[0]++;
			else
			{
				if (nearestsample[j].label == 2)
					label[1]++;
				else
					label[2]++;
			}
		}
		testdata[i].result = resultlabel[max(label, 3)];
	}
	int counttrue = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < fea; j++)
		{
			cout << testdata[i].X[j] << "   ";
		}
		cout << testdata[i].label << "     ";
		cout << testdata[i].result;
		cout << endl;
		if (testdata[i].label == testdata[i].result)
			counttrue++;
	}
	cout << "accuracy=" << counttrue / N << endl;
	system("pause");
	return 0;
}*/