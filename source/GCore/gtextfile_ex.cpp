#include "gtextfile_ex.h"
#include "gtextfile.h"

#define G_TEXT_DOCUMNET_BUFFER_SIZE 4096

GTextFile_Ex::GTextFile_Ex(const GString &sFileName)
: GFile_Ex(sFileName)
{

}

gbyte GTextFile_Ex::Format() const
{
	return GFile::TEXT_FILE;
}

gbool GTextFile_Ex::GetChar(guchar &c)
{
	if (EndOfFile() || !CanRead())
	{
		return false;
	}

	gint ic = fgetc(m_pFileStream);
	if (EOF == ic)
	{
		return false;
	}

	c = static_cast<guchar>(ic);
	return true;
}

gbool GTextFile_Ex::PutChar(guchar c)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}

	if (EOF == fputc(c, m_pFileStream))
	{
		return false;
	}
	return false;
}

gbool GTextFile_Ex::Read(gsize size, GString &str)
{
	if (EndOfFile() || !CanRead() || size <= 0)
	{
		return false;
	}

	gsize old_size = str.Size();
	str.Resize(old_size + size);

	gsize real_add_size = fread(str.CursorAt(old_size), sizeof(gchar), size, m_pFileStream);
	if (real_add_size == 0)
	{
		str.Resize(old_size);
		return false;
	}

	str.Resize(old_size + real_add_size);
	return true;
}

gbool GTextFile_Ex::ReadAll(GString &str)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}

	// �ɵ��ļ��α걸��
	glong old_tell = Tell();

	if (!Seek(0, GFile::SEEK_MODE_END))
	{
		// ��ԭ�α�
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	glong all_size = Tell();
	if (all_size < 0)
	{
		// ��ԭ�α�
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	// ���α����õ���ʼλ��
	Rewind();
	if (!Read(all_size, str))
	{
		// ��ԭ�α�
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	return true;
}

gbool GTextFile_Ex::Write(const GString &str)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}
	if (0 == fwrite(str.CString(), sizeof(gchar), str.Size() + 1, m_pFileStream))
	{
		return false;
	}
	return true;
}

gcstring GTextFile_Ex::OpenMode() const
{
	switch (m_nOpenMode)
	{
	case GFile::NO_OPEN:
		return GNULL;
	case GFile::ONLY_READ:
		return "rt";
	case GFile::ONLY_WIRTE:
		return "wt";
	case GFile::READ_WIRTE:
		return "rt+";
	case GFile::APPEND:
		return "at";
	default:
		break;
	}
	return GNULL;
}

#undef G_TEXT_DOCUMNET_BUFFER_SIZE
