/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#include "drawing_ps.hpp"


bool Drawing_ps :: add_to_ps(std::string ps_out_file_name)
{
    return move_buffer_to_ps(ps_out_file_name);
}

bool Drawing_ps :: move_buffer_to_ps(std::string ps_out_file_name)
{
    std::ofstream ps_out(ps_out_file_name, std::ofstream::app );
    if(!ps_out)
    {
        return false;
    }

    while(buffer.empty() == false)
    {
      try
      {
        ps_out << buffer.front() << "\n";
        buffer.pop_front();
      }
      catch(...)
      {
        return false;
      }
    }
    ps_out.close();
    return true;
}
