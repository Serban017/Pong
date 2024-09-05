#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
    public:
        float x, y;
        int speed_x, speed_y; 
        int radius;

        void Draw() {
            DrawCircle(x, y, radius, BLUE);
    }

        void Update() {
            x += speed_x;
            y += speed_y;

            //if the ball hits the edge of the screen the speed is transferred in the opposite direction
            if(y + radius >= GetScreenHeight() || y - radius <= 0) 
            {
                speed_y *= -1;
            }
            
            if (x + radius >= GetScreenWidth() || x - radius <= 0)
            {
                speed_x *= -1;
            }
            
        }
};

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;

    void Draw() 
    {
        DrawRectangle(x, y, width, height, BLUE);
    }

    void Update() 
    {
        if(IsKeyDown(KEY_W))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }
    }

};


Ball ball;
Paddle player;

int main() {

    const int screen_width = 1280; 
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25; 
    player.height = 120;
    player.x = 10;
    player.y = (screen_height / 2) - (player.height / 2);
    player.speed = 6; 

    while(WindowShouldClose() == false)
        {
        BeginDrawing();
        
        //Updating ball position
        ball.Update();
        player.Update();
        //Drawing the ball and paddles
        ClearBackground(BLACK);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        DrawRectangle(1245, screen_height / 2 - 60, 25, 120, BLUE);
        EndDrawing();
        }


    CloseWindow();
    return 0;
}