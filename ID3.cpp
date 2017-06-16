#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


const unsigned att_num = 3;
const unsigned rule_num = 14;
string decision_tree_name("Play Golf ?");
string attribute_names[] = { "Outlook", "Humidity", "Windy" };
string attribute_values[] = { "Sunny", "Overcast", "Rainy", "> 75", "<= 75", "True", "False", "Yes", "No" };
//ѵ�������һ��Ϊ�����ǩ������������Ϊ��������1
unsigned train_data[rule_num][att_num + 1] = {
	{ 0, 3, 6, 8 }, { 0, 3, 5, 8 }, { 1, 3, 6, 7 },
	{ 2, 3, 6, 7 }, { 2, 3, 6, 7 }, { 2, 4, 5, 8 },
	{ 1, 4, 5, 7 }, { 0, 3, 6, 8 }, { 0, 4, 6, 7 },
	{ 2, 3, 6, 7 }, { 0, 4, 5, 7 }, { 1, 3, 5, 7 },
	{ 1, 4, 6, 7 }, { 2, 3, 5, 8 }
};




/*************************************************
Function:       unique()
Description:    ��vector���ظ�Ԫ�غϲ���ֻ����һ��
Calls:          ��
Input:          vector
Output:         vector
*************************************************/
template <typename T>
vector<T> unique(vector<T> vals)
{
	vector<T> unique_vals;
	vector<T>::iterator itr;
	vector<T>::iterator subitr;

	int flag = 0;
	while (!vals.empty())
	{
		unique_vals.push_back(vals[0]);
		itr = vals.begin();
		subitr = unique_vals.begin() + flag;
		while (itr != vals.end())
		{
			if (*subitr == *itr)
				itr = vals.erase(itr);
			else
				itr++;
		}
		flag++;
	}
	return unique_vals;
}

/*************************************************
Function:       log2()
Description:    ����һ����ֵ����2Ϊ�׵Ķ���
Calls:          ��
Input:          double
Output:         double
*************************************************/

double log2(double n)
{
	return log10(n) / log10(2.0);
}

/*************************************************
Function:       compute_entropy()
Description:    �������Ե�ȡֵ����������Ե���
Calls:          unique(),log2(),count(),����count()
��STL��algorithm����
Input:          vector<unsigned>
Output:         double
*************************************************/
double compute_entropy(vector<unsigned> v)
{
	vector<unsigned> unique_v;
	unique_v = unique(v);

	vector<unsigned>::iterator itr;
	itr = unique_v.begin();

	double entropy = 0.0;
	auto total = v.size();
	while (itr != unique_v.end())
	{
		double cnt = count(v.begin(), v.end(), *itr);
		entropy -= cnt / total * log2(cnt / total);
		itr++;
	}
	return entropy;
}

/*************************************************
Function:       compute_gain()
Description:    �������ݼ����������Ե���Ϣ����
Calls:          compute_entropy(),unique()
Input:          vector<vector<unsigned> >
�൱��һ����ά���飬�洢��ѵ�����ݼ�
Output:         vector<double> �洢���������Ե���Ϣ
����
*************************************************/
vector<double> compute_gain(vector<vector<unsigned> > truths)
{
	vector<double> gain(truths[0].size() - 1, 0);//��ȥ���һ��
	vector<unsigned> attribute_vals;
	vector<unsigned> labels;
	for (unsigned j = 0; j < truths.size(); j++)
	{
		labels.push_back(truths[j].back());
	}

	for (unsigned i = 0; i < truths[0].size() - 1; i++)//���һ��������ǩ��û��Ҫ������Ϣ����
	{
		for (unsigned j = 0; j < truths.size(); j++)
			attribute_vals.push_back(truths[j][i]);

		vector<unsigned> unique_vals = unique(attribute_vals);//��������ȡֵ��һ��
		vector<unsigned>::iterator itr = unique_vals.begin();
		vector<unsigned> subset;
		while (itr != unique_vals.end())
		{
			for (unsigned k = 0; k < truths.size(); k++)
			{
				if (*itr == attribute_vals[k])
				{
					subset.push_back(truths[k].back());
				}
			}
			double A = (double)subset.size();
			gain[i] += A / truths.size() * compute_entropy(subset);
			itr++;
			subset.clear();
		}
		gain[i] = compute_entropy(labels) - gain[i];
		attribute_vals.clear();
	}
	return gain;
}

/*************************************************
Function:       compute_gain_ratio()
Description:    �������ݼ����������Ե���Ϣ�����
C4.5�㷨���õ�
Calls:          compute_gain();compute_entropy()
Input:          ѵ�����ݼ�
Output:         ��Ϣ�����
*************************************************/
vector<double> compute_gain_ratio(vector<vector<unsigned> > truths)
{
	vector<double> gain = compute_gain(truths);
	vector<double> entropies;
	vector<double> gain_ratio;

	for (unsigned i = 0; i < truths[0].size() - 1; i++)//���һ��������ǩ��û��Ҫ������Ϣ�����
	{
		vector<unsigned> attribute_vals(truths.size(), 0);
		for (unsigned j = 0; j < truths.size(); j++)//ÿһ������ֵ
		{
			attribute_vals[j] = truths[j][i];
		}
		double current_entropy = compute_entropy(attribute_vals);
		if (current_entropy)
		{
			gain_ratio.push_back(gain[i] / current_entropy);
		}
		else
			gain_ratio.push_back(0.0);

	}
	return gain_ratio;
}

/*************************************************
Function:       find_most_common_label()
Description:    �ҳ����ݼ�����������ǩ

Calls:          count();
Input:          ���ݼ�
Output:         ����ǩ
*************************************************/
template <typename T>
T find_most_common_label(vector<vector<T> > data)
{
	vector<T> labels;
	for (unsigned i = 0; i < data.size(); i++)
	{
		labels.push_back(data[i].back());
	}
	vector<T>::iterator itr = labels.begin();
	T most_common_label;
	unsigned most_counter = 0;
	while (itr != labels.end())
	{
		unsigned current_counter = count(labels.begin(), labels.end(), *itr);
		if (current_counter > most_counter)
		{
			most_common_label = *itr;
			most_counter = current_counter;
		}
		itr++;
	}
	return most_common_label;
}

/*************************************************
Function:       find_attribute_values()
Description:    �������ԣ��ҳ������Կ��ܵ�ȡֵ

Calls:          unique();
Input:          ���ԣ����ݼ�
Output:         �������п��ܵ�ȡֵ(���ظ�)
*************************************************/
template <typename T>
vector<T> find_attribute_values(T attribute, vector<vector<T> > data)
{
	vector<T> values;
	for (unsigned i = 0; i < data.size(); i++)
	{
		values.push_back(data[i][attribute]);
	}
	return unique(values);
}

/*************************************************
Function:       drop_one_attribute()
Description:    �ڹ����������Ĺ����У����ĳһ�����Ѿ��������
��ô�ʹ����ݼ���ȥ����һ���ԣ��˴�������������
�ϵ�ȥ�������ǽ����ǹ�������ȫ�����Ϊ110����
Ȼ�������������֣�ֻҪ�ܺ�ԭ��ѵ�����е�������
������������
Calls:          unique();
Input:          ���ԣ����ݼ�
Output:         �������п��ܵ�ȡֵ(���ظ�)
*************************************************/
template <typename T>
vector<vector<T> > drop_one_attribute(T attribute, vector<vector<T> > data)
{
	vector<vector<T> > new_data(data.size(), vector<T>(data[0].size() - 1, 0));
	for (unsigned i = 0; i < data.size(); i++)
	{
		data[i][attribute] = 110;
	}
	return data;
}


struct Tree{
	unsigned root;//�ڵ�����ֵ
	vector<unsigned> branches;//�ڵ����ȡֵ
	vector<Tree> children; //���ӽڵ�
};

/*************************************************
Function:       build_decision_tree()
Description:    �ݹ鹹��������

Calls:          unique()��count(),
find_most_common_label()
compute_gain()(ID3),
compute_gain_ratio()(C4.5),
find_attribute_values(),
drop_one_attribute(),
build_decision_tree()(�ݹ飬
��ȻҪ���ú�������)
Input:          ѵ�����ݼ���һ���վ�����
Output:         ��
*************************************************/
void build_decision_tree(vector<vector<unsigned> > examples, Tree &tree)
{
	//��һ�����ж�����ʵ���Ƿ�����ͬһ�࣬����ǣ���������ǵ��ڵ�
	vector<unsigned> labels(examples.size(), 0);
	for (unsigned i = 0; i < examples.size(); i++)
	{
		labels[i] = examples[i].back();
	}
	if (unique(labels).size() == 1)
	{
		tree.root = labels[0];
		return;
	}

	//�ڶ������ж��Ƿ���ʣ�������û�п��ǣ�����������Զ��Ѿ����ǹ��ˣ�
	//��ô��ʱ��������Ϊ0����ѵ�����������������Ϊ�ýڵ�������
	if (count(examples[0].begin(), examples[0].end(), 110) == examples[0].size() - 1)//ֻʣ��һ�������
	{
		tree.root = find_most_common_label(examples);
		return;
	}
	//������:�������������������ж�ʧ�ܺ󣬼�����Ϣ���棬ѡ����Ϣ�������
	//��������Ϊ���ڵ�,���ҳ��ýڵ������ȡֵ

	vector<double> standard = compute_gain(examples);

	//Ҫ�ǲ���C4.5��������һ��ע�͵���������һ�е�ע��ȥ������
	//vector<double> standard = compute_gain_ratio(examples);
	tree.root = 0;
	for (unsigned i = 0; i < standard.size(); i++)
	{
		if (standard[i] >= standard[tree.root] && examples[0][i] != 110)
			tree.root = i;
	}


	tree.branches = find_attribute_values(tree.root, examples);
	//���Ĳ�:���ݽڵ��ȡֵ����examples�ֳ������Ӽ�
	vector<vector<unsigned> > new_examples = drop_one_attribute(tree.root, examples);
	vector<vector<unsigned> > subset;
	for (unsigned i = 0; i < tree.branches.size(); i++)
	{
		for (unsigned j = 0; j < examples.size(); j++)
		{
			for (unsigned k = 0; k < examples[0].size(); k++)
			{
				if (tree.branches[i] == examples[j][k])
					subset.push_back(new_examples[j]);
			}
		}
		// ���岽:��ÿһ���Ӽ��ݹ����build_decision_tree()����
		Tree new_tree;
		build_decision_tree(subset, new_tree);
		tree.children.push_back(new_tree);
		subset.clear();
	}
}

/*************************************************
Function:       print_tree()
Description:    �ӵڸ��ڵ㿪ʼ����㽫�������������
����ʾ

Calls:          print_tree();
Input:          ������������
Output:         ��
*************************************************/
void print_tree(Tree tree, unsigned depth)
{
	for (unsigned d = 0; d < depth; d++) cout << "\t";
	if (!tree.branches.empty()) //����Ҷ�ӽڵ�
	{
		cout << attribute_names[tree.root] << endl;

		for (unsigned i = 0; i < tree.branches.size(); i++)
		{
			for (unsigned d = 0; d < depth + 1; d++) cout << "\t";
			cout << attribute_values[tree.branches[i]] << endl;
			print_tree(tree.children[i], depth + 2);
		}
	}
	else //��Ҷ�ӽڵ�
	{
		cout << attribute_values[tree.root] << endl;
	}

}


/*int main()
{
	vector<vector<unsigned> > rules(rule_num, vector<unsigned>(att_num + 1, 0));
	for (unsigned i = 0; i < rule_num; i++)
	{
		for (unsigned j = 0; j <= att_num; j++)
			rules[i][j] = train_data[i][j];
	}
	Tree tree;
	build_decision_tree(rules, tree);
	cout << decision_tree_name << endl;
	print_tree(tree, 0);
	system("pause");
	return 0;
}*/