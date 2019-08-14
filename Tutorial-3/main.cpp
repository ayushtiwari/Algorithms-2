#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include<cmath>
#include<limits>

using namespace std;

struct point {
	int x, y;
};

double dist(point A, point B) {
	return sqrt(pow(A.x-B.x, 2) + pow(A.y-B.y, 2));
}

void disp_dist_mat(vector<point> points) {
	cout << "      ";
	for(int i=0; i<points.size(); i++)
		cout << setw(5) << i << "|";
	cout << "\n";
	cout << "      ";
	for(int k=0; k<6*points.size(); k++)
		cout << "-";
	cout << "\n";
	float min = INT_MAX;
	int a=0, b=0;
	for(int i=0; i<points.size(); i++) {
		cout << setw(5) << i << "|";
		for(int j=0; j<i; j++) {
			double sep = dist(points[i], points[j]);
			cout << setw(5) << setprecision(3) << sep << "|";
			if(sep < min) {
				min=sep;
				a=i;
				b=j;
			}
		}
		cout << "\n";
		cout << "      ";
		for(int k=0; k<6*points.size(); k++)
			cout << "-";
		cout << "\n";
	}

	cout << "\n\n";
	cout << "Min Distance : " << min << endl;
	cout << "Points : " << a << " and " << b << endl;
	cout << "\n\n";
}

double findClosestPair(vector<point> points) {

	return 0.0;

}

int main() {

	ifstream file;

	file.open("points.txt", ios::in);

	vector<point> points;

	int n;
	file >> n;

	point p;
	if (file.is_open()) {
    	while(file >> p.x >> p.y)
			points.push_back(p);
    	file.close();
  	}
	cout << "\n\n";
	cout << "Number of Points : " << n << "\n\n";
	cout << "\n\n";
	for(int i=0; i<points.size(); i++)
		cout << setw(3) << i << ")" <<  setw(3) << points[i].x << " " << setw(3) << points[i].y << endl;
	cout << "\n\n";

	disp_dist_mat(points);

	return 0;
}
