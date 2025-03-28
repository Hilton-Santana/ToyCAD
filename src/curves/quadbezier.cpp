#include "quadbezier.h"
#include <math.h>
#include <vector>
using namespace std;

QuadBezier::QuadBezier()
{
	m_nPts = 0;
	m_nSteps = 50;
	for (int i = 0; i < 3; i++) m_lines.push_back(m_line);
}


//Virtual methods
void
QuadBezier::addPoint(double _x, double _y)
{
	if (m_nPts == 0) // first point 
	{
		m_x1 = _x;
		m_y1 = _y;
		m_nPts++;
		this->m_lines[0].addPoint(m_x1, m_y1);
	}
	else if (m_nPts == 1)
	{
		m_x3 = _x;
		m_y3 = _y;
		m_nPts++;
	}
	else if (m_nPts == 2)
	{
		m_x2 = _x;
		m_y2 = _y;
		m_nPts++;

	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Point
QuadBezier::getPoint(double _t)
{
	double xOn, yOn;
	Point pt1, pt2, pt3, pt;
	pt1 = Point(m_x1, m_y1);
	pt2 = Point(m_x2, m_y2);
	pt3 = Point(m_x3, m_y3);

	pt = pow((1 - _t), 2)*pt1 + 2 *(1-_t)*_t*pt2 + pow(_t,2)*pt3;
	return pt;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
QuadBezier::isPossible()
{
	if (m_nPts < 3)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
QuadBezier::getPoints()
{
	Point p1, p2, p3;
	vector<Point> tempPts;
	p1 = Point(m_x1, m_y1);
	p2 = Point(m_x2, m_y2);
	p3 = Point(m_x3, m_y3);
	tempPts.push_back(p1);
	tempPts.push_back(p2);
	tempPts.push_back(p3);
	return tempPts;


}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
QuadBezier::getPointsToDraw()
{
	return m_ptToDraw;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
QuadBezier::getPointsToDraw(Point _pt)
{
	vector<Point> tempPts;
	vector<Point> tempPtsTemp;

	//Implement Casteljau's algorithm 

	if (m_nPts == 1)
	{
		tempPtsTemp = m_lines[0].getPointsToDraw(_pt);
		tempPts.push_back(tempPtsTemp[0]);
		tempPts.push_back(tempPtsTemp[1]);
	}
	else if (m_nPts == 2)
	{
		Point p1, p2;
		float t, dt;
		//first line 
		this->m_lines[0] = Line();
		this->m_lines[0].addPoint(m_x1, m_y1);
		this->m_lines[0].addPoint(_pt.getX(), _pt.getY());
		//second line
		this->m_lines[1] = Line();
		this->m_lines[1].addPoint(_pt.getX(), _pt.getY());
		this->m_lines[1].addPoint(m_x3, m_y3);
		//third line
		this->m_line = Line();
		m_lines.push_back(m_line);
		for (int i = 0; i < m_nSteps+1; i++)
		{
			float dt = (float)i / (float)m_nSteps;
			t = dt;
			p1 = m_lines[0].getPoint(t);
			p2 = m_lines[1].getPoint(t);
			m_lines[2].addPoint(p1.getX(), p1.getY());
			m_lines[2].addPoint(p2.getX(), p2.getY());
			tempPts.push_back(m_lines[2].getPoint(t));
			this->m_lines[2] = Line();
		}
	}

	m_ptToDraw = tempPts;


	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
QuadBezier::closestPoint(double* _x, double* _y)
{
	double xOn, yOn, dist, distTemp;

	xOn = m_ptToDraw[0].getX();
	yOn = m_ptToDraw[0].getY();
	dist = sqrt((xOn - *_x)*(xOn - *_x) + (yOn - *_y)*(yOn - *_y));
	for (int i = 1; i <= m_nSteps; i++)
	{
		xOn = m_ptToDraw[i].getX();
		yOn = m_ptToDraw[i].getY();
		distTemp = sqrt((xOn - *_x)*(xOn - *_x) + (yOn - *_y)*(yOn - *_y));
		if (distTemp < dist)
		{
			dist = distTemp;
		}

	}
	return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
QuadBezier::getBoundBox(double* _xmin, double* _xmax,
double* _ymin, double* _ymax)
{
	// Consider the polygon formed by the four Bezier's points
	
	*_xmin = m_x1;
	*_xmax = m_x1;
	*_ymin = m_y1;
	*_ymax = m_y1;

	*_xmin = (*_xmin < m_x2) ? *_xmin : m_x2;
	*_xmin = (*_xmin < m_x3) ? *_xmin : m_x3;
	*_xmax = (*_xmax > m_x2) ? *_xmax : m_x2;
	*_xmax = (*_xmax > m_x3) ? *_xmax : m_x3;

	*_ymin = (*_ymin < m_y2) ? *_ymin : m_y2;
	*_ymin = (*_ymin < m_y3) ? *_ymin : m_y3;
	*_ymax = (*_ymax > m_y2) ? *_ymax : m_y2;
	*_ymax = (*_ymax > m_y3) ? *_ymax : m_y3;
}