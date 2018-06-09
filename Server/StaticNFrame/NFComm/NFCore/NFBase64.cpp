// -------------------------------------------------------------------------
//    @FileName         :    NFBase64.cpp
//    @Author           :    GaoYi
//    @Date             :    2017-08-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#include <stdlib.h>
#include "NFBase64.h"

static char Base64_code[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
* @Function: ������Base64������е�������ĳ���ַ�
*            0-63 : A-Z(25) a-z(51), 0-9(61), +(62), /(63)
* @Param:    unsigned char n
* @Return:   �ַ�
*/
char NFBase64::Base2Chr(unsigned char n)
{
	n &= 0x3F;
	if (n < 26)
	{
		return static_cast<char>(n + 'A');
	}
	else if (n < 52)
	{
		return static_cast<char>(n - 26 + 'a');
	}
	else if (n < 62)
	{
		return static_cast<char>(n - 52 + '0');
	}
	else if (n == 62)
	{
		return '+';
	}
	else
	{
		return '/';
	}
}

/**
* @Function: ���ĳ���ַ���Base64������е����
* @Param:    char c   �ַ�
* @Return:   ���ֵ
*/
unsigned char NFBase64::Chr2Base(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return static_cast<unsigned char>(c - 'A');
	}
	else if (c >= 'a' && c <= 'z')
	{
		return static_cast<unsigned char>(c - 'a' + 26);
	}
	else if (c >= '0' && c <= '9')
	{
		return static_cast<unsigned char>(c - '0' + 52);
	}
	else if (c == '+')
	{
		return 62;
	}
	else if (c == '/')
	{
		return 63;
	}
	else
	{
		return 64; //  ��Ч�ַ�
	}
}

bool NFBase64::Encode(const std::string& src, std::string* dst)
{
	if (0 == src.size() || NULL == dst)
	{
		return false;
	}

	dst->resize(Base64EncodeLen(static_cast<int>(src.size())));

	int c;

	unsigned char* p = reinterpret_cast<unsigned char*>(&(*dst)[0]);
	unsigned char* s = p;
	unsigned char* q = reinterpret_cast<unsigned char*>(const_cast<char*>(&src[0]));

	for (size_t i = 0; i < src.size();)
	{
		// �����ʱ�򣬶��ǰ�24bit����һ����λ����Ϊ3*8=4*6
		c = q[i++];
		c *= 256;
		if (i < src.size())
		{
			c += q[i];
		}
		i++;
		c *= 256;
		if (i < src.size())
		{
			c += q[i];
		}
		i++;

		// ÿ��ȡ6bit����һ��8bit��char����p��
		p[0] = Base64_code[(c & 0x00fc0000) >> 18];
		p[1] = Base64_code[(c & 0x0003f000) >> 12];
		p[2] = Base64_code[(c & 0x00000fc0) >> 6];
		p[3] = Base64_code[(c & 0x0000003f) >> 0];

		// �����Ǵ����β���
		if (i > src.size())
		{
			p[3] = '=';
		}

		if (i > src.size() + 1)
		{
			p[2] = '=';
		}

		p += 4; // ����������ָ����Ӧ���ƶ�
	}

	*p = 0; // ��Ұָ��
	dst->resize(p - s);

	return true;
}

bool NFBase64::Decode(const std::string& src, std::string* dst)
{
	if (0 == src.size() || NULL == dst)
	{
		return false;
	}

	dst->resize(Base64DecodeLen(static_cast<int>(src.size())));

	unsigned char* p = reinterpret_cast<unsigned char*>(&(*dst)[0]);
	unsigned char* q = p;
	unsigned char c;
	unsigned char t = 0;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == '=')
		{
			break;
		}
		do
		{
			if (src[i])
			{
				c = Chr2Base(src[i]);
			}
			else
			{
				c = 65; //  �ַ�������
			}
		}
		while (c == 64); //  ������Ч�ַ�����س���

		if (c == 65)
		{
			break;
		}
		switch (i % 4)
		{
		case 0:
			t = c << 2;
			break;
		case 1:
			*p = static_cast<unsigned char>(t | (c >> 4));
			p++;
			t = static_cast<unsigned char>(c << 4);
			break;
		case 2:
			*p = static_cast<unsigned char>(t | (c >> 2));
			p++;
			t = static_cast<unsigned char>(c << 6);
			break;
		case 3:
			*p = static_cast<unsigned char>(t | c);
			p++;
			break;
		default:
			break;
		}
	}

	dst->resize(static_cast<size_t>(p - q));

	return true;
}

int NFBase64::Base64EncodeLen(int n)
{
	return (n + 2) / 3 * 4 + 1;
}

int NFBase64::Base64DecodeLen(int n)
{
	return n / 4 * 3 + 2;
}

