#ifndef LIFE_CYCLE_OBJECT_H
#define LIFE_CYCLE_OBJECT_H

class LifeCycleObject
{
    public:
        LifeCycleObject() = default;
        ~LifeCycleObject() = default;

        virtual void onLiving() = 0;
        virtual void onDying() = 0;
};
#endif