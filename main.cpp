#include <iostream>
#include "raylib.h"
int currentAnime = 0;
int frameDelay = 8;
int frameCounter = 0;

void PlayGif(int& animFrames, Image& imScarfyAnim, Texture2D& texScarfyAnim){
      if(frameCounter >= frameDelay){

            currentAnime++;
            if(currentAnime >= animFrames){

                currentAnime = 0;
            }
            
 
               size_t nextFrame = (size_t)imScarfyAnim.width*imScarfyAnim.height *4*currentAnime;
                 UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrame);
                frameCounter =0 ;
        }

}

int main(void){
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    const int WIDTH = 1020;
    const int HEIGTH = 800;


    InitWindow(WIDTH, HEIGTH, "gif character");
    SetTargetFPS(60);
    int animFrames = 0;
    Image imScarfyAnim = LoadImageAnim("GIF/camel.gif", &animFrames);
    if(imScarfyAnim.data == nullptr){
        std::cout<<"cannot load GIF \n";
        return 1;
    }
    
    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
    while(!WindowShouldClose()){
        frameCounter++;
        PlayGif(animFrames, imScarfyAnim, texScarfyAnim);
  
        BeginDrawing();
        ClearBackground(BLANK);
        DrawTextureEx(texScarfyAnim, (Vector2){GetScreenWidth()-800, GetScreenHeight()-600}, 0.9f, 0.9f, WHITE);

        EndDrawing();
    }
    UnloadTexture(texScarfyAnim);
    UnloadImage(imScarfyAnim);

    CloseWindow();

    return 0;
}