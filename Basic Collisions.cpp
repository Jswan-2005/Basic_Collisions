#include <iostream>
#include <raylib.h>

class Ball {
public:
    float x,y;
    int radius;
    int speed_x, speed_y;

    void Draw() {
        DrawCircle(x,y,radius, BLUE);
    }
    void UpdateX() {
       x += speed_x;
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x = speed_x * -1;
        }
    }

    void UpdateY() {
        y += speed_y;
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y = speed_y * -1;
        }
    }

};

//Blocks
class Block {
public:
    float x,y;
    float width, height;
    void Draw() {
        DrawRectangle(x,y,width,height,BLACK);
    }

    Rectangle GetRect() {
        return Rectangle{x,y,width,height};
    }
};


//Instance of Our Class
Ball ball1;
Ball ball2;
Block block1;
Block block2;
Block block3;

//Raylib Gameloop
int main() {
    const int screen_width = 800;
    const int screen_height = 800;
    InitWindow(screen_width,screen_height, "Collisions");
    SetTargetFPS(60);

    //Block1 Properties
    block1.width = 50;
    block1.height = 50;
    block1.x = 400;
    block1.y = 600;

    //Block2 Properties
    block2.width = 200;
    block2.height = 50;
    block2.x = 60;
    block2.y = 200;

    //Block3 Properties
    block3.width = 50;
    block3.height = 100;
    block3.x = 400;
    block3.y = 300;

    //Ball1 Properties
    ball1.x = screen_width/2;
    ball1.y = screen_height/2;
    ball1.speed_x = 5;
    ball1.speed_y = 5;
    ball1.radius = 20;

    //Ball2 Properties
    ball2.x = 20;
    ball2.y = 20;
    ball2.speed_x = 5;
    ball2.speed_y = 5;
    ball2.radius = 20;

    bool collidedBall = false;
    bool collidedBlockBall1 = false;
    bool collidedBlockBall2 = false;
    Block blocks[] = { block1, block2, block3 };

        //Speed Choices For Collisions
        int speed_choices[2] = {-1, 1};

        while (WindowShouldClose() == false) {
            BeginDrawing();
            //Collision Checking
            bool isCollidingBall =  CheckCollisionCircles(Vector2{ball1.x,ball1.y}, ball1.radius, Vector2{ball2.x,ball2.y}, ball2.radius);


            //Updates
            ball1.UpdateX();
            ball1.UpdateY();
            ball2.UpdateX();
            ball2.UpdateY();

            //Collision Checking (Ball on Ball)
            if (isCollidingBall && !collidedBall) {
                ball1.speed_x *= speed_choices[GetRandomValue(0,1)];
                ball1.speed_y *= -1;
                ball2.speed_x *= speed_choices[GetRandomValue(0,1)];
                ball2.speed_y *= -1;
                collidedBall = true;
            } else if (!isCollidingBall) {
                collidedBall = false;
            }

            //Collision Checking (Ball on Block)
            // Ball–Block Collisions
            for (Block& block : blocks) {
                Rectangle rect = { block.x, block.y, block.width, block.height };

                // For Ball 1
                if (CheckCollisionCircleRec(Vector2{ ball1.x, ball1.y }, ball1.radius, rect) && !collidedBlockBall1) {
                    ball1.speed_y *= -1;
                    collidedBlockBall1 = true;
                }

                // For Ball 2
                if (CheckCollisionCircleRec(Vector2{ ball2.x, ball2.y }, ball2.radius, rect) && !collidedBlockBall2) {
                    ball2.speed_y *= -1;
                    collidedBlockBall2 = true;
                }
            }

            // Reset collision flags if no collisions in this frame
            collidedBlockBall1 = false;
            collidedBlockBall2 = false;

            //Collision Checking (Ball on Block)

            //Drawing
            ClearBackground(RAYWHITE);
            ball1.Draw();
            ball2.Draw();
            block1.Draw();
            block2.Draw();
            block3.Draw();

            EndDrawing();
        }
        CloseWindow();
        return 0;
}

