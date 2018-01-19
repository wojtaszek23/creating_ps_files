/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#include "circles_ps.hpp"

bool Circle_ps :: get_info ( boost::property_tree::ptree pt , std::string item_path )
{
  try
  {
    this->x = pt.get<std::string>(item_path + ".x");
    this->y = pt.get<std::string>(item_path + ".y");
    this->r = pt.get<std::string>(item_path + ".r");
  }
  catch(...)
  {
    return false;
  };
    buffer.push_back("\n" + x + " " + y + " " + r + " DrawCircle" "\n");
    return true;
}
