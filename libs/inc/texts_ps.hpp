/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#ifndef TEXTS_PS_HPP
#define TEXTS_PS_HPP

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <list>
#include "images_ps.hpp"


class Text_ps : public Image_ps
{
    public:
        Text_ps()
            {};
        Text_ps ( std::string name )
            :
            label ( name )
            {};
        virtual bool get_info ( boost::property_tree::ptree pt , std::string cur_string );
        
    protected:
        std::string label;
        std::string pointsize;
        std::string gravity;
        virtual bool convert_to_ps ();
};


#endif
