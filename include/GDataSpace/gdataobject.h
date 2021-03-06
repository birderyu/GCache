#pragma once

#include "GCore/gobject.h"

namespace gcache {
	class GDataSet;
}

namespace gcache {

class GAPI GDataObject final
{
public:
	GDataObject(GDataSet *data_set, gsize row_id);

	gvoid GetValue(gsize column, gint &value);

private:
	GDataSet *m_pDataSet;
	gsize m_nRowId;
};

}