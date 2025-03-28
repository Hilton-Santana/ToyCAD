#include "cubicbezier.h"
#include <algorithm>    // std::for_each
#include <math.h>
#include <vector>

using namespace std;

CubicBezier::CubicBezier()
{
	m_nPts = 0;
	m_nSteps = 100;
	for (int i = 0; i < 6; i++) m_lines.push_back(m_line);

}


//Virtual methods
void
CubicBezier::addPoint(double _x, double _y)
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
		m_x4 = _x;
		m_y4 = _y;
		m_nPts++;
	}
	else if (m_nPts == 2)
	{
		m_x2 = _x;
		m_y2 = _y;
		m_nPts++;

	}
	else if (m_nPts == 3)
	{
		m_x3 = _x;
		m_y3 = _y;
		m_nPts++;
	}

}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Point
CubicBezier::getPoint(double _t)
{
	Point pt1, pt2, pt3, pt4, pt;
	vector <double> arclength;
	double seg, total_length,target_length;
	int i, j, index;

	if (_t == 0)
	{
		return Point(m_x1, m_y1);
	}
	else if (_t == 1)
	{
		return Point(m_x4, m_y4);
	}
	// search the nearest len
	seg = 0;
	// acumullate segments
	for (i = 0; i < m_nSteps; i++)
	{
		pt2 = m_ptToDraw[i + 1];
		pt1 = m_ptToDraw[i];
		seg += euclidiandistance(pt2, pt1) ;
		arclength.push_back(seg);

	}
	total_length = arclength[m_nSteps - 1];
	target_length = _t*total_length;
	//search the target length with bissection method
	i = 0; 
	j = m_nSteps - 1; 
	index = 0;
	while (i < j)
	{
		index = i + (((j - i) / 2) | 0);
		if (arclength[index] < target_length)
		{
			i = index + 1;
		}
		else
		{
			j = index;
		}
	}
	pt = m_ptToDraw[index+1];

	return pt;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
CubicBezier::isPossible()
{
	if (m_nPts < 4)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
CubicBezier::getPoints()
{
	Point p1, p2, p3, p4;
	vector<Point> tempPts;
	p1 = Point(m_x1, m_y1);
	p2 = Point(m_x2, m_y2);
	p3 = Point(m_x3, m_y3);
	p4 = Point(m_x4, m_y4);
	tempPts.push_back(p1);
	tempPts.push_back(p2);
	tempPts.push_back(p3);
	tempPts.push_back(p4);
	return tempPts;


}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
CubicBezier::getPointsToDraw()
{
	
	vector <Point> ptsTemp;
	Point pt1, pt2, pt3, pt4, pt;
	float t;
	pt1 = Point(m_x1, m_y1);
	pt2 = Point(m_x2, m_y2);
	pt3 = Point(m_x3, m_y3);
	pt4 = Point(m_x4, m_y4);

	for (int i = 0; i <= m_nSteps; i++)
	{
		t = (float) i / (float) m_nSteps;
		pt = pow((1 - t), 3)*pt1 + 3 * pow((1 - t), 2)*t*pt2 + 3 * (1 - t)*pow(t, 2)*pt3 + pow(t, 3)*pt4;
		ptsTemp.push_back(pt);

	}

	m_ptToDraw = ptsTemp;
	return m_ptToDraw;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
CubicBezier::getPointsToDraw(Point _pt)
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
		double t=0, dt;
		this->m_lines[0] = Line();
		this->m_lines[0].addPoint(m_x1, m_y1);
		this->m_lines[0].addPoint(_pt.getX(), _pt.getY());
		this->m_lines[1] = Line();
		this->m_lines[1].addPoint(_pt.getX(), _pt.getY());
		this->m_lines[1].addPoint(m_x4, m_y4);
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
	else if (m_nPts == 3)
	{
		Point p1, p2, p3, p4, p5;
		double t = 0, dt;
		this->m_lines[0] = Line();
		this->m_lines[0].addPoint(m_x1, m_y1);
		this->m_lines[0].addPoint(m_x2, m_y2);
		this->m_lines[1] = Line();
		this->m_lines[1].addPoint(m_x2, m_y2);
		this->m_lines[1].addPoint(_pt.getX(),_pt.getY());
		this->m_lines[2] = Line();
		this->m_lines[2].addPoint(_pt.getX(), _pt.getY());
		this->m_lines[2].addPoint(m_x4, m_y4);
		for (int i = 0; i < m_nSteps+1; i++)
		{
			float dt = (float)i / (float)m_nSteps;
			t = dt;
			p1 = m_lines[0].getPoint(t);
			p2 = m_lines[1].getPoint(t);
			p3 = m_lines[2].getPoint(t);
			m_lines[3].addPoint(p1.getX(), p1.getY());
			m_lines[3].addPoint(p2.getX(), p2.getY());
			m_lines[4].addPoint(p2.getX(), p2.getY());
			m_lines[4].addPoint(p3.getX(), p3.getY());
			p4 = m_lines[3].getPoint(t);
			p5 = m_lines[4].getPoint(t);
			m_lines[5].addPoint(p4.getX(), p4.getY());
			m_lines[5].addPoint(p5.getX(), p5.getY());
			tempPts.push_back(m_lines[5].getPoint(t));
			this->m_lines[3] = Line();
			this->m_lines[4] = Line();
			this->m_lines[5] = Line();
		}
	}

	//ptToDraw = tempPts;


	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
CubicBezier::closestPoint(double* _x, double* _y)
{
	double xOn, yOn, dist, distTemp;
	int k;
	xOn = m_ptToDraw[0].getX();
	yOn = m_ptToDraw[0].getY();
	dist = sqrt((xOn - *_x)*(xOn - *_x) + (yOn - *_y)*(yOn - *_y));
	k = 0;
	for (int i = 1; i <= m_nSteps; i++)
	{
		xOn = m_ptToDraw[i].getX();
		yOn = m_ptToDraw[i].getY();
		distTemp = sqrt((xOn - *_x)*(xOn - *_x) + (yOn - *_y)*(yOn - *_y));
		if (distTemp < dist)
		{
			dist = distTemp;
			k++;
		}

	}
	*_x = m_ptToDraw[k].getX();
	*_y = m_ptToDraw[k].getY();
	return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CubicBezier::getBoundBox(double* _xmin, double* _xmax,
double* _ymin, double* _ymax)
{
	// Consider the polygon formed by the four Bezier's points
	
	*_xmin = m_x1;
	*_xmax = m_x1;
	*_ymin = m_y1;
	*_ymax = m_y1;

	*_xmin = (*_xmin < m_x2) ? *_xmin : m_x2;
	*_xmin = (*_xmin < m_x3) ? *_xmin : m_x3;
	*_xmin = (*_xmin < m_x4) ? *_xmin : m_x4;
	*_xmax = (*_xmax > m_x2) ? *_xmax : m_x2;
	*_xmax = (*_xmax > m_x3) ? *_xmax : m_x3;
	*_xmax = (*_xmax > m_x4) ? *_xmax : m_x4;

	*_ymin = (*_ymin < m_y2) ? *_ymin : m_y2;
	*_ymin = (*_ymin < m_y3) ? *_ymin : m_y3;
	*_ymin = (*_ymin < m_y4) ? *_ymin : m_y4;
	*_ymax = (*_ymax > m_y2) ? *_ymax : m_y2;
	*_ymax = (*_ymax > m_y3) ? *_ymax : m_y3;
	*_ymax = (*_ymax > m_y4) ? *_ymax : m_y4;
}
