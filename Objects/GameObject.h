#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "RenderedObject.h"
#include "MovingObject.h"
#include "LifeCycleObject.h"
#include "ClickableObject.h"
#include "GameProperty.h"

#include <set>

// class GameObject
class GameObject : public RenderedObject, public MovingObject, public LifeCycleObject, public ClickableObject
{
    public:
        GameObject(const std::initializer_list<GameProperty>& properties,
                    SDL_Renderer *window_renderer_ptr,
                    const std::string &file_path,
                    int velocity_x,
                    int velocity_y);
        ~GameObject() = default;

        // Virtual method
        virtual void interact(const std::shared_ptr<GameObject>& game_object) = 0;

        void add_property(GameProperty property);
        void remove_property(GameProperty property);
        bool contains_property(GameProperty property);

        std::set<GameProperty> get_properties() const {return properties;};
    
    protected:
        std::set<GameProperty> properties;
};
#endif