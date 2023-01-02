#ifndef RENDERED_OBJECT_H
#define RENDERED_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

class RenderedObject
{
    public:
        // Constructor && Destructor
        RenderedObject(SDL_Renderer *window_renderer_ptr,
                        const std::string &file_path);
        ~RenderedObject();

        virtual void render() = 0;
        bool collide(std::shared_ptr<RenderedObject> rendered_object);
        double get_distance(std::shared_ptr<RenderedObject> rendered_object);

        inline SDL_Rect get_rect() const {return this->rect;};

    protected:
        // Not the owner of this pointer
        SDL_Renderer *window_renderer_ptr;
        SDL_Rect rect;

        void render_image();
        void render_rectangle(SDL_Color color);
        static void renderer_width_height(SDL_Renderer *renderer_ptr, int *width, int *height);

    private:
        // Owner pointer
        SDL_Texture *image_ptr;
};
#endif