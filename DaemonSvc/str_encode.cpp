#pragma once
#include <cassert>
#include <Windows.h>
#include <boost/smart_ptr.hpp>
#include "last_error.h"
#include "str_encode.h"


//do not use log
//because we use this function to log
std::wstring ansistr2widestr(const std::string& s)
{
    assert(!s.empty());
    std::wstring ws;

    do 
    {
        int need_ch_len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size(), NULL, 0);
        if (0 == need_ch_len)
        {
            print_last_err(CLastError(), TSTR("MultiByteToWideChar fail when query need size"));
            break;
        }

        boost::scoped_array<wchar_t> str_buf(new wchar_t[need_ch_len]);
        memset(str_buf.get(), 0, need_ch_len * sizeof(wchar_t));

        need_ch_len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size(), str_buf.get(), need_ch_len);
        if (0 == need_ch_len)
        {
            print_last_err(CLastError(), TSTR("MultiByteToWideChar fail"));
            break;
        }

        ws.append(str_buf.get(), need_ch_len);

    } while (false);

    return ws;
}

//do not use log
//because we use this function to log
std::string widestr2ansistr(const std::wstring& ws)
{
    assert(!ws.empty());
    std::string s;

    do 
    {
        int need_ch_len = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), ws.size(), NULL, 0, NULL, NULL);
        if (0 == need_ch_len)
        {
            print_last_err(CLastError(), TSTR("WideCharToMultiByte fail when query need size"));
            break;
        }

        boost::scoped_array<char> str_buf(new char[need_ch_len]);
        memset(str_buf.get(), 0, need_ch_len * sizeof(char));

        need_ch_len = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), ws.size(), str_buf.get(), need_ch_len, NULL, NULL);
        if (0 == need_ch_len)
        {
            print_last_err(CLastError(), TSTR("WideCharToMultiByte fail"));
            break;
        }

        s.append(str_buf.get(), need_ch_len);

    } while (false);

    return s;
}


