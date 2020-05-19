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


#include "String.h"

String::
String(const string &s) : string(s) {}

String::
String(const string *&s) : string(*s) {}

String::
String(const char chr) : string(&chr) {}

/*static*/ bool
String::
contains(const string &content, const DataContainer<string> &string_list, const bool case_insensitive)
{
    if (case_insensitive)
        for (const auto &term : string_list) {
            if (search(content.begin(), content.end(), term.begin(), term.end(),
            [](const char a, const char b) {
                  return tolower(a) == tolower(b);
            }) != content.end()) return true;
        }
    else
        for (const auto &term : string_list)
            if (content.find(term) != npos)
                return true;

    return false;
}

/*static*/ bool
String::
contains(const string &content, const char c)
{
    return content.find(c) != npos;
}

/*static*/ bool
String::
startsWith(const string &content, const string &candidate)
{
    if (content.length() < candidate.length())
        return false;

    for (size_t i = 0; i != candidate.length(); ++i)
        if (content.at(i) != candidate.at(i))
            return false;

    return true;
}

/*static*/ bool
String::
startsWith(const string &content, const initializer_list<string> &candidates)
{
    for (const auto &candidate : candidates)
        if (startsWith(content, candidate))
            return true;

    return false;
}

/*static*/ bool
String::
endsWith(const string &content, const string &candidate)
{
    if (content.length() < candidate.length())
        return false;

    auto
    begin = candidate.begin(),
    itr1 = candidate.end()-1,
    itr2 = content.end()-1;

    for (; itr1 != begin; --itr1, --itr2)
        if (*itr1 != *itr2)
            return false;

    return true;
}

/*static*/ bool
String::
endsWith(const string &content, const initializer_list<string> &candidates)
{
    for (const auto &candidate : candidates)
        if (endsWith(content, candidate))
            return true;

    return false;
}

/*static*/ DataContainer<string>
String::
split(const string &content, const string &delimiter)
{
    if (content.empty()) return DataContainer<string>();

    DataContainer<string> str_list;

    auto itr = content.begin();
    while (bool(isspace(*itr))) ++itr;

    for (auto begin = itr; begin != content.end(); ++itr) {
        if (*itr == delimiter[0]) {
            str_list.emplace_back(string(begin, itr));
            do ++itr; while (bool(isspace(*itr)));
            begin = itr;
            continue;
        }

        if (itr == content.end()) {
            str_list.emplace_back(string(begin, itr));
            break;
        }
    }

    return str_list;
}

/*static*/ DataContainer<string>
String::
splitByWhiteSpace(const string &content)
{
    if (content.empty() || containsWhitepaceOnly(content)) return DataContainer<string>();

    DataContainer<string> str_list;

    auto itr = content.begin();
    while (bool(isspace(*itr))) ++itr;

    for (auto begin = itr; begin != content.end(); ++itr) {
        if (bool(isspace(*itr))) {
            str_list.emplace_back(string(begin, itr));
            do ++itr; while (bool(isspace(*itr)));
            begin = itr;
            continue;
        }

        if (itr == content.end()) {
            str_list.emplace_back(string(begin, itr));
            break;
        }
    }

    return str_list;
}

/*static*/ string
String::
ltrim(const string &content)
{
    string trimmed_content = content;
    while (bool(isspace(trimmed_content.front()))) trimmed_content.erase(trimmed_content.begin());
    return trimmed_content;
}

/*static*/ string
String::
rtrim(const string &content)
{
    string trimmed_content = content;
    while (bool(isspace(trimmed_content.back()))) trimmed_content.pop_back();
    return trimmed_content;
}

/*static*/ string
String::
trim(const string &content)
{
    return rtrim(ltrim(content));
}

/*static*/ string
String::
collapseWhiteSpace(const string &content)
{
    string str;

    for (auto itr = content.begin(); itr != content.end(); ++itr) {
        if (isspace(*itr)) {
            str += ' ';

            while (isspace(*next(itr))) ++itr;

            continue;
        }

        str += *itr;
    }

    return str;
}

/*static*/ bool
String::
isOneOfChars(char c, const string &allowed)
{
    return std::find(allowed.begin(), allowed.end(), c) != allowed.end();
}

/*static*/ bool
String::
isOneOfChars(const string &allowed, String::iterator itr)
{
    return std::find(allowed.begin(), allowed.end(), *itr) != allowed.end();
}

/*static*/ string
String::
repeatChar(const char chr, const uint64_t num)
{
    string result;

    for (uint64_t i = 0; i != num; ++i)
        result += chr;

    return result;
}

/*static*/ string
String::
repeat(const string &str, const uint64_t num)
{
    string result;

    for (uint64_t i = 0; i != num; ++i)
        result += str;

    return result;
}

/*static*/ string
String::
replace(const string &content, const string &search, const string &replace_with, const bool case_sensitive)
{
    if (content.empty() || search.empty())
        return content;

    string new_content;
    auto itr_begin = content.begin();
    auto itr_end = content.begin();

    const auto case_sensitivity = !case_sensitive ? [](const char a, const char b) -> bool {
        return tolower(a) == tolower(b);
    } : [](const char a, const char b) -> bool {return a == b;};

    while ((itr_end = std::search(itr_begin, content.end(), search.begin(), search.end(), case_sensitivity)) != content.end()) {
        new_content += string(itr_begin, itr_end);
        new_content += replace_with;

        itr_begin = itr_end+static_cast<difference_type>(search.length());
    }

    if (itr_end == content.end() && itr_begin != itr_end)
        new_content += string(itr_begin, itr_end);

    return new_content;
}

/*static*/ string
String::
replace(const string &content, const string::const_iterator &begin, const string::const_iterator &end, const string &new_value)
{
    string new_content(content);

    new_content.replace(begin, end, new_value);

    return new_content;
}

/*static*/ string
String::
numberFormat(double number, const streamsize precition)
{
    const double prec = pow(10, precition);
    number = round(number * prec) / prec;

    ostringstream ostrstr;
    ostrstr.setf(ostringstream::fixed);
    ostrstr.precision(precition);
    ostrstr << number;

    return ostrstr.str();
}

/*static*/ string
String::
toLower(string content)
{
    if (!all_of(content.begin(), content.end(), ::islower))
        std::transform(content.begin(), content.end(), content.begin(), ::tolower);

    return content;
}

/*static*/ string
String::
toUpper(string content)
{
    if (!all_of(content.begin(), content.end(), ::islower))
        std::transform(content.begin(), content.end(), content.begin(), ::toupper);

    return content;
}

/*static*/ string
String::
toLowerUtf8(const string &content)
{
    const locale utf8("en_US.UTF-8");

    wstring_convert<codecvt_utf8<wchar_t> > conv;
    wstring wstr = conv.from_bytes(content);

    for (wchar_t &wchr : wstr)
    {
        wchr = std::tolower(wchr, utf8);
    }

    return conv.to_bytes(wstr);
}

/*static*/ string
String::
toUpperUtf8(const string &content)
{
    const locale utf8("en_US.UTF-8");

    wstring_convert<codecvt_utf8<wchar_t>> conv;
    wstring wstr = conv.from_bytes(content);

    for (wchar_t &wchr : wstr) {
        wchr = std::toupper(wchr, utf8);
    }

    return conv.to_bytes(wstr);
}

/*static*/ size_t
String::
lastIndexOf(const string &content, const char c) noexcept
{
    return content.rfind(c);
}

/*static*/ size_t
String::
lastIndexOf(const string &content, const initializer_list<const char> &candidates) noexcept
{
    for (size_t i = content.size()-1; i != 0; --i) {
        for (const auto c : candidates)
            if (content.at(i) == c)
                return i;
    }

    for (const auto c : candidates)
        if (content.at(0) == c)
            return 0;

    return npos;
}
