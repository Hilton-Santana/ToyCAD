#ifndef CUBICBEZIER_H
#define CUBICBEZIER_H

#include "curve.h"
#include "curves/line.h"

class CubicBezier : public Curve
{
public:
	CubicBezier();
	// virtual methods implemented
	int getType() { return (int)Curve::CUBICBEZIER; };
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
	double getXend() { return m_x4; };
	double getYend() { return m_y4; };
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
	double m_x4;
	double m_y4;
};
#endif // POLYLINE_H