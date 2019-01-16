/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#include "texts_ps.hpp"


bool Text_ps :: get_info ( boost::property_tree::ptree pt , std::string item_path )
{    // zmienić wszędzie nazwę "get_info" na "get_data" albo "prepare_data" albo "prepare_buffer"
  try
  {
    this->label = pt.get<std::string>(item_path + ".label");
    this->pointsize = pt.get<std::string>(item_path + ".pointsize");
    this->x_pos = pt.get<std::string>(item_path + ".x_pos");
    this->y_pos = pt.get<std::string>(item_path + ".y_pos");
    this->dest_width = pt.get<std::string>(item_path + ".dest_width");
    this->dest_height = pt.get<std::string>(item_path + ".dest_height");
    this->gravity = pt.get<std::string>(item_path + ".gravity");
  }
  catch(...)
  {
    return false;
  };

  size_t found = 0;
  size_t tmp_found = 0;
  while(std::string::npos != (tmp_found = item_path.find('.', tmp_found + 1)))
  {
      found = tmp_found;
  };
  std::string tmp_name = item_path.substr(found+1);

  this->image_name = "tmp/" + tmp_name + ".bmp";
  //std::cout << std::endl<<this->image_name<<std::endl;

  std::string command = "convert -size " + this->dest_width + "x" + this->dest_height + " -background white -fill black -font Ubuntu -pointsize " + this->pointsize + " -gravity " + this->gravity + " " + "label:'" + this->label + "' " + this->image_name;
  
  //std::cout << std::endl<<command<<std::endl;

  system( command.c_str() );
    
  if ( prepare_buffer() == false )
  {
    return false;
  }

  return true;
}

bool Text_ps :: convert_to_ps()
{
  bool result = false;
  result = Image_ps::convert_to_ps();
  std::string command = "rm " + this->image_name;
  system ( command.c_str() );
  return result;
}
