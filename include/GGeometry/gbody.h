#ifndef _GEOMETRY_BODY_H_
#define _GEOMETRY_BODY_H_

#include "ggeometry.h"

class GAPI GBody
	: virtual public GGeometry
{
public:
	/****************************************************************************
	**
	** GBody
	**
	** @name	Volume
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{greal} ���ֵ��Ĭ�ϵ�λΪ������
	**
	****************************************************************************/
	virtual greal Volume() const = 0;
};

#endif // _GEOMETRY_BODY_H_