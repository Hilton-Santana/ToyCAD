#include "curvecollector.h"
#include "curves/curve.h"
#include "curves/line.h"
#include "curves/polyline.h"
#include "curves/cubicbezier.h"
#include "curves/circle.h"
#include "curves/circlearc.h"
#include "curves/quadbezier.h"

#ifndef ABS
#define ABS(x) (((x) < 0.0)? -(x): (x))
#endif

//-------------------------------------------------------------------------
CurveCollector::CurveCollector()
	: m_curve(NULL)
	, m_prevPt(0.0, 0.0)
	, m_tempPt(0.0, 0.0)
{
	m_curveType = Curve::LINE;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
CurveCollector::~CurveCollector()
{
	if (m_curve != NULL)
		delete m_curve;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::setCurveType(int _type)
{
	if (m_curveType == _type)
		return;

	switch (_type)
	{
	default:
	case Curve::LINE:
		m_curveType = Curve::LINE;
		break;
	case Curve::POLYLINE:
		m_curveType = Curve::POLYLINE;
		break;
	case Curve::QUADBEZIER:
		m_curveType = Curve::QUADBEZIER;
		break;
	case Curve::CUBICBEZIER:
		m_curveType = Curve::CUBICBEZIER;
		break;
	case Curve::CIRCLE:
		m_curveType = Curve::CIRCLE;
		break;
	case Curve::CIRCLEARC:
		m_curveType = Curve::CIRCLEARC;
		break;

	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::startCurveCollection()
{
	if (m_curve != NULL)
		delete m_curve;

	switch (m_curveType)
	{
	default:
	case Curve::LINE:
	{
		m_curve = new Line();
		break;
	}
	case Curve::POLYLINE:
	{
		m_curve = new PolyLine();
		break;
	}
	case Curve::CUBICBEZIER:
	{
		m_curve = new CubicBezier();
		break;
	}
	case Curve::CIRCLE:
	{
		m_curve = new Circle();
		break;
	}
	case Curve::CIRCLEARC:
	{
		m_curve = new CircleArc();
		break;
	}
	case Curve::QUADBEZIER:
	{
		m_curve = new QuadBezier();
		break;
	}
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::endCurveCollection()
{
	m_curve = NULL;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
CurveCollector::isActive()
{
	if (m_curve != NULL)
	{
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
CurveCollector::isCollecting()
{
	if (m_curve != NULL)
	{
		if (m_curve->getNumberOfPoints() > 0)
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
CurveCollector::hasFinished()
{
	if (m_curve != NULL)
	{
		if (m_curve->isPossible())
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
CurveCollector::isUnlimited()
{
	if (m_curve != NULL)
	{
		if (m_curve->isUnlimited())
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
int
CurveCollector::insertPoint(double _x, double _y, double _tol)
{
	if (isCollecting())
	{
		if ((ABS(_x - m_prevPt.getX()) <= _tol) &&
			(ABS(_y - m_prevPt.getY()) <= _tol))
			return 0;
	}
	m_curve->addPoint(_x, _y);
	m_prevPt.setCoords(_x, _y);
	return 1;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
int
CurveCollector::addTempPoint(double _x, double _y)
{
	m_tempPt.setCoords(_x, _y);
	return 1;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
CurveCollector::getDrawPoints()
{
	vector<Point> pts = m_curve->getPointsToDraw(m_tempPt);
	return pts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
vector<Point>
CurveCollector::getPoints()
{
	vector<Point> pts = m_curve->getPoints();
	return pts;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::getBoundBox(double* _xmin, double* _xmax,
double* _ymin, double* _ymax)
{
	if (!m_curve)
		return;
	m_curve->getBoundBox(_xmin, _xmax, _ymin, _ymax);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::reset()
{
	if (m_curve != NULL)
		delete m_curve;
	m_curve = NULL;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void
CurveCollector::kill()
{
	if (m_curve != NULL)
		delete m_curve;
	delete this;
}
//-------------------------------------------------------------------------
