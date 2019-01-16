/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#include "images_ps.hpp"


bool Image_ps :: convert_to_ps()
{
    size_t found = 0;
    size_t tmp_found = 0;
    while(std::string::npos != (tmp_found = this->image_name.find('/', tmp_found + 1)))
    {
        found = tmp_found;
    };
    std::string tmp_name = this->image_name.substr(found);

    found = 0;
    tmp_found = 0;
    while(std::string::npos != (tmp_found = tmp_name.find('.', tmp_found + 1)))
    {
        found = tmp_found;
    };
    
    tmp_name = tmp_name.substr(0, found);
    this->name_ps = "tmp/" + tmp_name + ".eps";
    std::string command = "convert " + image_name + " " + name_ps;
    system( command.c_str() );
    
    return true;
}

bool Image_ps :: move_ps_to_buffer()
{
    std::ifstream ps_in(name_ps);
    if(!ps_in)
    {
        return false;
    }

    do
    {
        buffer.push_back("");
    }
    while ( getline ( ps_in , buffer.back() ) );
    buffer.pop_back();

    ps_in.close();
    std::string command = "rm " + name_ps;
    system( command.c_str() );
    name_ps = "";

    return true;
}

bool Image_ps :: modify_buffer()
{
    while(buffer.empty() == false)
    {
        if(buffer.front() != "userdict begin")
        {
            buffer.pop_front();
            continue;
        }
        break;
    }
    if(buffer.empty() == false)
    {
        buffer.pop_front();
        buffer.pop_front();
        buffer.pop_front();
        buffer.pop_front();
        buffer.push_front(dest_width + " " + dest_height);
        buffer.push_front(x_pos + " " + y_pos);
        buffer.push_front("DisplayImage");
        buffer.push_front("userdict begin");
        return true;
    }
    return false;
}

bool Image_ps :: get_info ( boost::property_tree::ptree pt , std::string item_path )
{    // zmienić wszędzie nazwę "get_info" na "get_data"
  try
  {
    this->image_name = pt.get<std::string>(item_path + ".image_name");
    this->x_pos = pt.get<std::string>(item_path + ".x_pos");
    this->y_pos = pt.get<std::string>(item_path + ".y_pos");
    this->dest_width = pt.get<std::string>(item_path + ".dest_width");
    this->dest_height = pt.get<std::string>(item_path + ".dest_height");
  }
  catch(...)
  {
    return false;
  };

  if ( prepare_buffer() == false )
  {
    return false;
  }

  return true;
}

bool Image_ps :: prepare_buffer()
{
  if ( convert_to_ps() == false )
  {
    return false;
  };
  if ( move_ps_to_buffer() == false )
  {
    return false;
  };
  if ( modify_buffer() == false )
  {
    return false;
  };
  return true;
}
