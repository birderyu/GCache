#include "gjsonpair.h"
#include "gjsonvalue.h"
#include "gliststack.h"
#include "gjsonparsermessage.h"

GJsonPair::GJsonPair()
: m_pValue(GNULL)
{

}

GJsonPair::~GJsonPair()
{
	Dispose();
}

gbool GJsonPair::Valid() const
{
	return m_pValue != GNULL;
}

GString & GJsonPair::Key()
{
	return m_sKey;
}

const GString & GJsonPair::Key() const
{
	return m_sKey;
}

GJsonValue * GJsonPair::Value()
{
	return m_pValue;
}

const GJsonValue * GJsonPair::Value() const
{
	return m_pValue;
}

GString GJsonPair::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonPair = "\"";
	jsonPair += m_sKey;
	jsonPair += "\":";
	jsonPair += m_pValue->ToString();
	return jsonPair;
}

gbool GJsonPair::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // ���������ݣ���������
	GString parse_msg; // ��������˴��󣬷��ؿ��ܵ�ԭ��
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	gbool has_key = false;
	gsize key_start = GString::NULL_POS;

	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor);
		if (c == '\0')
		{
			// �����ַ���������������ʧ�ܣ�ֱ���˳�
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("�ַ�����ǰ����");
			}
			Dispose();
			return false;
		}
		else if (!G_CHAR_IS_ASCII(c))
		{
			// �����Ƿ����ַ�������ʧ�ܣ�ֱ���˳�
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("�Ƿ����ַ�");
			}
			Dispose();
			return false;
		}
		else if (G_CHAR_IS_SPACE(c))
		{
			// �հ��ַ��������κβ���
		}
		else if (c== '{' || c == '}' || 
			c == '[' || c == ']'||
			c == ',')
		{
			// ����ʧ�ܣ�ֱ���˳�
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
			}
			Dispose();
			return false;
		}
		else if (c == ':')
		{
			if (!has_key)
			{
				// ��û�н������Key��������':'������ʧ�ܣ�ֱ���˳�
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
				}
				Dispose();
				return false;
			}
			else
			{
				// �Ѿ�������Key��˵��Ӧ�ý���JsonValue��
				_cursor++; // �Ȱѹ����ƣ���Ϊ��ʱ���ָ�����':'
				GJsonValue *value = new GJsonValue();
				if (!value->Parse(jsonStr, &_cursor, msg))
				{
					// JsonValue����ʧ�ܣ��ͷ��ڴ棬ֱ���˳�
					if (cursor)
					{
						*cursor = _cursor;
					}
					delete value;
					Dispose();
					return false;
				}

				// JsonValue�����ɹ�������ѭ��
				m_pValue = value;
				break;
			}
		}
		else if (c == '"')
		{
			// ������'"'������Key
			if (has_key)
			{
				// Key�ѱ�������������ʧ�ܣ�ֱ���˳�
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
				}
				Dispose();
				return false;
			}
			else
			{
				if (key_start == GString::NULL_POS)
				{
					// Key��ʼ
					key_start = _cursor;
				}
				else
				{
					// Key������Key����Ϊ��
					if (_cursor <= key_start)
					{
						// ����ʧ�ܣ�ֱ���˳�
						if (cursor)
						{
							*cursor = _cursor;
						}
						if (msg)
						{
							msg->SetIsSuccess(false);
							msg->SetErrorCursor(_cursor);
							msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
						}
						Dispose();
						return false;
					}

					// �������ƣ�ע��Ӧ��ȥ����'"'
					m_sKey = jsonStr.SubString(key_start + 1, _cursor - key_start - 1);
					has_key = true;
				}
			}
		}
		else
		{
			// �����ַ����������κβ���
		}

		// ������
		_cursor++;
	} // while

	gbool success = (m_pValue != GNULL);
	if (!success)
	{
		// ����ʧ�ܣ������ڴ�
		Dispose();
	}

	if (cursor)
	{
		// ����ǰ���д����Ϣ
		*cursor = _cursor;
	}
	if (msg)
	{
		// ����Ϣд����Ϣ
		msg->SetIsSuccess(success);
		if (!success)
		{
			msg->SetErrorCursor(_cursor);
			if (!parse_msg.IsEmpty())
			{
				msg->SetErrorMessage(parse_msg);
			}
			else
			{
				msg->SetErrorMessage("δ֪��ԭ��");
			}
		}
	}
	return success;
}

gvoid GJsonPair::Dispose()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
	m_pValue = GNULL;
}
