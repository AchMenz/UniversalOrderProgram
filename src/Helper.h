#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>

class Helper
{
public:
   
   static std::string getSqlFromFile(char* file);
   static float toFloat(std::string stringFloat);

};

#endif // HELPER_HPP
