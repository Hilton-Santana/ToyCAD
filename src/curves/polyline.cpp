#include "polyline.h"
#include <math.h>
#include <vector>

PolyLine::PolyLine()
{
	m_nPts = 0;
	m_nLines = 0;
}


//Virtual methods
void
PolyLine::addPoint(double _x, double _y)
{
	if (m_nPts == 0) // first point 
	{
		m_x1 = _x;
		m_y1 = _y;
		m_nPts++;
		m_lines.push_back(m_line);
		this->m_lines[m_nLines].addPoint(m_x1, m_y1);

	}
	else
	{
		m_xInner = _x;
		m_yInner = _y;
		m_nPts++;
		this->m_lines[m_nLines].addPoint(m_xInner, m_yInner);
		m_nLines++;
		// Reset line
		this->m_line = Line();
		// New line
		this->m_line.addPoint(m_xInner, m_yInner);
		m_lines.push_back(m_line);

	}


}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Point
PolyLine::getPoint(double _t)
{
	Point p;
	double h, n_t;
	int k;
	h = 1. / m_nLines; // step 
	k = (_t - 0.01) / h;      // line where _t belong
	n_t = (_t - k*h) / h; // t in the local domain (line domain)

	p = m_lines[k].getPoint(n_t);

	return p;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
PolyLine::getPoints()
{

	vector<Point> tempPts;
	vector<Point> tempPtsTemp;

	tempPtsTemp = m_lines[0].getPoints();
	tempPts.push_back(tempPtsTemp[0]);

	for (int i = 0; i < m_nLines; i++)
	{
		tempPtsTemp = m_lines[i].getPoints();
		for (int i = 0; i < tempPtsTemp.size(); i++)
		{
			tempPts.push_back(tempPtsTemp[i]);
		}

	}
	return tempPts;


}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
PolyLine::getPointsToDraw()
{

	vector<Point> tempPts;
	vector<Point> tempPtsTemp;

	tempPtsTemp = m_lines[0].getPointsToDraw();
	tempPts.push_back(tempPtsTemp[0]);
	tempPts.push_back(tempPtsTemp[1]);

	for (int i = 1; i < m_nLines; i++)
	{
		tempPtsTemp = m_lines[i].getPointsToDraw();
		tempPts.push_back(tempPtsTemp[1]);
	}
	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
PolyLine::getPointsToDraw(Point _pt)
{
	vector<Point> tempPts;
	vector<Point> tempPtsTemp;


	for (int i = 0; i <= m_nLines; i++)
	{
		tempPtsTemp = m_lines[i].getPointsToDraw(_pt);

		for (int i = 0; i < tempPtsTemp.size(); i++)
		{
			tempPts.push_back(tempPtsTemp[i]);
		}

	}

	return tempPts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
double
PolyLine::closestPoint(double* _x, double* _y)
{
	double distTemp, dist;
	double xtemp, ytemp;
	xtemp = *_x;
	ytemp = *_y;

	dist = m_lines[0].closestPoint(_x, _y);
	for (int i = 1; i < m_nLines; i++)
	{
		*_x = xtemp;
		*_y = ytemp;
		distTemp = m_lines[i].closestPoint(_x, _y);
		if (distTemp < dist)
		{
			*_x = xtemp;
			*_y = ytemp;
			dist = m_lines[i].closestPoint(_x, _y);
		}
	}
	return dist;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
PolyLine::getBoundBox(double* _xmin, double* _xmax,
double* _ymin, double* _ymax)
{
	double xminTemp, xmaxTemp, yminTemp, ymaxTemp;

	m_lines[0].getBoundBox(_xmin, _xmax, _ymin, _ymax);
	xminTemp = *_xmin;
	xmaxTemp = *_xmax;
	yminTemp = *_ymin;
	ymaxTemp = *_ymax;

	for (int i = 1; i < (m_nLines); i++)
	{
		m_lines[i].getBoundBox(_xmin, _xmax, _ymin, _ymax);
		xminTemp = (*_xmin < xminTemp) ? *_xmin : xminTemp;
		xmaxTemp = (*_xmax > xmaxTemp) ? *_xmax : xmaxTemp;
		yminTemp = (*_ymin < yminTemp) ? *_ymin : yminTemp;
		ymaxTemp = (*_ymax > ymaxTemp) ? *_ymax : ymaxTemp;
	}

	*_xmin = xminTemp;
	*_xmax = xmaxTemp;
	*_ymin = yminTemp;
	*_ymax = ymaxTemp;
}