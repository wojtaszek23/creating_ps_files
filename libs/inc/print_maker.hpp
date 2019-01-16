/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#ifndef PRINT_MAKER_HPP
#define PRINT_MAKER_HPP

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <list>
#include <memory>
#include "drawing_ps.hpp"
#include "lines_ps.hpp"
#include "tables_ps.hpp"
#include "images_ps.hpp"
#include "texts_ps.hpp"
#include "rects_ps.hpp"
#include "circles_ps.hpp"


class Print_maker
{
  public:
    bool create_tmp_ps ( std::string ps_template , std::string ps_out_file_name );
    bool write_to_ps ( std::string xml_path , std::string group_path , std::string type_name , std::string ps_out_file_name );

  private:
    std::list <std::shared_ptr<Drawing_ps>> items;

    bool get_lines_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
    bool get_tables_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
    bool get_images_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
    bool get_texts_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
    bool get_rects_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
    bool get_circles_info ( boost::property_tree::ptree pt, std::string group_path, int num_items );
};

#endif
