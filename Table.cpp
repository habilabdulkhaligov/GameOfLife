#include "Table.hpp"

Cell::Cell() : state(false) {}

Cell::Cell(bool state) : state(state) {}

bool Cell::getState() const {
    return state;
}

void Cell::setState(bool state) {
    this->state = state;
}

void Cell::switchState() {
    this->state ^= true;
}

Table::Table(uint32_t width, uint32_t height) : width(width), height(height) {
    uint64_t size = width * height;

    this->_cells = new Cell[size]{};
    if (this->_cells == nullptr)
        throw MemoryException();
}

uint64_t Table::addressToIndex(uint32_t row, uint32_t col) {
    uint64_t result = col;
    result += row * width;
    return result;
}

void Table::fill(uint32_t density) {
    if (density > 100)
        throw InvalidArgumentException();

    uint64_t length = width * height;

    srand(time(nullptr));
    for (int i = 0; i < length; i++) {
        int random = rand() % 101;
        _cells[i].setState(density >= random);
    }
}

void Table::update() {
    uint64_t length = width * height;

    Cell *newCells = new Cell[length];
    if (newCells == nullptr)
        throw MemoryException();

    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            uint64_t cellIndex = addressToIndex(row, col);

            int aliveNeighborsCount = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0)
                        continue;

                    uint32_t newRow = (row + height + i) % height;
                    uint32_t newCol = (col + width + j) % width;

                    uint64_t neighbourIndex = addressToIndex(newRow, newCol);
                    if (_cells[neighbourIndex].getState())
                        aliveNeighborsCount++;
                }
            }

            Cell *cell = _cells + cellIndex;
            newCells[cellIndex] = *cell;

            if ((cell->getState() && (aliveNeighborsCount < 2 || aliveNeighborsCount >3)) || 
                (!cell->getState() && aliveNeighborsCount >= 2 && aliveNeighborsCount <= 3))
                newCells[cellIndex].switchState();
        }
    }

    delete[] _cells;
    _cells = newCells;
}

std::ostream &operator<<(std::ostream &os, const Table &table) {
    os << '+';
    for (uint32_t i = 0; i < table.width; i++)
        os << '-';
    os << '\n';

    for (uint32_t i = 0; i < table.height; i++) {
        os << '|';
        for (uint32_t j = 0; j < table.width; j++)
            os << (table._cells[i * table.width + j].getState() ? 'X' : ' ');
        os << '|' << '\n';
    }

    os << '+';
    for (uint32_t i = 0; i < table.width; i++)
        os << '-';
    os << '\n';

    return os;
}

Table::~Table() {
    delete[] _cells;
}
