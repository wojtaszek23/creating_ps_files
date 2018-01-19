/*

   Author: Wojciech Stanislawski <woj.stanislawski@gmail.com>

   Copyright (c) 2018, Uni-Trol Sp. z o.o.

   All rights reserved.

   This is unpublished proprietary source code of Uni-Trol Sp. z o.o.
   The contents of this file may not be disclosed to third parties,
   copied or duplicated in any form, in whole or in part, without
   prior written permission from Uni-Trol.

*/


#include <iostream>
#include <time.h>
#include "xml_converter.hpp"
#include "print_maker.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

void print_to_log ( std::string log_text , std::string logfile_path = "../print_data/log.txt" )
{
  time_t now; // czas w sekundach od 0 roku n.e.
  struct tm *now_info; // struktura rozkładająca liczbę całkowitą sekund od 0 roku n.e na obecny rok, miesięac, dzień, godzinę i sekundę.
  std::string time_text;

  time ( &now );  // zapis czasu obecnego do now
  now_info = localtime ( &now );  // zapis wartości poszczególnych jednostek czasowych do now_info  
  time_text = asctime ( now_info );  // zapis danych nt. czasu do stringa
  std::string print_command = "echo \"" + time_text + log_text + "\n\" >> " + logfile_path; 
  system ( print_command.c_str() );
}


int main( int argc, char **argv)
{

  std::string command;
  std::string bash_result;
  std::string printer_name = "Brother_HL-1110_series";
  print_to_log ( "----- Rozpoczęcie procesu drukowania -----" );
  if ( argc == 2 )
  {
    printer_name = argv[1];
  }

  command = "if lpstat -a | grep -q \"" + printer_name +
"\"\; then echo \"ZNALEZIONO DRUKARKĘ\" > log_tmp.txt\; else echo \"NIE ZNALEZIONO DRUKARKI\" > log_tmp.txt\; fi";
  system ( command.c_str() );
  std::ifstream log_tmp ( "log_tmp.txt" );
  getline ( log_tmp , bash_result );

  if ( bash_result != "ZNALEZIONO DRUKARKĘ" )
  {
    print_to_log ( "Drukarka: " + printer_name + " - NIE ZNALEZIONO" );
    print_to_log ( "----- Zakończenie procesu drukowania -----\n" );
    command = "result while searching printer " + printer_name + ": " + bash_result;
    std::cout<<command<<std::endl;
    return 2;
  }

  print_to_log ( "Drukarka: " + printer_name + " - ZNALEZIONO" );

  boost::property_tree::ptree pt;
  int lang = 0;
  std::string template_ps;

  try{
    read_xml ( "/home/monolith/settings.xml" , pt ); //czytanie glownego pliku zawierajacego podstawowe dane aktualnej konfiguracji systemu
    int lang = pt.get<int>( "settings.language" );
  }catch(...) {};
  
  switch ( lang ) //wybor odpowiedniego szablonu (rozszerzenie .ps) do drukowania zawierajacego napisy, ktore sie powtarzaja(template_<lang>.ps), w danym jezyku.
  {
    case 0:
      template_ps = "../print_data/template_polish.ps";
      break;
    case 1:
      template_ps = "../print_data/template_english.ps";
      break;
    case 2:
      template_ps = "../print_data/template_spanish.ps";
      break;
    case 3:
      template_ps = "../print_data/template_italian.ps";
      break;
    case 4:
      template_ps = "../print_data/template_russian.ps";
      break;
    case 5:
      template_ps = "../print_data/template_serbian.ps";
      break;
    case 6:
      template_ps = "../print_data/template_turkish.ps";
      break;
    case 7:
      template_ps = "../print_data/template_bulgarian.ps";
      break;
    default:
      template_ps = "../print_data/template_polish.ps";
      break;
  }

  command = "mkdir tmp";
  system ( command.c_str() );

/*
  Konstruktor Xml_converter ( std::string new_source_path , std::string new_layout_path , std::string new_out_path , bool execute = true )
  new_source_path - sciezka do pliku (.xml) zawierajacego szczegolowe dane do  stworzenia pliku .ps
  new_layout_path - sciezka do pliku (.xml) zawierajacego informacje o poszczegolnych elementach, takich jak tabele, napisy, obrazki itp. Ich wartosci sa szczegolowo okreslone w source_path.
  tmp/tmp.xml - plik stworzony tymczasowo na potrzeby dzialania aplikacji. Wykorzystywany do zapisu informacji z rozszerzeniem xml. Informacje te sa przygotowane zgodnie z zapisem, ktory Print_maker bedzie mogl odczytac i pozapisywac wszystkie do pliku wynikowego (.ps). 
*/

  print_to_log ( "Tworzenie pliku tymczasowego .xml zawierającego informacje o układzie strony..." );

  Xml_converter x_c( "../../printing.xml" , "../print_data/layout_printing.xml" , "tmp/tmp.xml" );


  print_to_log ( "Tworzenie pliku tymczasowego .ps zawierającego kod z układem strony do druku..." );

  Print_maker print_maker;
  print_maker.create_tmp_ps ( template_ps , "tmp/tmp.ps" ); 
//utworzenie pliku, do ktorego bedzie zapisywany kod (.ps), wykorzystywany bezposrednio do druku + zapis wczesniej wybranego szablonu jezykowego

  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.images" , "image", "tmp/tmp.ps" );
  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.texts" , "text", "tmp/tmp.ps" );
  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.lines" , "line", "tmp/tmp.ps" );
  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.tables" , "table", "tmp/tmp.ps" );
  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.rects" , "rect", "tmp/tmp.ps" );
  print_maker.write_to_ps ( "tmp/tmp.xml" , "template.circles" , "circle", "tmp/tmp.ps" );
/*
dodawanie poszczegolnych elementow do pliku (.ps) wykorzystywanego do druku (obrazy, teksty, linie, tabelki, prostokaty, kola)
wedlug nastepujacej kolejnosci:
1. sprawdzenie typu elementu
2. odczyt informacji z tymczasowego pliku xml (tmp/tmp.xml) do postaci drzewa (boost::property_tree::ptree):
- odczyt liczby elementow
- odczyt kazdego elementu i zapis informacji do obiektow reprezentujacych poszczegolne elementy zawierajace dane takie jak polozenie, wymiary komponentu itp. Odpowiedzialna jest za to funkcja wirtualna "get_info"
- w przypadku linii, tabel, prostokatow, kol (elementy generowane przez interpreter jezyka postscript) zapis informacji do bufora zgodnie ze standardem funkcji zawartych w pliku template_ps. Natomiast w przypadku obrazow i tekstow, wygenerowanie pliku (.ps) na podstawie obrazu podanego w sciezce (w przypadku tekstow jest to poprzedzone wygenerowaniem takiego obrazu z podanym napisem i wymiarami czcionki oraz rozmiarow wykikowego obrazu). W przypadku obrazow i tekstow, do wyzej wymienionych operacji sluzy polecenie konsolowe "convert" z pakietu Image Magick.
3.zapis zawartosci wygenerowanych plikow do pliku wyjsciowego (tmp/tmp.ps)
*/

  print_to_log ( "Operacja drukowania strony..." );

  command = "lpr -P " + printer_name + " tmp/tmp.ps";
  system ( command.c_str() );
  //wydrukowanie zawartosci pliku (.ps) interpretowalnego przez drukarke.

  command = "rm -rf tmp";
  system ( command.c_str() );

  command = "rm -rf log_tmp.txt";
  system ( command.c_str() );

  //usuniecie tymczasowego logu

  print_to_log ( "----- Zakończenie procesu drukowania -----\n" );

  return 0;
}
