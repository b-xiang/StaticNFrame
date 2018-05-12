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
    NFBase64() {}
    virtual ~NFBase64() {}

    static bool Encode(const std::string& src, std::string* dst);

    static bool Decode(const std::string& src, std::string* dst);

private:
    // ������Base64������е�������ĳ���ַ�
    static inline char Base2Chr(unsigned char n);

    // ���ĳ���ַ���Base64������е����
    static inline unsigned char Chr2Base(char c);

    inline static int Base64EncodeLen(int n);
    inline static int Base64DecodeLen(int n);
};
