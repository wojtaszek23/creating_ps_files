/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#include "lines_ps.hpp"

bool Line_ps :: get_info ( boost::property_tree::ptree pt , std::string item_path )
{
  try
  {
    this->x1 = pt.get<std::string>(item_path + ".x1");
    this->y1 = pt.get<std::string>(item_path + ".y1");
    this->x2 = pt.get<std::string>(item_path + ".x2");
    this->y2 = pt.get<std::string>(item_path + ".y2");
    this->thickness = pt.get<std::string>(item_path + ".thickness");
  }
  catch(...)
  {
    return false;
  };
    buffer.push_back("\n" + x1 + " " + y1 + " " + x2 + " " + y2 + " " + thickness + " DrawLine" "\n");
    return true;
}
