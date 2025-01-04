#include<stdio.h>
#include<SDL2/SDL.h>
#include<math.h>
#define width 900
#define height 900
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0xefefefef
#define RAYS_NUMBER 100
struct Circle{
    double x;
    double y;
    double r;
};

struct  Ray
{
    double x_start,y_start;
    double angle;
};



void FillCircle(SDL_Surface*surface, struct Circle circle, uint32_t color){
    double radius_squared = pow(circle.r, 2);
    for(double x= circle.x-circle.r;x<=circle.x+circle.r;x++){
        for(double y= circle.y-circle.r;y<=circle.y+circle.r;y++){
            double distance_squared = pow(x-circle.x,2) + pow(y-circle.y,2);
            if (distance_squared<radius_squared)
            {
                SDL_Rect pixel = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surface,&pixel,color);
            }
             
        }
    }
}


void generate_rays(struct Circle Circle, struct Ray rays[RAYS_NUMBER]){
    for (int i = 0; i < RAYS_NUMBER; i++)
    {
        double angle = ((double)i/RAYS_NUMBER)*360;
        printf("angle: %f\n",angle);
    }
    
}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], uint32_t color){
    
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    
    struct Circle circle = {200,200,80};
    struct Circle shadow_circle = {650,300,140};
    SDL_Rect erase_rect = {0,0,width,height};
    struct Ray rays[RAYS_NUMBER];
    generate_rays(circle,rays);

    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running)
    {
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                simulation_running = 0;
            }
            if(event.type == SDL_MOUSEMOTION && event.motion.state!=0){
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle,rays);
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        FillRays(surface, rays, COLOR_GRAY);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
    
}