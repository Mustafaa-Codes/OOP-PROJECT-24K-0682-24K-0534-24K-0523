#include <raylib.h>
#include <iostream>

// Neon purple-themed colors
Color NeonPurple      = Color{180, 0, 255, 255};
Color DarkPurple      = Color{40, 0, 60, 255};
Color LightPurple     = Color{200, 150, 255, 255};
Color NeonBlue        = Color{0, 255, 255, 255};
Color NeonPink        = Color{255, 20, 147, 255};

int player_score = 0;
int cpu_score = 0;

class Ball {
 public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, NeonPink);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }

        if (y - radius <= 0) {
            cpu_score++;
            ResetBall();
        }

        if (y + radius >= GetScreenHeight()) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x = 6 * speed_choices[GetRandomValue(0, 1)];
        speed_y = 6 * speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
 protected:
    void LimitMovement() {
        if (x <= 0) x = 0;
        if (x + width >= GetScreenWidth()) {
            x = GetScreenWidth() - width;
        }
    }

 public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, NeonBlue);
    }

    void Update() {
        if (IsKeyDown(KEY_LEFT)) x -= speed;
        if (IsKeyDown(KEY_RIGHT)) x += speed;
        LimitMovement();
    }
};

class CpuPaddle : public Paddle {
 public:
    void Update(int ball_x){
        if (x + width / 2 > ball_x) x -= speed;
        if (x + width / 2 <= ball_x) x += speed;
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
    std::cout << "Starting vertical Pong game" << std::endl;
    const int screen_width = 1600;
    const int screen_height = 1000;
    InitWindow(screen_width, screen_height, "Vertical Neon Pong");
    SetTargetFPS(60);

    // Ball setup
    ball.radius = 12;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 6;
    ball.speed_y = 6;

    // Player paddle (bottom)
    player.width = 100;
    player.height = 20;
    player.x = screen_width / 2 - player.width / 2;
    player.y = screen_height - 30;
    player.speed = 10;

    // CPU paddle (top)
    cpu.width = 100;
    cpu.height = 20;
    cpu.x = screen_width / 2 - cpu.width / 2;
    cpu.y = 10;
    cpu.speed = 8;

    while (!WindowShouldClose()) {
        // Update
        ball.Update();
        player.Update();
        cpu.Update(ball.x);

        // Collision detection
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
            ball.speed_y *= -1;
        }
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_y *= -1;
        }

        // Draw
        BeginDrawing();
        ClearBackground(DarkPurple);
        DrawCircle(screen_width / 2, screen_height / 2, 200, LightPurple);
        DrawLine(0, screen_height / 2, screen_width, screen_height / 2, NeonPurple);

        ball.Draw();
        player.Draw();
        cpu.Draw();

        DrawText(TextFormat("%i", cpu_score), screen_width / 2 - 80, screen_height / 2 - 100, 80, NeonBlue);
        DrawText(TextFormat("%i", player_score), screen_width / 2 + 40, screen_height / 2 + 20, 80, NeonBlue);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}