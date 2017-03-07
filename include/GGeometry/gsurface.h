#ifndef _GEOMETRY_SURFACE_H_
#define _GEOMETRY_SURFACE_H_

#include "ggeometry.h"

class GAPI GSurface
	: virtual public GGeometry
{
public:
	/****************************************************************************
	**
	** GSurface
	**
	** @name	Area
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{greal} ���ֵ��Ĭ�ϵ�λΪƽ����
	**
	****************************************************************************/
	virtual greal Area() const = 0;
};

#endif // _GEOMETRY_SURFACE_H_