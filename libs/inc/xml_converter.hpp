/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#ifndef XML_CONVERTER_HPP
#define XML_CONVERTER_HPP


#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <vector>


struct Line_xml
{
  std::string x1;
  std::string y1;
  std::string x2;
  std::string y2;
  std::string thickness;
};

struct Table_xml
{
  std::string x1;
  std::string y1;
  std::string x2;
  std::string y2;
  std::string cols_number;
  std::string rows_number;
  std::string thickness;
};

struct Image_xml
{
  std::string variable_path;
  std::string image_name;
  std::string x_pos;
  std::string y_pos;
  std::string dest_width;
  std::string dest_height;
};

struct Text_xml
{
  std::string variable_path;
  std::string label;
  std::string pointsize;
  std::string x_pos;
  std::string y_pos;
  std::string dest_width;
  std::string dest_height;
  std::string gravity;
};

struct Rect_xml
{
  std::string x;
  std::string y;
  std::string width;
  std::string height;
};

struct Circle_xml
{
  std::string x;
  std::string y;
  std::string r;
};

struct Gen_xml
{
  std::string keyword_name;
  std::string keyword_path;
  int value;
  int items_number;
};

class Xml_converter
{
    public:
        boost::property_tree::ptree pt;
        std::string source_path;
        std::string layout_path;
        std::string out_path;

        bool get_items();        
        bool move_items_to_pt();
        bool move_pt_to_xml();
        void delete_tmp_xml();

        Xml_converter ( std::string new_source_path , std::string new_layout_path , std::string new_out_path , bool execute = true )
        :
        source_path ( new_source_path ),
        layout_path ( new_layout_path ),
        out_path ( new_out_path )
        {
            if ( execute == true )
            {        
                get_items();
                move_items_to_pt();
                move_pt_to_xml();
            }
        };

        
    private:
        std::vector <Line_xml> lines_xml;
        std::vector <Table_xml> tables_xml;
        std::vector <Image_xml> images_xml;
        std::vector <Text_xml> texts_xml;
        std::vector <Rect_xml> rects_xml;
        std::vector <Circle_xml> circles_xml;
        std::vector <Gen_xml> gens_xml;
};


#endif
