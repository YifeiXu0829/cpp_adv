#ifndef FORMAT_H
#define FORMAT_H
#include<string_view>
#include<string>
#include<sstream>
using std::string_view;
using std::string;
using std::ostringstream;

namespace mpcs {
string format(string_view fmt)
{
    return string{ fmt };
}

template<typename T, typename... Args>
string
format(string_view fmt, const T& value, const Args... args) {
    ostringstream result;
    for (unsigned i = 0; i < fmt.size(); i++) {
        if (fmt[i] == '{' && fmt[++i] == '}') {
            // ignore the character that follows the ‘%’: we already know the type!
            result << value;
            return result.str() + format(fmt.substr(i+1), args...);
        }
        result << fmt[i];
    }
    return result.str();
}

}
#endif