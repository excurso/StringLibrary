/******************************************************************************
StringLibrary - A C++ library extending the functionality of the STL strings
Copyright (C) 2019-2020 Waldemar Zimpel <hspp@utilizer.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*******************************************************************************/


#ifndef STRING_H
#define STRING_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define DECL_EXPORT __declspec(dllexport)
    #define DECL_IMPORT __declspec(dllimport)
    #define NEWLINE "\r\n"
    #define DBLNEWLINE "\r\n\r\n"
#else
    #define DECL_EXPORT __attribute__((visibility("default")))
    #define DECL_IMPORT __attribute__((visibility("default")))
    #define NEWLINE "\n"
    #define DBLNEWLINE "\n\n"
#endif

#ifdef STRING_LIBRARY
#  define STRING_EXPORT DECL_EXPORT
#else
#  define STRING_EXPORT DECL_IMPORT
#endif

#include "../../ContainerLibrary/src/DataContainer.h"
#include <algorithm>
#include <codecvt>
#include <ctgmath>
#include <locale>

using namespace std;

class STRING_EXPORT String : private string
{
public:
    explicit
    String              (const string &s),
    String              (const string *&s),
    String              (const char chr);

    static bool
    isOneOfChars        (char c, const string &allowed),
    isOneOfChars        (const string &allowed, string::iterator itr),
    contains            (const string &content, const char c),
    contains            (const string &content, const DataContainer<string> &string_list,
                         const bool case_insensitive = true),
    startsWith          (const string &content, const string &candidate),
    startsWith          (const string &content, const initializer_list<string> &candidates),
    endsWith            (const string &content, const string &candidate),
    endsWith            (const string &content, const initializer_list<string> &candidates);

    static inline bool
    containsOneOfChars  (const string &content, const string &allowed_chars),
    containsWhitepace   (const string &content),
    containsWhitepaceOnly(const string &content);

    static string
    repeatChar          (const char chr, const uint64_t num),
    repeat              (const string &str, const uint64_t num),
    replace             (const string &content, const string &search, const string &replace_with,
                         const bool case_sensitive = true),
    replace             (const string &content, const string::const_iterator &begin,
                         const string::const_iterator &end, const string &new_value),
    toLower             (string content),
    toUpper             (string content),

    toLowerUtf8         (const string &content),
    toUpperUtf8         (const string &content);

    static DataContainer<string>
    split               (const string &content, const string &delimiter),
    splitByWhiteSpace   (const string &content);

    static string
    ltrim               (const string &content),
    rtrim               (const string &content),
    trim                (const string &content),
    collapseWhiteSpace  (const string &content);

    static string
    numberFormat        (double number, const streamsize precition);

    static size_t
    lastIndexOf(const string &content, const char c) noexcept,
    lastIndexOf(const string &content, const initializer_list<const char> &candidates) noexcept;
};

/*static*/ inline bool
String::
containsOneOfChars(const string &content, const string &allowed_chars)
{
    return std::find_first_of(content.begin(), content.end(), allowed_chars.begin(),
                              allowed_chars.end()) != content.end();
}

/*static*/ inline bool
String::
containsWhitepace(const string &content)
{
    return any_of(content.begin(), content.end(), ::isspace);
}

/*static*/ inline bool
String::
containsWhitepaceOnly(const string &content)
{
    return all_of(content.begin(), content.end(), ::isspace);
}

#endif // STRING_H
