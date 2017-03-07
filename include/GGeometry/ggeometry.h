/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	ggeometry.h
** @brief	�������νӿڵĶ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _GEOMETRY_GEOMETRY_H_
#define _GEOMETRY_GEOMETRY_H_

#include "ggeometryglobal.h"
#include "GCore/gobject.h"

class GGeometry;
class GGeometryFactory;
class GEnvelope;
class GCoordinate;
class GCoordinateSequence;
typedef GSharedPointer<GGeometry> GGeometryP;

/****************************************************************************
**
** ggeometry.h
**
** @class		GGeometry
** @brief		�������νӿ�
** @module		GGeometry
**
** �����������������м��ζ���ӿڵĻ��࣬����Ҫ��ģ�͵�˼�������һ��ӿڷ�װ��
**
****************************************************************************/
class GAPI GGeometry 
	: public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_GEOMETRY, };

public:
	/****************************************************************************
	**
	** GGeometry
	**
	** @name	~GGeometry
	** @brief	����������destructor��
	**
	** ��������Ӧ��������ģ�virtual����
	**
	****************************************************************************/
	virtual ~GGeometry() = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	Factory
	** @brief	��ȡ��ǰ���ζ���Ĺ���
	** @return	{const GGeometryFactory *} ���ι���
	**
	****************************************************************************/
	virtual const GGeometryFactory *Factory() const = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	Valid
	** @brief	��ǰʵ���Ƿ���Ч
	** @return	{gbool} ��Ч�򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual gbool Valid() const = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	GeometryType
	** @brief	��ȡ��ǰ����ļ�������
	** @return	{gint} �������ͣ���ֵ����ö�� {G_GEOMETRY_TYPE}
	** @see		{G_GEOMETRY_TYPE}
	**
	****************************************************************************/
	virtual gint GeometryType() const = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	Dimension
	** @brief	��ȡ��ǰ�����ά��
	** @return	{gint} ά�ȣ���ֵ����ö�� {G_GEOMETRY_DIMENSION}
	** @see		{G_GEOMETRY_DIMENSION}
	**
	****************************************************************************/
	virtual guint Dimension() const = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	Envelope
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{GEnvelope} ���
	** @see		{GEnvelope}
	**
	****************************************************************************/
	virtual GEnvelope Envelope() const = 0;

	/****************************************************************************
	**
	** GGeometry
	**
	** @name	CoordinateSequence
	** @brief	��ȡ��ǰ���ζ������������
	** @return	{GCoordinateSequence} ��������
	** @see		{GCoordinateSequence}
	**
	****************************************************************************/
	virtual GCoordinateSequence CoordinateSequence() const = 0;
	
	//virtual gbool IsEmpty() const = 0;
	//virtual gbool IsSimple() const = 0;
	//virtual gbool Clear() = 0;
	//virtual GGeometryP Flatten() const = 0; // ����ά��ɶ�ά

	//virtual greal Distance(const GGeometry &geo) const = 0;
	//virtual gbool Touches(const GGeometry &geo) const = 0;
	//virtual gbool Intersects(const GGeometry &geo) const = 0;
	//virtual gbool Disjoint(const GGeometry &geo) const = 0;
	//virtual gbool Crosses(const GGeometry &geo) const = 0;
	//virtual gbool Within(const GGeometry &geo) const = 0;
	//virtual gbool Contains(const GGeometry &geo) const = 0;
	//virtual gbool Overlaps(const GGeometry &geo) const = 0;
	//virtual gbool Covers(const GGeometry &geo) const = 0;
	//virtual gbool CoveredBy(const GGeometry &geo) const = 0;

	//virtual GGeometryP Buffer() const = 0;
	//virtual GGeometryP Intersection(const GGeometry &geo) const = 0;
	//virtual GGeometryP Union(const GGeometry &geo) const = 0;
	//virtual GGeometryP Difference(const GGeometry &geo) const = 0;
};

#endif // _GEOMETRY_GEOMETRY_H_