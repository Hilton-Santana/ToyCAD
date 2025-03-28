#include "circle.h"

#include <math.h>

# define m_PI           3.14159265358979323846  /* pi */

//-------------------------------------------------------------------------
Circle::Circle()
{
	m_nPts = 0;
	m_nSteps = 50;
	m_radius = 0;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Circle::Circle(double _x1, double _y1, double _x2, double _y2)
{
	m_x1 = _x1;
	m_y1 = _y1;
	m_x2 = _x2;
	m_y2 = _y2;
	m_nPts = 2;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
Circle::addPoint(double _x, double _y)
{
	if (m_nPts == 0)
	{
		m_x1 = _x;
		m_y1 = _y;
		m_nPts++;
	}
	else if (m_nPts == 1)
	{
		m_x2 = _x;
		m_y2 = _y;
		m_nPts++;
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Point
Circle::getPoint(double _t)
{
	Point center, circ, pt;

	center = Point(m_x1, m_y1);
	circ = Point(m_x2, m_y2);

	pt = center + Point(m_radius*cos(2 * m_PI*_t + m_phase), m_radius*sin(2 * m_PI*_t + m_phase));

	return pt;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
Circle::isPossible()
{
	if (m_nPts < 2)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
Circle::getPoints()
{
	if (m_nPts == 1)
	{
		vector<Point> tempPts(1);
		tempPts[0] = Point(m_x1, m_y1);
		return tempPts;
	}
	vector<Point> tempPts(2);
	tempPts[0] = Point(m_x1, m_y1);
	tempPts[1] = Point(m_x2, m_y2);
	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
Circle::getPointsToDraw()
{
	vector<Point> tempPts;
	Point center, pts, circ;
	double x, y,dot,cross;

	circ = Point(m_x2, m_y2);
	center = Point(m_x1, m_y1);

	//find phase angle
	dot = dotprod(normalize(circ - center), Point(1, 0));
	cross = crossprod(Point(1, 0), (circ - center));
	m_phase = acos(dot);
	if (cross <= 0)
	{
		m_phase = acos(-dot);
		m_phase = m_PI + m_phase;
	}

	m_radius = euclidiandistance(center, circ);

	for (int i = 0; i <= m_nSteps; i++)
	{
		double t = i * 2 * m_PI / m_nSteps;
		x = m_radius*cos(t + m_phase);
		y = m_radius*sin(t + m_phase);
		pts = center + Point(x, y);
		tempPts.push_back(pts);

	}
	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
Circle::getPointsToDraw(Point _pt)
{
	vector<Point> tempPts;
	Point center, pts;
	double x, y, dot,cross,radius, phase;

	center = Point(m_x1, m_y1);
	radius = euclidiandistance(center, _pt);

	//find phase angle
	dot = dotprod(normalize(_pt - center), Point(1, 0));
	cross = crossprod(Point(1, 0), (_pt - center));
	phase = acos(dot);
	if (cross <= 0)
	{
		phase = acos(-dot);
		phase = m_PI + phase;
	}


	for (int i = 0; i <= m_nSteps; i++)
	{
		double t = i * 2 * m_PI / m_nSteps;
		x = radius*cos(t + phase);
		y = radius*sin(t + phase);
		pts = center + Point(x, y);
		tempPts.push_back(pts);

	}

	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
Circle::closestPoint(double* _x, double* _y)
{
	Point center, pt;
	double dist, angle,dot,cross;

	pt = Point(*_x, *_y);
	center = Point(m_x1, m_y1);
	dist = euclidiandistance(pt, center);
	dist = abs(m_radius - dist);
	//find phase angle
	dot = dotprod(normalize(pt - center), Point(1, 0));
	cross = crossprod(Point(1, 0), (pt - center));
	angle = acos(dot);
	if (cross <= 0)
	{
		angle = acos(-dot);
		angle = m_PI + angle;
	}
	*_x = m_x1 + m_radius*cos(angle);
	*_y = m_y1 + m_radius*sin(angle);



	return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
Circle::getBoundBox(double* _xmin, double* _xmax,
double* _ymin, double* _ymax)
{
	*_xmin = m_x1 - m_radius;
	*_xmax = m_x1 + m_radius;
	*_ymin = m_y1 - m_radius;
	*_ymax = m_y1 + m_radius;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
Circle::setPoints(double _x1, double _y1, double _x2, double _y2)
{
	m_x1 = _x1;
	m_x2 = _x2;
	m_y1 = _y1;
	m_y2 = _y2;
}
//-------------------------------------------------------------------------
