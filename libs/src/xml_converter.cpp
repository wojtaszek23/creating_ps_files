/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be copied or duplicated 
   in any form, in whole or in part, without prior written 
   permission from Uni-Trol.

*/


#include "xml_converter.hpp"


bool Xml_converter :: get_items()
{
  boost::property_tree::ptree pt_layout;
  boost::property_tree::ptree pt_source;
  read_xml ( layout_path , pt_layout );
  read_xml ( source_path , pt_source );
  int texts_number = 0;
  int images_number = 0;
  int lines_number = 0;
  int tables_number = 0;
  int gens_number = 0;
  try
  {
    texts_number = pt_layout.get<int>("layout.texts.number");
  }catch(...){};
  try
  {
    images_number = pt_layout.get<int>("layout.images.number");
  }catch(...){};
  try
  {
    lines_number = pt_layout.get<int>("layout.lines.number");
  }catch(...){};
  try
  {
    tables_number = pt_layout.get<int>("layout.tables.number");
  }catch(...){};
  try
  {
    gens_number = pt_layout.get<int>("layout.gens.keywords.number");
  }catch(...){};

  for ( int i = 0 ; i < lines_number ; i++ )
  {
    Line_xml line;
    try
    {
      line.x1 = pt_layout.get <std::string> ( "layout.lines.line_" + std::to_string ( i + 1 ) + ".x1" );
      line.y1 = pt_layout.get <std::string> ( "layout.lines.line_" + std::to_string ( i + 1 ) + ".y1" );
      line.x2 = pt_layout.get <std::string> ( "layout.lines.line_" + std::to_string ( i + 1 ) + ".x2" );
      line.y2 = pt_layout.get <std::string> ( "layout.lines.line_" + std::to_string ( i + 1 ) + ".y2" );
      line.thickness = pt_layout.get <std::string> ( "layout.lines.line_" + std::to_string ( i + 1 ) + ".thickness" );
    }
    catch (...)
    {
      continue;
    }
    lines_xml.push_back ( line );
  } 


  for ( int i = 0 ; i < tables_number ; i++ )
  {
    Table_xml table;
    try
    {
      table.x1 = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".x1" );
      table.y1 = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".y1" );
      table.x2 = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".x2" );
      table.y2 = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".y2" );
      table.cols_number = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".cols_number" );
      table.rows_number = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".rows_number" );
      table.thickness = pt_layout.get <std::string> ( "layout.tables.table_" + std::to_string ( i + 1 ) + ".thickness" );
    }
    catch (...)
    {
      continue;
    }
    tables_xml.push_back ( table );
  }


  for ( int i = 0 ; i < images_number ; i++ )
  {
    Image_xml image;
    try
    {
      image.variable_path = pt_layout.get <std::string> ( "layout.images.image_" + std::to_string ( i + 1 ) + ".variable_path" );

      image.x_pos = pt_layout.get <std::string> ( "layout.images.image_" + std::to_string ( i + 1 ) + ".x_pos" );
      image.y_pos = pt_layout.get <std::string> ( "layout.images.image_" + std::to_string ( i + 1 ) + ".y_pos" );
      image.dest_width = pt_layout.get <std::string> ( "layout.images.image_" + std::to_string ( i + 1 ) + ".dest_width" );
      image.dest_height = pt_layout.get <std::string> ( "layout.images.image_" + std::to_string ( i + 1 ) + ".dest_height" );

      image.image_name = pt_source.get <std::string> ( image.variable_path );
    }
    catch (...)
    {
      continue;
    }
    images_xml.push_back ( image );
  }


  for ( int i = 0 ; i < texts_number ; i++ )
  {
    Text_xml text;
    try
    {
      text.variable_path = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".variable_path" );

      text.pointsize = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".pointsize" );
      text.x_pos = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".x_pos" );
      text.y_pos = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".y_pos" );
      text.dest_width = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".dest_width" );
      text.dest_height = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".dest_height" );
      text.gravity = pt_layout.get <std::string> ( "layout.texts.text_" + std::to_string ( i + 1 ) + ".gravity" );

      text.label = pt_source.get <std::string> ( text.variable_path );
    }
    catch (...)
    {
      continue;
    }
    texts_xml.push_back ( text );
  }  

  for ( int i = 0 ; i < gens_number ; i++ )
  {
    Gen_xml gen_xml;
    try
    {
      gen_xml.keyword_name = pt_layout.get <std::string> ( "layout.gens.keywords.keyword_" + std::to_string ( i + 1 ) + ".name" );
      gen_xml.keyword_path = pt_layout.get <std::string> ( "layout.gens.keywords.keyword_" + std::to_string ( i + 1 ) + ".path" );
      gen_xml.value = pt_source.get <int> ( gen_xml.keyword_path );
      gen_xml.items_number = pt_layout.get <int> ( "layout.gens.keywords.keyword_" + std::to_string ( i + 1 ) + ".items_number" );

      for ( int j = 0 ; j < gen_xml.items_number ; j++ )
      {
        std::string tmp_str = "layout.gens." + gen_xml.keyword_name + "_" + std::to_string ( gen_xml.value );
        std::string drawing_type = pt_layout.get <std::string> ( tmp_str  + ".item_" + std::to_string ( j + 1 ) + ".drawing_type" );

        if ( drawing_type == "line" )
        {
          Line_xml line;
          line.x1 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x1" );
          line.y1 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y1" );
          line.x2 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x2" );
          line.y2 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y2" );
          line.thickness = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".thickness" );
          lines_xml.push_back(line);
        }

        else if ( drawing_type == "table" )
        {
          Table_xml table;
          table.x1 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x1" );
          table.y1 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y1" );
          table.x2 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x2" );
          table.y2 = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y2" );
          table.cols_number = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".cols_number" );
          table.rows_number = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".rows_number" );
          table.thickness = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".thickness" );
          tables_xml.push_back(table);
        }

        else if ( drawing_type == "image" )
        {
          Image_xml image;
          image.image_name = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".image_name" );
          image.x_pos = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x_pos" );
          image.y_pos = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y_pos" );
          image.dest_width = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".dest_width" );
          image.dest_height = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".dest_height" );
          images_xml.push_back(image);
        }

        else if ( drawing_type == "text" )
        {
          Text_xml text;
          text.label = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".label" );
          text.pointsize = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".pointsize" );
          text.x_pos = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x_pos" );
          text.y_pos = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y_pos" );
          text.dest_width = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".dest_width" );
          text.dest_height = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".dest_height" );
          text.gravity = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".gravity" );
          texts_xml.push_back(text);
        }

        else if ( drawing_type == "rect" )
        {
          Rect_xml rect;
          rect.x = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x" );
          rect.y = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y" );
          rect.width = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".width" );
          rect.height = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".height" );
          rects_xml.push_back(rect);
        }

        else if ( drawing_type == "circle" )
        {
          Circle_xml circle;
          circle.x = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".x" );
          circle.y = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".y" );
          circle.r = pt_layout.get <std::string> ( tmp_str + ".item_" + std::to_string ( j + 1 ) + ".r" );
          circles_xml.push_back(circle);
        }
      }
    } catch (...) { continue; };
  }

  return true;
}


bool Xml_converter :: move_items_to_pt()
{  
  boost::property_tree::ptree pt_layout;

  boost::property_tree::ptree pt_lines;
  boost::property_tree::ptree pt_tables;
  boost::property_tree::ptree pt_images;
  boost::property_tree::ptree pt_texts;
  boost::property_tree::ptree pt_rects;
  boost::property_tree::ptree pt_circles;

  

  for ( unsigned int i = 0 ; i < lines_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "line_" + std::to_string ( i + 1 );    

    pt_tmp.put ( "x1" , lines_xml[i].x1 );
    pt_item.add_child ( string_tmp + ".x1" , pt_tmp.get_child ( "x1" ) );

    pt_tmp.put ( "y1" , lines_xml[i].y1 );
    pt_item.add_child ( string_tmp + ".y1" , pt_tmp.get_child ( "y1" ) );

    pt_tmp.put ( "x2" , lines_xml[i].x2 );
    pt_item.add_child ( string_tmp + ".x2" , pt_tmp.get_child ( "x2" ) );

    pt_tmp.put ( "y2" , lines_xml[i].y2 );
    pt_item.add_child ( string_tmp + ".y2" , pt_tmp.get_child ( "y2" ) );

    pt_tmp.put ( "thickness" , lines_xml[i].thickness );
    pt_item.add_child ( string_tmp + ".thickness" , pt_tmp.get_child ( "thickness" ) );

    pt_lines.add_child ( "lines." + string_tmp , pt_item.get_child ( string_tmp ) );
  }


  for ( unsigned int i = 0 ; i < tables_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "table_" + std::to_string ( i + 1 );    

    pt_tmp.put ( "x1" , tables_xml[i].x1 );
    pt_item.add_child ( string_tmp + ".x1" , pt_tmp.get_child ( "x1" ) );

    pt_tmp.put ( "y1" , tables_xml[i].y1 );
    pt_item.add_child ( string_tmp + ".y1" , pt_tmp.get_child ( "y1" ) );

    pt_tmp.put ( "x2" , tables_xml[i].x2 );
    pt_item.add_child ( string_tmp + ".x2" , pt_tmp.get_child ( "x2" ) );

    pt_tmp.put ( "y2" , tables_xml[i].y2 );
    pt_item.add_child ( string_tmp + ".y2" , pt_tmp.get_child ( "y2" ) );

    pt_tmp.put ( "cols_number" , tables_xml[i].cols_number );
    pt_item.add_child ( string_tmp + ".cols_number" , pt_tmp.get_child ( "cols_number" ) );

    pt_tmp.put ( "rows_number" , tables_xml[i].rows_number );
    pt_item.add_child ( string_tmp + ".rows_number" , pt_tmp.get_child ( "rows_number" ) );

    pt_tmp.put ( "thickness" , tables_xml[i].thickness );
    pt_item.add_child ( string_tmp + ".thickness" , pt_tmp.get_child ( "thickness" ) );

    pt_tables.add_child ( "tables." + string_tmp , pt_item.get_child ( string_tmp ) );
  }


  for ( unsigned int i = 0 ; i < images_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "image_" + std::to_string ( i + 1 ); 

    pt_tmp.put ( "image_name" , images_xml[i].image_name );
    pt_item.add_child ( string_tmp + ".image_name" , pt_tmp.get_child ( "image_name" ) );   

    pt_tmp.put ( "x_pos" , images_xml[i].x_pos );
    pt_item.add_child ( string_tmp + ".x_pos" , pt_tmp.get_child ( "x_pos" ) );

    pt_tmp.put ( "y_pos" , images_xml[i].y_pos );
    pt_item.add_child ( string_tmp + ".y_pos" , pt_tmp.get_child ( "y_pos" ) );

    pt_tmp.put ( "dest_width" , images_xml[i].dest_width );
    pt_item.add_child ( string_tmp + ".dest_width" , pt_tmp.get_child ( "dest_width" ) );

    pt_tmp.put ( "dest_height" , images_xml[i].dest_height );
    pt_item.add_child ( string_tmp + ".dest_height" , pt_tmp.get_child ( "dest_height" ) );

    pt_images.add_child ( "images." + string_tmp , pt_item.get_child ( string_tmp ) );
  }


  for ( unsigned int i = 0 ; i < texts_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "text_" + std::to_string ( i + 1 ); 

    pt_tmp.put ( "label" , texts_xml[i].label );
    pt_item.add_child ( string_tmp + ".label" , pt_tmp.get_child ( "label" ) );

    pt_tmp.put ( "pointsize" , texts_xml[i].pointsize );
    pt_item.add_child ( string_tmp + ".pointsize" , pt_tmp.get_child ( "pointsize" ) );   

    pt_tmp.put ( "x_pos" , texts_xml[i].x_pos );
    pt_item.add_child ( string_tmp + ".x_pos" , pt_tmp.get_child ( "x_pos" ) );

    pt_tmp.put ( "y_pos" , texts_xml[i].y_pos );
    pt_item.add_child ( string_tmp + ".y_pos" , pt_tmp.get_child ( "y_pos" ) );

    pt_tmp.put ( "dest_width" , texts_xml[i].dest_width );
    pt_item.add_child ( string_tmp + ".dest_width" , pt_tmp.get_child ( "dest_width" ) );

    pt_tmp.put ( "dest_height" , texts_xml[i].dest_height );
    pt_item.add_child ( string_tmp + ".dest_height" , pt_tmp.get_child ( "dest_height" ) );

    pt_tmp.put ( "gravity" , texts_xml[i].gravity );
    pt_item.add_child ( string_tmp + ".gravity" , pt_tmp.get_child ( "gravity" ) );

    pt_texts.add_child ( "texts." + string_tmp , pt_item.get_child ( string_tmp ) );
  }


  for ( unsigned int i = 0 ; i < rects_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "rect_" + std::to_string ( i + 1 );    

    pt_tmp.put ( "x" , rects_xml[i].x );
    pt_item.add_child ( string_tmp + ".x" , pt_tmp.get_child ( "x" ) );

    pt_tmp.put ( "y" , rects_xml[i].y );
    pt_item.add_child ( string_tmp + ".y" , pt_tmp.get_child ( "y" ) );

    pt_tmp.put ( "width" , rects_xml[i].width );
    pt_item.add_child ( string_tmp + ".width" , pt_tmp.get_child ( "width" ) );

    pt_tmp.put ( "height" , rects_xml[i].height );
    pt_item.add_child ( string_tmp + ".height" , pt_tmp.get_child ( "height" ) );

    pt_rects.add_child ( "rects." + string_tmp , pt_item.get_child ( string_tmp ) );
  }


  for ( unsigned int i = 0 ; i < circles_xml.size() ; i++ )
  {
    boost::property_tree::ptree pt_item;
    boost::property_tree::ptree pt_tmp;
    std::string string_tmp = "circle_" + std::to_string ( i + 1 );    

    pt_tmp.put ( "x" , circles_xml[i].x );
    pt_item.add_child ( string_tmp + ".x" , pt_tmp.get_child ( "x" ) );

    pt_tmp.put ( "y" , circles_xml[i].y );
    pt_item.add_child ( string_tmp + ".y" , pt_tmp.get_child ( "y" ) );

    pt_tmp.put ( "r" , circles_xml[i].r );
    pt_item.add_child ( string_tmp + ".r" , pt_tmp.get_child ( "r" ) );

    pt_circles.add_child ( "circles." + string_tmp , pt_item.get_child ( string_tmp ) );
  }

  boost::property_tree::ptree pt_lines_num;
  boost::property_tree::ptree pt_tables_num;
  boost::property_tree::ptree pt_images_num;
  boost::property_tree::ptree pt_texts_num;
  boost::property_tree::ptree pt_rects_num;
  boost::property_tree::ptree pt_circles_num;

  pt_lines_num.put ( "number" , lines_xml.size() );
  pt_tables_num.put ( "number" , tables_xml.size() );
  pt_images_num.put ( "number" , images_xml.size() );
  pt_texts_num.put ( "number" , texts_xml.size() );
  pt_rects_num.put ( "number" , rects_xml.size() );
  pt_circles_num.put ( "number" , circles_xml.size() );

  pt_lines.add_child ( "lines.number" , pt_lines_num.get_child ( "number" ) );
  pt_tables.add_child ( "tables.number" , pt_tables_num.get_child ( "number" ) );
  pt_images.add_child ( "images.number" , pt_images_num.get_child ( "number" ) );
  pt_texts.add_child ( "texts.number" , pt_texts_num.get_child ( "number" ) );
  pt_rects.add_child ( "rects.number" , pt_rects_num.get_child ( "number" ) );
  pt_circles.add_child ( "circles.number" , pt_circles_num.get_child ( "number" ) );

  pt.add_child ( "template.lines" , pt_lines.get_child ( "lines" ) );
  pt.add_child ( "template.tables" , pt_tables.get_child ( "tables" ) );  
  pt.add_child ( "template.images" , pt_images.get_child ( "images" ) );  
  pt.add_child ( "template.texts" , pt_texts.get_child ( "texts" ) );
  pt.add_child ( "template.rects" , pt_rects.get_child ( "rects" ) );
  pt.add_child ( "template.circles" , pt_circles.get_child ( "circles" ) );

  lines_xml.clear();
  tables_xml.clear();
  images_xml.clear();
  texts_xml.clear();
  rects_xml.clear();
  circles_xml.clear();
  gens_xml.clear();


  return true;

}


bool Xml_converter :: move_pt_to_xml ()
{
  std::string command = "touch " + out_path;
  std::system ( command.c_str() );
  write_xml( out_path , pt);
  pt.clear();
  return true;
}

void Xml_converter :: delete_tmp_xml ()
{
  std::string command = "rm " + out_path;
  std::system( command.c_str() );
}
