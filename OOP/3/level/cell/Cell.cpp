#include "Cell.hpp"
[[nodiscard]] TypeCell Cell::get_typeCell()
{
    return this->_typeCell;
}
[[nodiscard]] Inventory& Cell::get_listItems()
{
    return this->_listItems;
}
[[nodiscard]] Coordinates& Cell::get_position()
{
    return this->_position;
}
Cell& Cell::set_typecell(TypeCell typeCell)
{
    this->_typeCell = typeCell;
    return (*this);
}