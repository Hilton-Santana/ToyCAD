
#include "transfinbilinear.h"
#include <math.h>

// Macro definition for indexing a matrix with size = (m_nu+1,*)
// stored in a vector
//#define id_pts(i,j) (((i)*(m_nu+1))+(j))
int
TransfinBilinear::id_pts(int i, int j)
{
	return (((i)*(m_nu + 1)) + (j));
}


//-------------------------------------------------------------------------
TransfinBilinear::TransfinBilinear()
	: m_nu(0)
	, m_nv(0)
{
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
TransfinBilinear::setParam(vector<vector<int>> _loops)
{
	// Check for just one loop
	if (_loops.size() != 1)
		return false;

	// Check for exactly four curves on loop
	vector<int> curveSbdvs = _loops[0];
	if (curveSbdvs.size() != 4)
		return false;

	// Check for equal number of subdivisions on opposite curves of loop
	if (curveSbdvs[0] != curveSbdvs[2])
		return false;
	if (curveSbdvs[1] != curveSbdvs[3])
		return false;

	// Save parameters of valid boundary loop
	m_nu = curveSbdvs[0];
	m_nv = curveSbdvs[1];

	return true;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
bool
TransfinBilinear::generateMesh(vector<Point> _bound,
vector<Point>& _pts, vector<vector<int> >& _conn)
{
	// Total number of boundary nodes must be consistent with
	// number of boundary segments
	if (_bound.size() != (m_nu + m_nv) * 2)
		return false;

	int id_bound = 0;
	Point pt(0.0, 0.0);
	int i;
	int j;
	vector<float> psi1, psi2, ksi1, ksi2;

	// Allocate point vector in row major order
	for (i = 0; i <= m_nv; i++)
	{
		for (j = 0; j <= m_nu; j++)
		{
			_pts.push_back(pt);
		}
	}

	// Input nodes from first boundary curve
	i = 0;
	for (j = 0; j < m_nu; j++)
	{
		_pts[id_pts(i, j)] = _bound[id_bound];
		id_bound++;
	}

	// Input node from second boundary curve
	j = m_nu;
	for (i = 0; i < m_nv; i++)
	{
		/*** COMPLETE HERE - TRANSFINBILINEAR: 01 ***/
		_pts[id_pts(i, j)] = _bound[id_bound];
		id_bound++;
		/*** COMPLETE HERE - TRANSFINBILINEAR: 01 ***/
	}

	// Input node from third boundary curve
	/*** COMPLETE HERE - TRANSFINBILINEAR: 02 ***/
	i = m_nv;
	for (j = m_nu; j > 0; j--)
	{
		_pts[id_pts(i, j)] = _bound[id_bound];
		id_bound++;
	}
	/*** COMPLETE HERE - TRANSFINBILINEAR: 02 ***/

	// Input node from fourth boundary curve
	/*** COMPLETE HERE - TRANSFINBILINEAR: 03 ***/
	j = 0;
	for (i = m_nv; i > 0; i--)
	{
		_pts[id_pts(i, j)] = _bound[id_bound];
		id_bound++;
	}

	/*** COMPLETE HERE - TRANSFINBILINEAR: 03 ***/
	// Generate interior nodes
	/*** COMPLETE HERE - TRANSFINBILINEAR: 04 ***/
	vector<double> u, v;
	double h;
	for (i = 0; i <= m_nu; i++)
	{
		h = i*(1. / m_nu);
		u.push_back(h);
	}
	for (i = 0; i <= m_nv; i++)
	{
		h = i*(1. / m_nv);
		v.push_back(h);
	}
	for (j = 1; j < m_nu; j++)
	{
		for (i = 1; i < m_nv; i++)
		{
			_pts[id_pts(i, j)] = (1 - v[i])*_pts[id_pts(0, j)] + v[i] * _pts[id_pts(m_nv, j)] +
				(1 - u[j])*_pts[id_pts(i, 0)] + u[j] * _pts[id_pts(i, m_nu)] -
				(1 - u[j])*(1 - v[i])*_pts[id_pts(0, 0)] - u[j] * (1 - v[i])*_pts[id_pts(0, m_nu)]
				- u[j] * v[i] * _pts[id_pts(m_nv, m_nu)] - (1 - u[j])*v[i] * _pts[id_pts(m_nv, 0)];

		}
	}

	/*** COMPLETE HERE - TRANSFINBILINEAR: 04 ***/

	// Generate quadrilateral elements
	/*** COMPLETE HERE - TRANSFINBILINEAR: 05 ***/
	int n, k, l, node1, node2, node3, node4;
	vector<int> elem;
	n = m_nu*m_nv;
    for (i = 0; i < n; i++)
	{
		k = i / m_nu;
		l = i - k*m_nu;
		node1 = id_pts(k, l);
		node2 = id_pts(k, l+1);
		node3 = id_pts(k + 1, l + 1);
		node4 = id_pts(k+1, l);
		elem.push_back(node1);
		elem.push_back(node2);
		elem.push_back(node3);
		elem.push_back(node4);
		_conn.push_back(elem);
		elem.clear();
	}
	/*** COMPLETE HERE - TRANSFINBILINEAR: 05 ***/

	return true;
}
//-------------------------------------------------------------------------
