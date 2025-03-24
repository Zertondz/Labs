#include "Personage.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include "Factories.hpp"
#include "game_algorithm.hpp"
#include "initfactory.hpp"
using json = nlohmann::json;
Level& Level::set_activeTeam(Team team)
{
    _activeTeam = team;
    return (*this);
}
[[nodiscard]] Team Level::get_activeTeam()
{
    return _activeTeam;
}
[[nodiscard]] Vector<Vector<std::shared_ptr<Cell>>>& Level::get_field()
{
    return _field;
}
[[nodiscard]] std::vector<std::shared_ptr<Entity>>& Level::get_listEntity()
{
    return _listEntity;
}
Level::Level() : _field(), _listEntity()
{
    try
    {
        int default_size = 10;
        _activeTeam = Team::None;
        _field.resize(default_size);
        for(int i = 0; i < default_size; i++)
        {
            _field[i].resize(default_size);
            for(int j = 0; j < default_size; j++)
            {
                _field[i][j] = std::make_shared<Cell>(TypeCell::field, Coordinates{i , j});
            }
        }
    }
    catch(std::exception& e)
    {
        throw e;
    }
}
void Level::save(std::string file_Name)
{
    std::ofstream outf(file_Name);
    json jClass;
    json Cell_array = json::array();
    json Entity_array = json::array();
    for(size_t x = 0; x <_field.size(); x++)
    {
        for(size_t y = 0; y < _field[0].size(); y++)
        {
            json jCell;
            json jLCI;
            jCell["TypeCell"] = _field[x][y]->get_typeCell();
            jCell["ListCellItem"] = _field[x][y]->get_listItems().InventoryJson(jLCI);
            jCell["Position"] = {x, y};
            Cell_array.push_back(jCell);
        }
    }
    for(size_t i = 0; i < _listEntity.size(); i++)
    {
        json jEntity;
        Entity_array.push_back(_listEntity[i]->make_json(jEntity));
    }
    jClass["SizeList"] = static_cast<int>(_listEntity.size());
    jClass["Field"] = Cell_array;
    jClass["listEntity"] = Entity_array;
    jClass["ActiveTeam"] = _activeTeam;
    jClass["Size"] = {_field.size(), _field[0].size()};
    outf << std::setw(4) << jClass << std::endl;
}

Level::Level(std::string file_Name): _field(), _listEntity()
{
    EntityFactoryJson factoryEntity;
    register_entity(factoryEntity);
    std::ifstream inf(file_Name);
    json jClass;
    inf >> jClass;
    _field.resize(jClass["Size"][0]);
    _activeTeam = Team(jClass["ActiveTeam"]);
    for(int x = 0; x < jClass["Size"][0]; x++)
    {
        _field[x].resize(jClass["Size"][1]);
        for(int y = 0; y < jClass["Size"][1]; y++)
        {
            Inventory inventory{};
            json jCell(jClass["Field"][x * static_cast<int>(jClass["Size"][1]) + y]);
            _field[x][y] = std::make_shared<Cell>(TypeCell(jCell["TypeCell"]), Coordinates(jCell["Position"][0], jCell["Position"][1]));
            _field[x][y]->get_listItems().addItems(makeInvntoeyJson(inventory, jCell["ListCellItem"]["Items"], jCell["ListCellItem"]["amountItem"]));
        }
    }
    for(size_t i = 0; i < jClass["SizeList"]; i++)
    {
        _listEntity.push_back(factoryEntity.create(_field, jClass["listEntity"][i], jClass["listEntity"][i]["typeEntity"]));
    }
}
void Level::resizeField(int x, int y)
{
    if((static_cast<int>(_field.size()) >= x)&&(static_cast<int>(_field[0].size()) >= y))
    {
        _field.resize(x);
        for(auto iter = _field.begin(); iter != _field.end(); ++iter)
        {
            (*iter).resize(y);
        }
    }
    else if((static_cast<int>(_field.size()) < x)&&(static_cast<int>(_field[0].size()) >= y))
    {
        int curret_size_x = _field.size();
        for(int i = 0; i < x; i++)
        {
            if(i < curret_size_x)
            {
                _field[i].resize(y);
            }
            else
            {
                Vector<std::shared_ptr<Cell>> line;
                for(int j = 0; j < y; j++)
                {
                    line.push_back(std::make_shared<Cell>(TypeCell::field, Coordinates(i, j)));
                }
                _field.push_back(line);
            }
        }
    }
    else if((static_cast<int>(_field.size()) >= x)&&(static_cast<int>(_field[0].size()) < y))
    {
        _field.resize(x);
        int curret_size_y = _field[0].size();
        for(int i = 0; i < x; i++)
        {
            for(int j = curret_size_y; j < y; j++)
            {
                _field[i].push_back(std::make_shared<Cell>(TypeCell::field, Coordinates(i, j)));
            }
        }
    }
    else if((static_cast<int>(_field.size()) < x)&&(static_cast<int>(_field[0].size()) < y))
    {
        int curret_size_y = _field[0].size();
        int curret_size_x = _field.size();
        for(int i = 0; i < x; i++)
        {
            if(i < curret_size_x)
            {
                for(int j = curret_size_y; j < y; j++)
                {
                    _field[i].push_back(std::make_shared<Cell>(TypeCell::field, Coordinates(i, j)));
                }
            }
            else
            {
                Vector<std::shared_ptr<Cell>> line;
                for(int j = 0; j < y; j++)
                {
                    line.push_back(std::make_shared<Cell>(TypeCell::field, Coordinates(i, j)));
                }
                _field.push_back(line);
            }
        }
    }
}