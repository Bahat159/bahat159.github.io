#include "structure.h"

int main() {
    struct PERSON sister;
    PERSON brother;

    sister.age = 13;
    brother.age = 7;
    std::cout << "Sister age = " << sister.age <<std::endl;
    std::cout << "Brother age = " <<brother.age <<std::endl;

    CELL my_cell;
    my_cell.character = 1;

    std::cout <<"my_cell.character = " <<my_cell.character <<std::endl;
}
