/*--------------------------------------------------------------------------------
    Header-only module for string helper functions.
--------------------------------------------------------------------------------*/
#ifndef STRING_UTILS
#define STRING_UTILS
#include <string>


inline std::string indents(int num_indents)
{
    return std::string(4*num_indents, ' ');
}


#endif // STRING_UTILS
