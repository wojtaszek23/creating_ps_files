/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#include "rects_ps.hpp"

bool Rect_ps :: get_info ( boost::property_tree::ptree pt , std::string item_path )
{
  try
  {
    this->x = pt.get<std::string>(item_path + ".x");
    this->y = pt.get<std::string>(item_path + ".y");
    this->width = pt.get<std::string>(item_path + ".width");
    this->height = pt.get<std::string>(item_path + ".height");
  }
  catch(...)
  {
    return false;
  };
    buffer.push_back("\n" + x + " " + y + " " + width + " " + height + " DrawRectangle" "\n");
    return true;
}
