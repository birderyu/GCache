#ifndef _GEOMETRY_GEOMETRY_GLOBAL_H_
#define _GEOMETRY_GEOMETRY_GLOBAL_H_

#include "GCore/gglobal.h"

#define G_GEOMETRY_HAS_Z

#ifdef G_GEOMETRY_HAS_Z
#	define G_COORDINATE_SIZE	3
#	define G_ENVELOPE_SIZE		6
#	define G_COORDINATE_X_POS	0
#	define G_COORDINATE_Y_POS	1
#	define G_COORDINATE_Z_POS	2
#else // !G_GEOMETRY_HAS_Z
#	define G_COORDINATE_SIZE	2
#	define G_ENVELOPE_SIZE		4
#	define G_COORDINATE_X_POS	0
#	define G_COORDINATE_Y_POS	1
#endif // G_GEOMETRY_HAS_Z

// ά�� * 4
enum G_GEOMETRY_DIMENSION
{
	GEOMETRY_DIMENSION_0 = 0,	/**< ��ά */
	GEOMETRY_DIMENSION_1 = 1,	/**< һά */
	GEOMETRY_DIMENSION_2 = 2,	/**< ��ά */
	GEOMETRY_DIMENSION_3 = 3,	/**< ��ά */
};

// �������� * 2
enum G_GEOMETRY_COORDINATE
{
	GEOMETRY_COORDINATE_PLANE	= 0,	/**< ƽ�� */
	GEOMETRY_COORDINATE_SPHERE	= 1,	/**< ���� */
};

// �������� * 32
enum G_GEOMETRY_TYPE
{
	GEOMETRY_TYPE_NULL = 0,
	GEOMETRY_TYPE_POINT,
	GEOMETRY_TYPE_CURVE,		// ��ģ��
	GEOMETRY_TYPE_SURFACE,		// ��ģ��
	GEOMETRY_TYPE_BODY,			// ��ģ��
	GEOMETRY_TYPE_COLLECTION,	// ����ģ��

	// ��ģ��ʵ��
	GEOMETRY_TYPE_SEGMENT,	// �߶�
	GEOMETRY_TYPE_LINE,		// ֱ��
	GEOMETRY_TYPE_POLYLINE, // ����
	GEOMETRY_TYPE_RING,		// ��

	// ��ģ��ʵ��
	GEOMETRY_TYPE_POLYLGON,
	GEOMETRY_TYPE_TRIANGLE,		// ������
	GEOMETRY_TYPE_QUADRANGLE,	// �ı���
	GEOMETRY_TYPE_1, // ����
	GEOMETRY_TYPE_2, // ������
	GEOMETRY_TYPE_3, // Բ��
	GEOMETRY_TYPE_4, // ��Բ��

	// ��ģ��ʵ��
	GEOMETRY_TYPE_POLYHEDRON,	// ������
	GEOMETRY_TYPE_TETRAHEDRON,	// ������
	GEOMETRY_TYPE_HEXAHEDRON,	// ������
	GEOMETRY_TYPE_5,	// ������
	GEOMETRY_TYPE_6,	// ������
	GEOMETRY_TYPE_7,	// ����

	// ����ģ��ʵ��
	GEOMETRY_TYPE_MULTI_POINT,
	GEOMETRY_TYPE_MULTI_POLYLINE,
	GEOMETRY_TYPE_MULTI_POLYLGON,
	GEOMETRY_TYPE_MULTI_POLYHEDRON,
};

struct GGeometryGlobal
{
	static greal _g_n_coordinate_x_;
	static greal _g_n_coordinate_y_;
	static greal _g_n_coordinate_z_;
};

#endif // _GEOMETRY_GEOMETRY_GLOBAL_H_