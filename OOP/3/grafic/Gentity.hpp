#ifndef GRAVIC
#define GRAVIC
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "Personage.hpp"
#include "game_algorithm.hpp"
class GEntity
{
private:
    std::shared_ptr<Entity> _entity;
    sf::Text _text;
    sf::Sprite _sprite;
public:
    [[nodiscard]] const std::shared_ptr<Entity>& get_entity() const {return _entity;}
    [[nodiscard]] sf::Text& get_text() {return _text;}
    [[nodiscard]] sf::Sprite& get_sprite() {return _sprite;}
    GEntity();
    GEntity(std::shared_ptr<Entity> entity) :_entity(entity), _text(), _sprite(){}
    ~GEntity() = default;
    void visiable_Entity(Vector<Vector<std::shared_ptr<Cell>>> &field, std::vector<GEntity>& listEntity, std::vector<GEntity>& visible_entity)
    {
        for(size_t i = 0; i < listEntity.size(); i++)
        {
            int x_enemy = listEntity[i].get_entity()->get_position()->get_position().x, x_this = _entity->get_position()->get_position().x;
            int y_enemy = listEntity[i].get_entity()->get_position()->get_position().y, y_this = _entity->get_position()->get_position().y;
            if(((x_enemy - x_this) == 0)&&((y_enemy - y_this) == 0))
            {
                continue;
            }
            if((std::pow((x_enemy - x_this),2) + std::pow((y_enemy - y_this),2)) <= std::pow(_entity->get_viewRadius(), 2))
            {
                if(std::find(visible_entity.begin(), visible_entity.end(), listEntity[i]) == visible_entity.end())
                {
                    if(propobility_see(field, _entity->get_position(), listEntity[i].get_entity()->get_position()))
                    {
                        visible_entity.push_back(listEntity[i]);
                    }
                }
            }
        }
    }
    bool operator ==(const GEntity& gentity)
    {
        return _entity == gentity.get_entity();
    }
};

class Textures
{
private:
    int amount_uniquie_type_item = 1;
    int amount_weapon_type = 4;
    int amount_type_cell = 5;
    int amount_type_entity = 4;
public:
    std::unordered_map<std::string, sf::Texture> textures_entity;
    std::unordered_map<TypeCell, sf::Texture> textures_cell;
    std::unordered_map<ItemType, sf::Texture> textures_item;
    std::unordered_map<WeaponType, sf::Texture> textures_caseBullets;
    std::unordered_map<WeaponType, sf::Texture> textures_weapon;
    Textures(std::string filename) : textures_entity(amount_type_entity), textures_cell(amount_type_cell),
    textures_item(amount_uniquie_type_item), textures_caseBullets(amount_weapon_type), textures_weapon(amount_weapon_type)
    {
        if (!textures_cell[TypeCell::field].loadFromFile(filename + "/field.jpg")) throw std::runtime_error("Error: Could not load field.jpg");
        if (!textures_cell[TypeCell::glass].loadFromFile(filename + "/glass.jpg")) throw std::runtime_error("Error: Could not load glass.jpg");
        if (!textures_cell[TypeCell::partition].loadFromFile(filename + "/partition.jpg")) throw std::runtime_error("Error: Could not load partition.jpg");
        if (!textures_cell[TypeCell::storagePoint].loadFromFile(filename + "/SP.jpg")) throw std::runtime_error("Error: Could not load SP.jpg");
        if (!textures_cell[TypeCell::wall].loadFromFile(filename + "/wall.jpg")) throw std::runtime_error("Error: Could not load wall.jpg");
        for (const auto& entry : std::filesystem::directory_iterator(filename + "/entities")) {
            std::string outfilename = entry.path().filename().string();
            outfilename.erase(outfilename.begin() + outfilename.find('.'), outfilename.end());
            std::string entityType = outfilename;
            if (!textures_entity[entityType].loadFromFile(entry.path()))throw std::runtime_error("Error: Could not load" + outfilename);
        }
        if (!textures_caseBullets[WeaponType::pistol].loadFromFile(filename + "/pistol.png"))throw std::runtime_error("Error: Could not load pistol.png");
        if (!textures_item[ItemType::firstAidKit].loadFromFile(filename + "/FAK.png"))throw std::runtime_error("Error: Could not load FAK.png");
        if (!textures_caseBullets[WeaponType::shotgun].loadFromFile(filename + "/shotgun.png"))throw std::runtime_error("Error: Could not load shotgun.png");
        if (!textures_caseBullets[WeaponType::revolver].loadFromFile(filename + "/revolver.png"))throw std::runtime_error("Error: Could not load revolver.png");
        if (!textures_caseBullets[WeaponType::rifle].loadFromFile(filename + "/rifle.png"))throw std::runtime_error("Error: Could not load rifle.png");
        if (!textures_weapon[WeaponType::pistol].loadFromFile(filename + "/pistolGun.png"))throw std::runtime_error("Error: Could not load pistolGun.png");
        if (!textures_weapon[WeaponType::shotgun].loadFromFile(filename + "/shotgunGun.png"))throw std::runtime_error("Error: Could not load shotgunGun.png");
        if (!textures_weapon[WeaponType::revolver].loadFromFile(filename + "/revolverGun.png"))throw std::runtime_error("Error: Could not load revolverGun.png");
        if (!textures_weapon[WeaponType::rifle].loadFromFile(filename + "/rifleGun.png"))throw std::runtime_error("Error: Could not load rifleGun.png");
    }
    Textures() = default;
    ~Textures() = default;
};
class Game_stat
{
public:
    const int pixel_correction = 8;
    const int CELL_SIZE = 64;
    const int menu_size = 500;
    const int inventory_size = 500;
    const int frame_limit = 60;
    Textures textures;
    std::vector<GEntity> GEntities;
    std::shared_ptr<Entity> active_entity;
    sf::RenderWindow window;
    sf::RenderWindow menu;
    sf::RenderWindow inventory;
    bool active_step = false;
    bool active_shoot = false;
    bool showText = false;
    bool cell_inventory = false;
    bool gameEnd = false;
    bool save_window = false;    
    sf::Clock clock;
    sf::Time beginTime;
    sf::Time endTime;
    std::string file_save = "save/level.json";
    const std::string file_save_in_time = "save/levelpop.json";
    Game_stat() : textures("texture"){}
};
class Game_sprites
{

};
class Game_texts
{
public:
    const int font_size = 30;
    const int font_size_warning = 90;
    sf::Text text_menu;
    sf::Text save_text;
    sf::Text Text_gen;
    sf::Text eventText;
    sf::Font font;
    Game_texts(){
        font.loadFromFile("Lobster-Regular.ttf");
        Text_gen.setFont(font);
        text_menu.setFont(font);
        save_text.setFont(font);
        eventText.setFont(font);
        text_menu.setFillColor(sf::Color::Red);
        Text_gen.setFillColor(sf::Color::Red);
        eventText.setFillColor(sf::Color::Red);
        save_text.setFillColor(sf::Color::Red);
        eventText.setCharacterSize(font_size_warning);
        Text_gen.setCharacterSize(font_size);
        save_text.setCharacterSize(font_size);        
        text_menu.setCharacterSize(font_size);
        save_text.setString("save file: \n level.json\n level_save.json\n");
    }
};
#endif