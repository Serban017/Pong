#include <iostream>
#include <raylib.h>

using namespace std;

int player_one_score = 0; 
int player_two_score = 0;


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
            
            if (x + radius >= GetScreenWidth())
            {
                player_two_score++;
               ResetBall();
            }
            if (x - radius <= 0) 
            {
                player_one_score++;
                ResetBall();
            }
        }

        void ResetBall()
        {
            x = GetScreenWidth() / 2;
            y = GetScreenHeight() / 2; 

            int speed_choices[2] = { -1,1 }; 
            speed_x *= speed_choices[GetRandomValue(0, 1)];
            speed_y *= speed_choices[GetRandomValue(0, 1)];
        }
};

class Player_One_Paddle {

protected: 

    void Limit_Movement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

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
            
            Limit_Movement();
        }

    };

class Player_Two_Paddle : public Player_One_Paddle {
    public: 
        void Update()
        {
            if (IsKeyDown(KEY_UP))
            {
                y = y - speed;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                y = y + speed;
            }

            Limit_Movement();
        }
};

class CPU_Paddle : public Player_One_Paddle {
    public:
        void Update(int ball_y)
        {
            if (y + height/2 > ball_y)
            {
                y = y - speed;
            }
            if(y + height/2 <= ball_y)
            {
                y = y + speed;
            }
            Limit_Movement();
        }
    };

Ball ball;
Player_One_Paddle player_one;
Player_Two_Paddle player_two;
CPU_Paddle cpu;

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

    player_one.width = 25; 
    player_one.height = 120;
    player_one.x = 10;
    player_one.y = (screen_height / 2) - (player_one.height / 2);
    player_one.speed = 6; 

    player_two.width = 25; 
    player_two.height = 120;
    player_two.x = screen_width - player_two.width - 10;
    player_two.y = screen_height / 2 - player_two.height / 2;
    player_two.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = screen_width - player_two.width - 10;
    cpu.y = screen_height / 2 - player_two.height / 2;
    cpu.speed = 6;


    while(WindowShouldClose() == false)
        {
        BeginDrawing();
        
        //Updating ball position, player and cpu
        ball.Update();
        player_one.Update();
        //player_two.Update();
        cpu.Update(ball.y);
        //Checking for colision
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player_one.x, player_one.y, player_one.width, player_one.height })) 
        {
            ball.speed_x *= -1;
        }
        
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player_two.x, player_two.y, player_two.width, player_two.height }))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
        {
            ball.speed_x *= -1;
        }
        //Drawing the ball, paddles, line and score
        ClearBackground(BLACK);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player_one.Draw();
        //player_two.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", player_two_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_one_score),3 * screen_width / 4 - 20, 20, 80, WHITE);
        EndDrawing();
        }

    CloseWindow();
    return 0;
}