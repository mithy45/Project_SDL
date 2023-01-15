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
        bool collide(const std::shared_ptr<RenderedObject>& rendered_object);
        double get_distance(const std::shared_ptr<RenderedObject>& rendered_object);

        inline SDL_Rect get_rect() const {return this->rect;};
        static void renderer_width_height(SDL_Renderer *renderer_ptr, int *width, int *height);
        static bool is_point_in_rect(int x, int y, const SDL_Rect& rect);

    protected:
        // Not the owner of this pointer
        SDL_Renderer *window_renderer_ptr;
        SDL_Rect rect;

        void render_image();
        void render_rectangle(const SDL_Color& color);

    private:
        // Owner pointer
        SDL_Texture *image_ptr;
};
#endif