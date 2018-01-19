/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#ifndef TABLES_PS_HPP
#define TABLES_PS_HPP

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <list>
#include "drawing_ps.hpp"

class Table_ps : public Drawing_ps
{
    public:
        virtual bool get_info ( boost::property_tree::ptree pt , std::string cur_string );
        
    private:
        std::string x1;
        std::string y1;
        std::string x2;
        std::string y2;
        std::string cols_number;
        std::string rows_number;
        std::string thickness;
};


#endif
