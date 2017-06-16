#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>
using namespace std;
double hypothesis(vector<double> &feature, vector<double>&w){
	double sum = 0.0;
	for (int i = 0; i<feature.size(); i++){
		sum += w[i] * feature[i];
	}
	return 1 / (1 + exp(-sum));
}
double cost_fuction(vector<vector<double> > &feature_sample, vector<double> &w, vector<double>&lable){
	double sum = 0.0;
	for (int i = 0; i<lable.size(); i++){
		sum += -lable[i] * log(hypothesis(feature_sample[i], w)) - (1 - lable[i])*log(1 - hypothesis(feature_sample[i], w));
	}
	return sum / lable.size();
}
void logic_regression(vector<vector<double> >&feature_sample, vector<double> &lable, vector<double> &w, double a){
	vector<double> delta_w;
	for (int j = 0; j<feature_sample[0].size(); j++){
		double sum = 0.0;
		for (int i = 0; i<lable.size(); i++){
			sum += (hypothesis(feature_sample[i], w) - lable[i])*feature_sample[i][j];
		}
		delta_w.push_back(sum / lable.size()*a);
	}
	for (int i = 0; i<w.size(); i++){
		w[i] -= delta_w[i];
	}
	cout << cost_fuction(feature_sample, w, lable) << endl;
}
int main(){
	freopen("testSet.txt", "r", stdin);
	int feature_num, training_num, t;
	double a;
	cin >> feature_num >> training_num >> a >> t;
	vector<vector<double> >feature_sample;
	vector<double> tem;
	vector<double> lable;
	vector<double> w;
	double m;
	for (int i = 0; i<training_num; i++){
		tem.clear();
		tem.push_back(1);
		for (int j = 0; j<feature_num; j++){
			cin >> m;
			tem.push_back(m);
		}
		cin >> m;
		lable.push_back(m);
		feature_sample.push_back(tem);
	}
	for (int i = 0; i <= feature_num; i++) w.push_back(0);
	while (t--) logic_regression(feature_sample, lable, w, a);
	for (int i = 0; i <= feature_num; i++) cout << w[i] << " ";
	return 0;
}
