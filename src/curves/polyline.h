#ifndef POLYLINE_H
#define POLYLINE_H

#include "curve.h"
#include "curves/line.h"

class PolyLine : public Curve
{
public:
	PolyLine();

	// virtual methods implemented
	int getType() { return (int)Curve::POLYLINE; };
	bool isUnlimited() { return true; };
	void addPoint(double _x, double _y);
	Point getPoint(double _t);
	bool isPossible() { return true; };
	vector<Point> getPoints();
	vector<Point> getPointsToDraw();
	vector<Point> getPointsToDraw(Point _pt);
	double closestPoint(double* _x, double* _y);
	void getBoundBox(double* _xmin, double* _xmax,
		double* _ymin, double* _ymax);
	double getXinit() { return m_x1; };
	double getYinit() { return m_y1; };
	double getXend() { return m_xInner; };
	double getYend() { return m_yInner; };
private:
	vector<Line> m_lines;
	Line m_line;
	int m_nLines;
	double m_x1;
	double m_y1;
	double m_xInner;
	double m_yInner;
};
#endif // POLYLINE_H