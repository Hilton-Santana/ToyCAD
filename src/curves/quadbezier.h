#ifndef QUADBEZIER_H
#define QUADBEZIER_H

#include "curve.h"
#include "curves/line.h"

class QuadBezier : public Curve
{
public:
	QuadBezier();

	// virtual methods implemented
	int getType() { return (int)Curve::QUADBEZIER; };
	bool isUnlimited() { return false; };
	void addPoint(double _x, double _y);
	Point getPoint(double _t);
	bool isPossible();
	vector<Point> getPoints();
	vector<Point> getPointsToDraw();
	vector<Point> getPointsToDraw(Point _pt);
	double closestPoint(double* _x, double* _y);
	void getBoundBox(double* _xmin, double* _xmax,
		double* _ymin, double* _ymax);
	double getXinit() { return m_x1; };
	double getYinit() { return m_y1; };
	double getXend() { return m_x3; };
	double getYend() { return m_y3; };
private:
	Line m_line;
	vector<Line> m_lines;
	int m_nSteps;
	vector<Point> m_ptToDraw;
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
	double m_x3;
	double m_y3;
};
#endif // QUADBEZIER_H