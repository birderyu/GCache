#include "gjsonarray.h"
#include "gjsonvalue.h"
#include "gjsonparsermessage.h"
#include "gliststack.h"

GJsonArray::GJsonArray()
{

}

GJsonArray::~GJsonArray()
{
	Dispose();
}

gbool GJsonArray::Valid() const
{
	return !m_tJsonValues.IsEmpty();
}

GString GJsonArray::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonArr = "[";
	gsize size = m_tJsonValues.Size();
	gsize pos = 0;
	for (GList<GJsonValue*>::ConstIterator citer = m_tJsonValues.ConstBegin();
		citer != m_tJsonValues.ConstEnd(); citer++)
	{
		if (!*citer)
		{
			return GString();
		}
		else
		{
			jsonArr += (*citer)->ToString();
		}

		if (pos < size - 1)
		{
			jsonArr += ",";
		}
		pos++;
	}
	jsonArr += "]";
	return jsonArr;
}

gbool GJsonArray::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Dispose(); // ���������ݣ���������
	GString parse_msg; // ��������˴��󣬷��ؿ��ܵ�ԭ��
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	// �ַ�ջ
	// �����ַ�������ջ��'['��','
	// �������������ַ����ҷ��Ϲ���ʱ��������ջ
	// ������']'�ҷ��Ϲ���ʱ��'['��ջ
	// ��һ��JsonValue�����������Ҹ�JsonValue���ǵ�һ��ʱ��','��ջ
	GListStack<gchar> char_stack;

	// ѭ������
	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor); // ��ȡһ���ַ�

		if (c == '\0')
		{
			// �����ַ���������������ѭ������ʱ�������ж��Ƿ��Ѿ������ɹ�
			parse_msg = "�ַ�����ǰ����";
			break;
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
		else if (c == '[')
		{
			// ����'['��˵��Ӧ�ÿ�ʼ����JsonArray
			if (!char_stack.IsEmpty())
			{
				// '['֮ǰ��ջ���Ѿ������ݣ�����ʧ�ܣ�ֱ���˳�
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

			//����'['��ջ
			char_stack.Push(c); // '['��ջ
		}
		else if (c == ']')
		{
			// ����']'����������������ѭ������ʱ�������ж��Ƿ��Ѿ������ɹ�
			char_stack.Pop(); // '['��ջ
			parse_msg = "�Ƿ��Ĺ����ַ�";
			break;
		}
		else if (c == ',')
		{
			// ������','��˵���Ѿ�������������һ��JsonValue
			if (m_tJsonValues.IsEmpty())
			{
				// δ����JsonValue��������','������ʧ�ܣ�ֱ���˳�
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

			//����','��ջ
			char_stack.Push(c); // ','��ջ
		}
		else
		{
			// ��������֮����κ��ַ���˵��������һ��JsonValue
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

			if (!m_tJsonValues.IsEmpty())
			{
				gchar _c = '\0';
				char_stack.Pop(&_c); // ','��ջ
				if (_c != ',')
				{
					// ����ʧ�ܣ��ͷ��ڴ棬ֱ���˳�
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
					delete value;
					Dispose();
					return false;
				}
			}

			// �������ɹ���JsonPair����JsonPairs
			m_tJsonValues.PushBack(value);
		}
		// ������
		_cursor++;
	} // while

	// �Ƿ�����ɹ�
	gbool success = (char_stack.IsEmpty()) && (!m_tJsonValues.IsEmpty());
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

gvoid GJsonArray::Dispose()
{
	for (GList<GJsonValue*>::Iterator iter = m_tJsonValues.Begin();
		iter != m_tJsonValues.End(); iter++)
	{
		if (*iter)
		{
			delete *iter;
		}
	}
	m_tJsonValues.Clear();
}
