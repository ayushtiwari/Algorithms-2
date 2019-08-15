//
//  main.cpp
//  closest_pair
//
//  Created by Ayush Tiwari on 15/08/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

struct point {
    int x, y;

    bool operator<(const point &p) const{
        return ((this->x < p.x) || (this->y < p.y));
    }
};

struct closestPair {
    point first, second;
    double dist;
};

bool pointCompareX(const point &p, const point &q) {
    return p.x < q.x;
}

bool pointCompareY(const point &p, const point &q) {
    return p.y < q.y;
}

vector<point> generatePoints(vector<point>::size_type n) {

    srand(unsigned(time(NULL)));

    set<point> unq_pts;

    while (unq_pts.size()!=n)
        unq_pts.insert({rand()%900, rand()%500});

    return vector<point>(unq_pts.begin(), unq_pts.end());
}

double dist(point p, point q) {
    return sqrt((p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y));
}

closestPair bruteForce(vector<point> points) {

    closestPair cp = {{0, 0}, {0, 0}, numeric_limits<double>::max()};

    for(int i=0; i<points.size(); i++) {
        for(int j=i+1; j<points.size(); j++) {
            double currDist = dist(points[i], points[j]);
            if(currDist < cp.dist) {
                cp.first = points[i];
                cp.second = points[j];
                cp.dist = currDist;
            }
        }
    }

    return cp;
}

closestPair findInStrip(vector<point> strip, closestPair cp) {

    for(int i=0; i<strip.size(); i++) {
        for(int j=i+1; j<strip.size() && (strip[j].y-strip[i].y) < cp.dist; j++) {
            if(dist(strip[j], strip[i]) < cp.dist) {
                cp.first = strip[i];
                cp.second = strip[j];
                cp.dist = dist(strip[j], strip[i]);
            }
        }
    }

    return cp;
}

closestPair findCP(vector<point> sortedX, vector<point> sortedY) {

    if(sortedX.size() <= 3) {
        closestPair cp = bruteForce(sortedX);
        return cp;
    }

    vector<point>::size_type mid = sortedX.size()/2;

    closestPair cpL = findCP(vector<point>(sortedX.begin(), sortedX.begin()+mid), sortedY);
    closestPair cpR = findCP(vector<point>(sortedX.begin()+mid, sortedX.end()), sortedY);

    closestPair cp = (cpL.dist < cpR.dist)? cpL:cpR;

    vector<point> strip;
    for(int i=0; i<sortedY.size(); i++) {
        if(abs(sortedX[mid].x - sortedY[i].x) <= cp.dist)
            strip.push_back(sortedY[i]);
    }

    closestPair cpStrip = findInStrip(strip, cp);

    return (cp.dist < cpStrip.dist)? cp: cpStrip;

}

int main() {

    int n = 25;

    vector<point> points = generatePoints(n);

    // ifstream file;
    // file.open("pairs.txt");
    //
    // point p;
    // while(file >> p.x >> p.y) {
    //     points.push_back(p);
    // }
    //
    // file.close();

    vector<point> sortedX(points.begin(), points.end());
    vector<point> sortedY(points.begin(), points.end());

    sort(sortedX.begin(), sortedX.end(), pointCompareX);
    sort(sortedY.begin(), sortedY.end(), pointCompareY);

    for(int i=0; i<points.size(); i++) {
        cout << setw(2) << i << " : " << "(" << setw(3) << sortedX[i].x << "," << setw(3) << sortedX[i].y << ")" << endl;
    }

    closestPair cp = bruteForce(points);

    cout << endl;
	cout << "O(n^2) Answer : " << "\n\n";
    cout << cp.first.x << " " << cp.first.y << endl;
    cout << cp.second.x << " " << cp.second.y << endl;
    cout << cp.dist;


    cout << "\n\n";

    cp = findCP(sortedX, sortedY);

	cout << "O(nlog(n)) Answer : " << "\n\n";
    cout << cp.first.x << " " << cp.first.y << endl;
    cout << cp.second.x << " " << cp.second.y << endl;
    cout << cp.dist;

    cout << endl;

	ofstream outfile;
	outfile.open("pairs.txt");

	for(int i=0; i<points.size(); i++)
        outfile << points[i].x << " " << points[i].y << endl;

	outfile.close();

	outfile.open("answer.txt");

	outfile << cp.first.x << " " << cp.first.y << endl;
	outfile << cp.second.x << " " << cp.second.y << endl;
	outfile << cp.dist << endl;

	outfile.close();


    ifstream preIndex, postIndex;
    ofstream index;
    preIndex.open("preIndex.txt");
    postIndex.open("postIndex.txt");
    index.open("index.html");

    string line;

    vector<string> content;

    while(getline(preIndex, line)) {
        content.push_back(line);
    }

    content.push_back(string("<svg width=") + string("1000") + string(" height=") + string("600") + string(">"));

    for(int i=0; i<points.size(); i++) {

        string s;
        s += "<circle cx=";
        s += to_string(points[i].x);
        s += " cy=";
        s += to_string(points[i].y);
        s += " r=";
        s += "5";
        s += " stroke=";
        s += "white";
        s += " stroke-width=";
        s += "0";
        s += " fill=";
        // s += "white";
        if(((points[i].x==cp.first.x) && (points[i].y==cp.first.y)) || ((points[i].x == cp.second.x) && (points[i].y == cp.second.y))) {
            s += "red";
        } else {
            s += "black";
        }
        s += " />";

        content.push_back(s);

        if(((points[i].x==cp.first.x) && (points[i].y==cp.first.y)) || ((points[i].x == cp.second.x) && (points[i].y == cp.second.y))) {
            cout << "alpha";
            string s;
            s += "<circle cx=";
            s += to_string(points[i].x);
            s += " cy=";
            s += to_string(points[i].y);
            s += " r=";
            s += to_string(cp.dist);
            s += " stroke=";
            s += "green";
            s += " stroke-width=";
            s += "2";
            s += " fill=";
            s += "transparent";
            s += " />";
            content.push_back(s);
        }
    }

    content.push_back("</svg>");

    while(getline(postIndex, line)) {
        content.push_back(line);
    }

    for(int i=0; i<content.size(); i++) {
        index << content[i] << endl;
    }

    preIndex.close();
    postIndex.close();
    index.close();


    return 0;
}
