#include <iostream>
#include <fstream>
#include <algorithm>//for heap
#include <iomanip>//for setw
#include <vector>
#include <string>

using namespace std;
const int MAX = 210;
char H_tree[MAX][MAX];
vector <char> v;
int currentSize = 0;
int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };

void print_rotated(int leaf, int depth);
void print_non_rotated();
void print_H_tree(int leaf, int i, int j, int d, int U, int D, int R, int L);
int H_depth(int n);//H-tree depth
int H_center(int n);//H-tree center
int getdepth(int total);//non-rotated form

void print_rotated(int leaf, int depth)
{
	if (currentSize != 0 && leaf < currentSize)
	{
		print_rotated(2 * leaf + 2, depth + 1); // 오른쪽
		cout << setw(2 * depth) << "" << v[leaf] << endl;
		print_rotated(2 * leaf + 1, depth + 1); // 왼쪽
	}
}

void print_non_rotated()
{
	int dep = getdepth(currentSize);
	int index = 0, n = 0;
	int c_dep = 1;
	int blank = 2 * (pow(2, dep));

	for (int i = 0; i < dep; i++)
	{

		for (int j = 0; j < c_dep; j++)
		{
			if (j == 0)
			{
				blank /= 2;
				cout << setw(blank) << v[index];
				index++;

				if (index == currentSize)
				{
					break;
				}
			}
			else
			{
				blank = (2 * blank);
				cout << setw(blank) << v[index];
				index++;

				if (index == currentSize)
				{
					break;
				}
				blank = (blank + 1) / 2;
			}
		}
		if (n != dep)
		{
			n++;
			c_dep = pow(2, n);
		}

		cout << endl;
	}

}

int getdepth(int total)
{
	int tree_depth = 0;
	int i = 0;

	while (total > 0)
	{
		if ((total < pow(2, i + 1)) && (total >= pow(2, i)))
		{
			tree_depth = i + 1;
			break;
		}
		i++;
	}

	return tree_depth;
}

int H_depth(int n)
{
	return n <= 7 ? 1 : 2 * H_depth(n / 4);
}

int H_center(int n)
{
	return  n <= 1 ? 0 : 2 * H_center(n / 4) + 1;
}

void print_H_tree(int leaf, int i, int j, int d, int U, int D, int R, int L)
{
	if (leaf > currentSize) return;
	H_tree[i][j] = v[leaf-1];
	if (2 * leaf <= currentSize)
	{
		H_tree[i + d * V[L][0]][j + d * V[L][1]] = v[2 * leaf-1];
		print_H_tree(4 * leaf, i + d * (V[L][0] + V[U][0]), j + d * (V[L][1] + V[U][1]), d / 2, D, U, L, R);
		print_H_tree(4 * leaf + 1, i + d * (V[L][0] + V[D][0]), j + d * (V[L][1] + V[D][1]), d / 2, U, D, R, L);
	}
	if (2 * leaf + 1 <= currentSize)
	{
		H_tree[i + d * V[R][0]][j + d * V[R][1]] = v[2 * leaf];
		print_H_tree(4 * leaf + 2, i + d * (V[R][0] + V[D][0]), j + d * (V[R][1] + V[D][1]), d / 2, U, D, R, L);
		print_H_tree(4 * leaf + 3, i + d * (V[R][0] + V[U][0]), j + d * (V[R][1] + V[U][1]), d / 2, D, U, L, R);
	}
}

int main()
{
	string op;
	char ch;
	ifstream ifs;
	ifs.open("input.txt");

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			ifs >> op;
			//v.push_back(op);
			if (op == "INS") 
			{
				ifs >> op;
				ch = op[0];
				v.push_back(ch);
				push_heap(v.begin(), v.end());
				currentSize++;
			}
			else if (op == "DEL")
			{
				pop_heap(v.begin(), v.end());
				v.pop_back();
				currentSize--;
			}
			else if (op == "EOI")
			{
				break;
			}
		}
	}
	ifs.close();

	//for (int i = 0; i < v.size(); i++)
	//{
	//	cout << v[i] << " ";
	//}
	//cout << endl;

	cout << "============ Rotated form ============" << endl;
	print_rotated(0, 1);
	cout << endl;

	cout << "========== Non-Roatated from ==========" << endl;
	print_non_rotated();
	cout << endl;

	cout << "============= H-tree form =============" << endl;
	//cout << H_center(currentSize) << " " << H_depth(currentSize) << endl;
	print_H_tree(1, H_center(currentSize), H_center(currentSize), H_depth(currentSize), 0, 1, 2, 3);
	for (int i = 0; i < 2*H_center(currentSize); i++)
	{
		for (int j = 0; j < currentSize; j++)
		{
			cout << H_tree[i][j] << setw(H_depth(currentSize));
		}
		cout << endl;
	}
}