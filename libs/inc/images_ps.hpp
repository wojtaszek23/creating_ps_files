/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#ifndef IMAGES_PS_HPP
#define IMAGES_PS_HPP

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <fstream>
#include <list>
#include "drawing_ps.hpp"


class Image_ps : public Drawing_ps
{
    public:
        Image_ps()
            {};
        Image_ps ( std::string name )
            :
            image_name ( name )
            {};
        virtual bool get_info ( boost::property_tree::ptree pt , std::string cur_string );
        //virtual bool add_to_ps ( std::string ps_out_file_name );
        
    protected:
        std::string image_name;
        std::string name_ps;
        std::string x_pos;
        std::string y_pos;
        std::string dest_width;
        std::string dest_height;

        bool prepare_buffer();
        virtual bool convert_to_ps ();

    private:
        bool modify_buffer ();
        bool move_ps_to_buffer ();
};


#endif
