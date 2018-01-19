#include <iostream>
#include <string>
#include "xml_converter.hpp"
#include "print_maker.hpp"


int main (int argc, char **argv)
{
  std::string command;
  command = "mkdir tmp";
  system ( command.c_str() );
  if ( argc != 5 )
  {
    std::cout<<"usage: ./make_template <path_to>/solid_<language>.xml <path_to>/layout_solid.xml <path_to>/template.ps <path_to>/template_<language>.ps"<<std::endl;
    return 1;
  }
  std::string src_xml = argv[1];
  std::string layout_xml = argv[2];
  std::string template_ps = argv[3];
  std::string dest_ps = argv[4];
  std::string tmp_xml = "tmp/tmp.xml";
  command = "touch " + dest_ps;
  system ( command.c_str() );
  Xml_converter x_c( src_xml , layout_xml , tmp_xml );
  Print_maker print_maker;
  print_maker.create_tmp_ps ( template_ps , dest_ps );
  print_maker.write_to_ps ( tmp_xml , "template.images" , "image", dest_ps );
  print_maker.write_to_ps ( tmp_xml , "template.texts" , "text", dest_ps );
  print_maker.write_to_ps ( tmp_xml , "template.lines" , "line", dest_ps );
  print_maker.write_to_ps ( tmp_xml , "template.tables" , "table", dest_ps );
  command = "rm -r tmp";
  system ( command.c_str() );
  return 0;
}
