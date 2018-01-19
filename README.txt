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
