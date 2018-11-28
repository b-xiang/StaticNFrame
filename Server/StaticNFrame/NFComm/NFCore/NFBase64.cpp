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

// Base64�����������������ÿ��ȡ6 bit���ô�6 bit��ֵ(0-63)��Ϊ����ȥ��������Ӧ�ַ���������ÿ3���ֽڽ�����Ϊ4���ַ�(3��8 �� 4��6)������4���ַ�����'='��䡣
const char  NFBase64::EnBase64Tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Base64�������64���ɴ�ӡ�ַ���ֵ��Ϊ���������õ���ֵ����ΧΪ0-63�������������õ���������
// �����sizeΪ256���Ƿ��ַ���������ΪASCII 0
const char  NFBase64::DeBase64Tab[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	62,        // '+'
	0, 0, 0,
	63,        // '/'
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61,        // '0'-'9'
	0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,        // 'A'-'Z'
	0, 0, 0, 0, 0, 0,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,        // 'a'-'z'
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

std::string NFBase64::Encode(const std::string &data, bool bChangeLine/* = false*/)
{
	if (data.empty())
		return "";
	//��ԭʼ������Ϊa,����������ϻس����м�'/0',���ճ���Ϊ(a/3+1)*4+(a/3+1)*4*2/76+1,ԼΪ1.369*a+6
	char *pDst = NULL;
	int iBufSize = (int)(data.size()*1.4) + 6;
	pDst = new char[iBufSize];
	if (pDst == NULL)
		return "";
	int iDstLen = Encode((unsigned char*)data.c_str(), data.size(), pDst, bChangeLine);
	std::string ret(pDst, iDstLen);
	delete[] pDst;
	return ret;
}

std::string NFBase64::Decode(const std::string &data)
{
	if (data.empty())
		return "";
	unsigned char *pDst = NULL;
	pDst = new unsigned char[data.size()];
	if (pDst == NULL)
		return "";
	int iDstLen = Decode(data.c_str(), data.size(), pDst);
	std::string ret((char*)pDst, iDstLen);
	delete[] pDst;
	return ret;
}

int NFBase64::Encode(const unsigned char* pSrc, int nSrcLen, char* pDst, bool bChangeLine/* = false*/)
{
	unsigned char c1, c2, c3;
	int nDstLen = 0;
	int nLineLen = 0;
	int nDiv = nSrcLen / 3;
	int nMod = nSrcLen % 3;
	// ÿ��ȡ3���ֽڣ������4���ַ�
	for (int i = 0; i < nDiv; i++)
	{
		c1 = *pSrc++;
		c2 = *pSrc++;
		c3 = *pSrc++;

		*pDst++ = EnBase64Tab[c1 >> 2];
		*pDst++ = EnBase64Tab[((c1 << 4) | (c2 >> 4)) & 0x3f];
		*pDst++ = EnBase64Tab[((c2 << 2) | (c3 >> 6)) & 0x3f];
		*pDst++ = EnBase64Tab[c3 & 0x3f];
		nLineLen += 4;
		nDstLen += 4;
		// ���RFC��ÿ�г���76�ַ�ʱ��Ҫ��ӻس�����
		if (bChangeLine && nLineLen > 72)
		{
			*pDst++ = '\r';
			*pDst++ = '\n';
			nLineLen = 0;
			nDstLen += 2;
		}
	}
	// �������µ��ֽ�
	if (nMod == 1)
	{
		c1 = *pSrc++;
		*pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
		*pDst++ = EnBase64Tab[((c1 & 0x03) << 4)];
		*pDst++ = '=';
		*pDst++ = '=';
		nLineLen += 4;
		nDstLen += 4;
	}
	else if (nMod == 2)
	{
		c1 = *pSrc++;
		c2 = *pSrc++;
		*pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
		*pDst++ = EnBase64Tab[((c1 & 0x03) << 4) | ((c2 & 0xf0) >> 4)];
		*pDst++ = EnBase64Tab[((c2 & 0x0f) << 2)];
		*pDst++ = '=';
		nDstLen += 4;
	}
	// ����Ӹ�������
	*pDst = '\0';

	return nDstLen;
}


int  NFBase64::Decode(const char* pSrc, int nSrcLen, unsigned char* pDst)
{
	int nDstLen;            // ������ַ����� 
	int nValue;             // �����õ�������
	int i;
	i = 0;
	nDstLen = 0;

	// ȡ4���ַ������뵽һ�����������پ�����λ�õ�3���ֽ�
	while (i < nSrcLen)
	{
		// �����س�����    
		if (*pSrc != '\r' && *pSrc != '\n')
		{
			if (i + 4 > nSrcLen)                             //�������ַ������Ϸ�������ֹͣ���뷵��
				break;

			nValue = DeBase64Tab[int(*pSrc++)] << 18;
			nValue += DeBase64Tab[int(*pSrc++)] << 12;
			*pDst++ = (nValue & 0x00ff0000) >> 16;
			nDstLen++;
			if (*pSrc != '=')
			{
				nValue += DeBase64Tab[int(*pSrc++)] << 6;
				*pDst++ = (nValue & 0x0000ff00) >> 8;
				nDstLen++;
				if (*pSrc != '=')
				{
					nValue += DeBase64Tab[int(*pSrc++)];
					*pDst++ = nValue & 0x000000ff;
					nDstLen++;
				}
			}

			i += 4;
		}
		else
		{
			pSrc++;
			i++;
		}
	}
	// ����Ӹ�������
	*pDst = '\0';
	return nDstLen;
}
