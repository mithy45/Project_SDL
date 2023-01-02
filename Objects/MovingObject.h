#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

class MovingObject
{
    public:
        // Constructor && Destructor
        MovingObject(int velocity_x,
                    int velocity_y);
        ~MovingObject() = default;

        // Virtual method
        virtual void move() = 0;

    protected:
        int velocity_x, velocity_y;
};
#endif