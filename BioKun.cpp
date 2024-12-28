#define SDL_MAIN_HANDLED
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

int main(int argc, char* argv[])
{   //游戏初始化
    SDL_Init(SDL_INIT_EVERYTHING);//选择初始化所有
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);//初始化所有Jpg和Png格式图片
    TTF_Init();//字体只有一种格式.ttf不用指定
    Mix_Init(MIX_INIT_MP3);//初始化MP3格式
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);//采样率、格式（这里是mp3）、通道为2、块大小是2048
    SDL_Window* window=SDL_CreateWindow(u8"My First SDL Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,SDL_WINDOW_SHOWN);
    SDL_Renderer*renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);//创建渲染器并使用硬件加速
    SDL_Surface* surface=IMG_Load("./resources/chicken_slow_5.png");//将图片反序列化到内存中
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);//将内存的数据转换为纹理数据
    TTF_Font *font = TTF_OpenFont("./resources/IPix.ttf", 32);
    SDL_Color color={255,255,255,255};
    SDL_Surface*sur_ttf=TTF_RenderUTF8_Blended(font,u8"My First SDL Game",color);
    SDL_Texture*tex_ttf=SDL_CreateTextureFromSurface(renderer,sur_ttf);
    Mix_Music *music=Mix_LoadMUS("./resources/bgm.mp3");
    Mix_FadeInMusic(music,-1,1500);
    //主循环
    int fps=60;//帧率
    bool is_quit=false;
    SDL_Event event;
    SDL_Point mouse{0,0};
    SDL_Rect rect,rect_ttf;
    Uint64 lastCounter=SDL_GetPerformanceCounter();
    Uint64 counterFreq=SDL_GetPerformanceFrequency();
    rect.w=surface->w;
    rect.h=surface->h;
    rect_ttf.w=sur_ttf->w;
    rect_ttf.h=sur_ttf->h;
    while(!is_quit)
    {
        //处理事件
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)is_quit=true;//设置退出事件
            else if (event.type == SDL_MOUSEMOTION)
            {
                mouse.x=event.motion.x;
                mouse.y=event.motion.y;
            }
        }
        Uint64 curr_counter=SDL_GetPerformanceCounter();
        double delta=static_cast<double>((curr_counter-lastCounter)/counterFreq);
        lastCounter=curr_counter;
        if (delta*1000<1000.0/60)SDL_Delay(static_cast<Uint32>(1000.0/60-delta*1000));
        //处理数据
        rect.x=mouse.x;
        rect.y=mouse.y;
        rect_ttf.x=mouse.x;
        rect_ttf.y=mouse.y;
        SDL_SetRenderDrawColor(renderer,0,0,0,255);//设置渲染颜色为黑色
        SDL_RenderClear(renderer);//清空上一次渲染
        //渲染绘制
        SDL_RenderCopy(renderer,texture,nullptr,&rect);//绘制一张图片，src是被截取原图片，nullptr代表全部截取。dst代表被放大的src的大小、位置（这里保持和鼠标位置一致）
        SDL_RenderCopy(renderer,tex_ttf,nullptr,&rect_ttf);
        SDL_RenderPresent(renderer);//刷新渲染器
        
    }
    
    
    return 0;
}
