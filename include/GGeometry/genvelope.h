// �������
#ifndef _GEOMETRY_ENVELOPE_H_
#define _GEOMETRY_ENVELOPE_H_

// ע�⣺����ṹ�д洢��Zֵ�����ڽ����ڶ�ά�����ݳ��������д�������������
// ��ˣ��ýṹֻ����Ϊһ������ṹ��������Ϊ�洢�ṹ��

#include "ggeometryglobal.h"
#include "GCore/gobject.h"

class GCoordinate;
class GCoordinateSequence;

class GAPI GEnvelope
	: public GObject
{
public:
	GEnvelope();
	GEnvelope(greal x, greal y);
	GEnvelope(greal x, greal y, greal z);
	GEnvelope(greal min_x, greal min_y, greal max_x, greal max_y);
	GEnvelope(greal min_x, greal min_y, greal min_z, greal max_x, greal max_y, greal max_z);
	GEnvelope(const GCoordinate &min_c, const GCoordinate &max_c);
	GEnvelope(const GCoordinateSequence &);
	GEnvelope(const GEnvelope &);

	GCoordinate Min() const;
	GCoordinate Max() const;
	GCoordinate Center() const;

	greal MinX() const;
	greal MinY() const;
	greal MinZ() const;

	greal MaxX() const;
	greal MaxY() const;
	greal MaxZ() const;

	greal CenterX() const;
	greal CenterY() const;
	greal CenterZ() const;

	greal Length() const;
	greal Width() const;
	greal Height() const;

	gvoid SetMin(const GCoordinate &);
	gvoid SetMax(const GCoordinate &);
	gvoid SetCenter(const GCoordinate &);

	gvoid SetMinX(greal);
	gvoid SetMinY(greal);
	gvoid SetMinZ(greal);

	gvoid SetMaxX(greal);
	gvoid SetMaxY(greal);
	gvoid SetMaxZ(greal);

	gvoid SetCenterX(greal);
	gvoid SetCenterY(greal);
	gvoid SetCenterZ(greal);

	gvoid SetLength(greal);
	gvoid SetWidth(greal);
	gvoid SetHeight(greal);

	guint Dimension() const;

private:
	// MinX, MinY(, MinZ), MaxX, MaxY(, MaxZ)
	greal m_tCoords[G_ENVELOPE_SIZE];
};

#endif // _GEOMETRY_ENVELOPE_H_