#include "Vector.hpp"

#include "Factories.hpp"
void register_entity(EntityFactoryJson& factory)
{
    factory.registerType("Oper", [](Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) { return std::make_shared<Oper>(field, jEntity); });
    factory.registerType("Smart", [](Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) { return std::make_shared<Smart>(field, jEntity); });
    factory.registerType("Wild", [](Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) { return std::make_shared<Wild>(field, jEntity); });
    factory.registerType("Forager", [](Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) { return std::make_shared<Forager>(field, jEntity); });
    factory.registerType("FAK", [](Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) { return std::make_shared<FAK>(field, jEntity); });
}