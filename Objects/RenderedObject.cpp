#include "RenderedObject.h"

#include <ctgmath>
#include <random>

namespace 
{
    // Create texture from img loaded given by args and fill the height and width of img
    SDL_Texture *create_texture_from(const std::string &path, SDL_Renderer *renderer_ptr, SDL_Rect *rect)
    {
        SDL_Surface *img_loaded = IMG_Load(path.c_str());
        if (!img_loaded)
            throw std::runtime_error("IMG_Load"
                                    + std::string(IMG_GetError()));
        rect->h = img_loaded->h;
        rect->w = img_loaded->w;
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_ptr, img_loaded);
        if (!texture)
            throw std::runtime_error("SDL_ConvertSurface"
                                    + std::string(IMG_GetError()));
        SDL_FreeSurface(img_loaded);
        return texture;
    }

    double distance_between_rect(SDL_Rect rect_a, SDL_Rect rect_b)
    {
        double x1 = (rect_a.x + rect_a.x + rect_a.w) / 2.0;
        double y1 = (rect_a.y + rect_a.y + rect_a.h) / 2.0;

        double x2 = (rect_b.x + rect_b.x + rect_b.w) / 2.0;
        double y2 = (rect_b.y + rect_b.y + rect_b.h) / 2.0;

        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }
};

RenderedObject::RenderedObject(SDL_Renderer *window_renderer_ptr, const std::string &file_path)
{
    this->window_renderer_ptr = window_renderer_ptr;
    this->image_ptr = create_texture_from(file_path, this->window_renderer_ptr, &this->rect);

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_width(this->rect.w, 1400 - this->rect.w);
    std::uniform_int_distribution<int> dis_height(this->rect.h, 900 - this->rect.h);
    this->rect.x = dis_width(generator);
    this->rect.y = dis_height(generator);
}


RenderedObject::~RenderedObject()
{
    SDL_DestroyTexture(this->image_ptr);
}


bool RenderedObject::collide(std::shared_ptr<RenderedObject> rendered_object)
{
    SDL_Rect Rect_A = this->get_rect();
    SDL_Rect Rect_B = rendered_object->get_rect();

    return ((Rect_A.x >= Rect_B.x && Rect_A.x <= (Rect_B.x + Rect_B.w)) ||
            (Rect_B.x >= Rect_A.x && Rect_B.x <= (Rect_A.x + Rect_A.w))) 
            && 
            ((Rect_A.y >= Rect_B.y && Rect_A.y <= (Rect_B.y + Rect_B.h)) ||
            (Rect_B.y >= Rect_A.y && Rect_B.y <= (Rect_A.y + Rect_A.h)));
}


double RenderedObject::get_distance(std::shared_ptr<RenderedObject> rendered_object)
{
    return distance_between_rect(this->get_rect(), rendered_object->get_rect());
}

void RenderedObject::render_image()
{
    if (SDL_RenderCopy(window_renderer_ptr, image_ptr, NULL, &this->rect))
        throw std::runtime_error("SDL_RenderCopy"
                                + std::string(SDL_GetError()));
}

void RenderedObject::render_rectangle(SDL_Color color)
{
    if(SDL_SetRenderDrawColor(this->window_renderer_ptr, color.r, color.g, color.b, color.a))
        throw std::runtime_error("SDL_SetRenderDrawColor"
                                + std::string(SDL_GetError()));

    if(SDL_RenderDrawRect(window_renderer_ptr, &this->rect))
        throw std::runtime_error("SDL_RenderDrawRect"
                                + std::string(SDL_GetError()));
}

void RenderedObject::renderer_width_height(SDL_Renderer *renderer_ptr, int *width, int *height)
{
    // Get the current renderer size
    if (SDL_GetRendererOutputSize(renderer_ptr, width, height) != 0)
        throw std::runtime_error("SDL_GetRendererOutputSize"
                                + std::string(SDL_GetError()));
}

bool RenderedObject::is_point_in_rect(int x, int y, SDL_Rect rect)
{
    return x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h);
}