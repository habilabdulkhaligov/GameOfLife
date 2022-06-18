#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <iostream>
#include "Exceptions.hpp"

class Cell {
private:
    bool state;

public:
    Cell();

    Cell(bool state);

    bool getState() const;
    void setState(bool state);

    void switchState();
};

class Table {
private:
    uint32_t width, height;
    Cell *_cells;

    uint64_t addressToIndex(uint32_t row, uint32_t col);
public:
    Table(uint32_t width, uint32_t height);

    void fill(uint32_t density);

    void update();

    friend std::ostream &operator<<(std::ostream &os, const Table &table);

    ~Table();
};

#endif
