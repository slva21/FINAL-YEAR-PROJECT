#include "main.h"

//returns a string
char tmp_str[7]; // temporary variable used in convert function
char *convert_int16_to_str(int16_t i)
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.

    sprintf(tmp_str, "%6d", i);
    return tmp_str;
}
//this fuction is used to convert any double/float to a string with the specied lenth
String convert_double_to_string_with_len(double value, int len)
{

    int f = value;
    if (String(f).length() == 1 && String(value).indexOf("-") >= 0)
    {
        f--;
    }
    return String(value, (len - (String(f).length() + 1)));
}