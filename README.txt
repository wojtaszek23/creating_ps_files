MAKE_TEMPLATE:
program make_template służy do tworzenia template'ów językowych.
W celu utworzenia template'u należy wejść do katalogu build, w którym znajduje się plik make_template i wywołać polecenie (przykład dla utworzenia polskiego template'a):

./make_template ../xml/solid_polish.xml ../xml/layout_solid.xml ../templates/template.ps <ścieżka>/template_polish.ps

stworzone pliki template'owe należy przenieść do katalogu w raspberry produkcyjnym:
~/monolith/raspberry/print_data/
Program drukując będzie korzystał z tych plików.

PRINTING_REPORT:
skompilowany program należy umieścić w ścieżce na raspberry produkcyjnym:
~/monolith/raspberry/build/

W ścieżce:
~monolith/
musi znajdować się plik printing.xml, z danymi firmy i pomiaru do wydruku.

W ścieżce
~/monolith/raspberry/print_data/
powinny się znajdować:
-logo firmy, jeśli firma je posiada; 
-plik layout_printing.xml służacy do interpretacji danych zawartych w ~/monolith/printing.xml
-pliki layout_<lang>.ps , gdzie <lang> zastępuję nazwę języka (np. 'polish' dla polskiego) dla wszystkich dostępnych opcji językowych w maszynie.

Przykładowa zawartość pliku (wzór) printing.xml znajdującego się w ścieżce ~/monolith/ :

<printing>
   <company>
      <logo>
         <file>../print_info/logo.png</file>
      </logo>
      <texts>
         <name>Nazwa Firmy</name>
         <address>Miejscowość, ul. Nazwa ulicy nr</address>
         <tel>tel. 22 100 200</tel>
      </texts>
   </company>
   <date>20.11.2017</date>
   <time>14:45</time>

   <balancing_program>2</balancing_program>

   <distance>231.5</distance>
   <width>165.8</width>
   <diameter>924.1</diameter>

   <wheel_1>
      <imbalance_in>30.1</imbalance_in>
      <imbalance_out>20.5</imbalance_out>
   </wheel_1>
   <wheel_2>
      <imbalance_in>30.1</imbalance_in>
      <imbalance_out>20.5</imbalance_out>
   </wheel_2>
   <wheel_3>
      <imbalance_in>30.1</imbalance_in>
      <imbalance_out>20.5</imbalance_out>
   </wheel_3>
   <wheel_4>
      <imbalance_in>30.1</imbalance_in>
      <imbalance_out>20.5</imbalance_out>
   </wheel_4>
</printing>

Program ma być uruchamiany przez polecenie systemowe, w przypadku błędów, logi zawierające info o działaniu programu można sprawdzić przeglądając plik:
 ~/monolith/raspberry/print_data/log.txt
