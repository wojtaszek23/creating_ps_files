/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#ifndef DRAWING_PS_HPP
#define DRAWING_PS_HPP

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <list>


class Drawing_ps
{
    public:
        virtual bool get_info ( boost::property_tree::ptree pt , std::string cur_string )=0;
        virtual bool add_to_ps ( std::string ps_out_file_name );
    protected:
        bool move_buffer_to_ps ( std::string ps_out_file_name );
        std::list <std::string> buffer;
};


#endif
