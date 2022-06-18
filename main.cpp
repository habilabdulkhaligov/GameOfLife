#include <iostream>
#include <unistd.h>
#include "Table.hpp"
#include "Exceptions.hpp"

#define WIDTH  50
#define HEIGHT 25
#define FPS 2
#define DENSITY 1


int main() {
    Table *table;

    try {
        table = new Table(WIDTH, HEIGHT);
    } catch (MemoryException &ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    try {
        table->fill(DENSITY);
    } catch (InvalidArgumentException &ex) {
        std::cout << ex.what() << std::endl;
        delete table;
        return -1;
    }

    std::cout << *table << std::endl;

    useconds_t timeDelay = 1000000 / FPS;

    for (int i = 0; i < 1000; i++) {
        table->update();
        usleep(timeDelay);
        std::cout << *table << std::endl;
    }

    delete table;
    return 0;
}
