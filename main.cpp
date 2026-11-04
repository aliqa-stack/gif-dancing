#include <iostream>
#include <random>
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

float Random(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.5f, 2.0f);
    return dis(gen);
}

bool CheckColl(Vector2& position, Image& imScarfyAnims){
    if((position.x + imScarfyAnims.width) >= GetScreenWidth() && position.x <= 0){
        position.x *= -1;
        return true;
    }
    return false;
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
    Vector2 movement = {0, 0};
    int gifSpeed = 3;
    bool isMoved = false;
    
    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
    while(!WindowShouldClose()){
        frameCounter++;
        PlayGif(animFrames, imScarfyAnim, texScarfyAnim);
        if(IsKeyDown(KEY_F)){
            isMoved = true;

        }
        if(isMoved){
            movement.x += Random() * gifSpeed;
        }
        if((movement.x + imScarfyAnim.width) >= GetScreenWidth() || movement.x <= 0){
            gifSpeed *= -1;
        }
     

        BeginDrawing();
        ClearBackground(BLANK);
        DrawTextureEx(texScarfyAnim, movement, 0.9f, 0.9f, WHITE);

        EndDrawing();
    }
    UnloadTexture(texScarfyAnim);
    UnloadImage(imScarfyAnim);

    CloseWindow();

    return 0;
}