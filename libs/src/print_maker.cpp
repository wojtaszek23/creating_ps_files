/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#include "print_maker.hpp"


bool Print_maker :: create_tmp_ps( std::string ps_template , std::string ps_out_file_name )
{
    std::string command = "cp " + ps_template + " " + ps_out_file_name;
    system ( command.c_str() );
}

bool Print_maker :: write_to_ps(std::string xml_path, std::string group_path, std::string type_name, std::string ps_out_file_name)
{
    boost::property_tree::ptree pt;
    read_xml ( xml_path, pt );
    int num_items = pt.get<int>( group_path + ".number" );
    
             //jak będzie czas, zmienić wywoływanie tych wszystkich funkcji na przypisanie wskaźnika do funkcji i wywoływanie funkcji z pod tego wskaźnika w pętli
    if( type_name == "line" )
        get_lines_info(pt, group_path, num_items);
    else if( type_name == "table" )
        get_tables_info(pt, group_path, num_items);
    else if( type_name == "image" )
        get_images_info(pt, group_path, num_items);
    else if( type_name == "text" )
        get_texts_info(pt, group_path, num_items);
    else if( type_name == "rect" )
        get_rects_info(pt, group_path, num_items);
    else if( type_name == "circle" )
        get_circles_info(pt, group_path, num_items);
    while(items.empty() == false)
    {
        items.front()->add_to_ps(ps_out_file_name);
        items.pop_front();
    }
}

bool Print_maker :: get_images_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".image_" + std::to_string(i+1);
        items.push_back (std::make_shared<Image_ps>(Image_ps()));

        if ( items.back()->get_info (pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}

bool Print_maker :: get_texts_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".text_" + std::to_string(i+1);
        items.push_back (std::make_shared<Text_ps>(Text_ps()));

        if ( items.back()->get_info ( pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}

bool Print_maker :: get_lines_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".line_" + std::to_string(i+1);
        items.push_back (std::make_shared<Line_ps>(Line_ps()));

        if ( items.back()->get_info ( pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}

bool Print_maker :: get_tables_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".table_" + std::to_string(i+1);
        items.push_back (std::make_shared<Table_ps>(Table_ps()));

        if ( items.back()->get_info ( pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}

bool Print_maker :: get_rects_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".rect_" + std::to_string( i + 1 );
        items.push_back (std::make_shared<Rect_ps>(Rect_ps()));

        if ( items.back()->get_info ( pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}

bool Print_maker :: get_circles_info ( boost::property_tree::ptree pt, std::string group_path, int num_items )
{
    std::string item_path;
    for(int i = 0; i < num_items ; i++)
    {
        item_path = group_path + ".circle_" + std::to_string(i+1);
        items.push_back (std::make_shared<Circle_ps>(Circle_ps()));

        if ( items.back()->get_info ( pt , item_path ) == false )
        {
            items.pop_back();
        }
    }
    if ( num_items == items.size() )
    {
        return true;
    }
    return false;
}
