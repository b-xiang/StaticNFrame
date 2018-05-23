// -------------------------------------------------------------------------
//    @FileName         :    NFBase64.h
//    @Author           :    GaoYi
//    @Date             :    2017-08-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <string>

#include "NFPlatform.h"

class _NFExport NFBase64
{
public:
	/**
	* @brief ���캯��.
	*
	*/
	NFBase64() {}

	/**
	* @brief ��������.
	*/
	virtual ~NFBase64() {}

	/**
	* @brief Base64λ����
	*
	* @param src  Ҫ��������ݣ�����Ϊ��
	* @param dst  ���������ݣ������ǿ�ָ��
	* @return     �����Ƿ�ɹ�
	*/
	static bool Encode(const std::string& src, std::string* dst);

	/**
	* @brief Base64λ����
	*
	* @param data  Ҫ��������ݣ�����Ϊ��
	* @param size  ���������ݣ������ǿ�ָ��
	* @return      �����Ƿ�ɹ�
	*/
	static bool Decode(const std::string& src, std::string* dst);

private:
	/**
	* @brief ������Base64������е�������ĳ���ַ�
	*
	* @param n  ��Base64������е����
	* @return   ��Base64������е���Ŷ�Ӧ��ĳ���ַ�
	*/
	static inline char Base2Chr(unsigned char n);

	/**
	* @brief ���ĳ���ַ���Base64������е����
	*
	* @param c  �����ַ�
	* @return   �ַ���Base64������е����
	*/
	static inline unsigned char Chr2Base(char c);

	/**
	* @brief ��ñ��������ݳ���
	*
	* @param n  ����ǰ���ݵĳ���
	* @return   ��������ݵĳ���
	*/
	inline static int Base64EncodeLen(int n);

	/**
	* @brief ��ý��������ݳ���
	*
	* @param n  ����ǰ���ݵĳ���
	* @return   ��������ݵĳ���
	*/
	inline static int Base64DecodeLen(int n);
};
