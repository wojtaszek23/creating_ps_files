MAKE_TEMPLATE:
program make_template służy do tworzenia dokumentów tekstowych w formacie ps (post script), które przypominają format pdf, tyle, że w trybie edycji.
Zbudowanie programu wykonywalnego: polecenie "cmake -H. -Bbuild". Następnie w podkatalogu "build" wykonać polecenie "make".
W celu utworzenia pliku dokumentowego należy wejść do katalogu build, w którym znajduje się plik make_template i wywołać polecenie (przykład dla utworzenia polskiego template'a):
./make_template ../xml/solid_polish.xml ../xml/layout_solid.xml ../templates/template.ps <ścieżka>/template_polish.ps
