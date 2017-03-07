#ifndef _GEOMETRY_GEOMETRY_COLLECTION_H_
#define _GEOMETRY_GEOMETRY_COLLECTION_H_

#include "ggeometry.h"

class GAPI GGeometryCollection
	: public GGeometry
{
public:
	virtual ~GGeometryCollection() = 0;

	/****************************************************************************
	**
	** GGeometryCollection
	**
	** @name	Size
	** @brief	��ȡ��ǰ���ζ��������
	** @return	{gsize} ����
	**
	****************************************************************************/
	virtual gsize Size() const = 0;

	virtual GGeometryP GetAt(gsize pos) = 0;
	virtual const GGeometryP GetAt(gsize pos) const = 0;
	virtual gvoid SetAt(gsize pos, const GGeometryP &geo) = 0;
};

#endif // _GEOMETRY_GEOMETRY_COLLECTION_H_