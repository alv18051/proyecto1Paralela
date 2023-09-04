#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <cmath>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BALL_RADIUS = 30;
const float GRAVITY = 200.0f;
const float BOUNCE_FACTOR = 0.6f;
const float BALL_COLLISION_FACTOR = 0.8f;


//Herramientas para calcular el tiempo
Uint32 start_time_operations, end_time_operations;
Uint64 total_time_operations = 0;

Uint32 start_time_collision = SDL_GetTicks();
struct Ball {
    int x, y, dx, dy, bounces, radius;
    Uint8 r, g, b;
    Uint32 start_time_collision;

};

//verificar colision entre dos bolas

bool useBallCollision(Ball &ball1, Ball &ball2, bool ignoreCollision) {
    if (ignoreCollision) {
        return false;
    }
    int dx = ball1.x - ball2.x;
    int dy = ball1.y - ball2.y;
    int distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= (ball1.radius + ball2.radius) * (ball1.radius + ball2.radius);
}

//funcion para dibujar estrellas 
void drawStar(SDL_Renderer* renderer, int x, int y, int radius) {
    const int num_points = 5;
    const double angle = 2 * M_PI / num_points;
    SDL_Point points[num_points * 2 + 1];

    for (int i = 0; i < num_points * 2; i += 2) {
        points[i].x = x + radius * cos(i / 2 * angle);
        points[i].y = y + radius * sin(i / 2 * angle);
        points[i + 1].x = x + (radius / 2) * cos((i / 2) * angle + angle / 2);
        points[i + 1].y = y + (radius / 2) * sin((i / 2) * angle + angle / 2);
    }

    points[num_points * 2] = points[0];
    SDL_RenderDrawLines(renderer, points, num_points * 2 + 1);
}


struct Collision {
    int id1, id2;
    Uint32 timestamp;
};

void ballCollisionManager(Ball &ball1, Ball &ball2) {
    int dx = ball1.x - ball2.x;
    int dy = ball1.y - ball2.y;
    float distance = hypot(dx, dy);

    if (distance == 0.0f) {
        return;
    }
    if (std::isnan(distance)) {
        std::cerr << "Error: invalid distance value: dx = " << dx << ", dy = " << dy << std::endl;
        return;
    }

    float overlap = ball1.radius + ball2.radius - distance;
    float nx = dx / distance;
    float ny = dy / distance;

    ball1.x += nx * overlap / 2;
    ball1.y += ny * overlap / 2;
    ball2.x -= nx * overlap / 2;
    ball2.y -= ny * overlap / 2;

    float relativeVelocityX = ball1.dx - ball2.dx;
    float relativeVelocityY = ball1.dy - ball2.dy;
    float impulse = (relativeVelocityX * nx + relativeVelocityY * ny) * BALL_COLLISION_FACTOR;

    ball1.dx -= nx * impulse;
    ball1.dy -= ny * impulse;
    ball2.dx += nx * impulse;
    ball2.dy += ny * impulse;

    // Add the size reduction feature for the two balls colliding
    if (ball1.radius > BALL_RADIUS/2 && ball2.radius > BALL_RADIUS/2) {
        ball1.radius *= BOUNCE_FACTOR;
        ball2.radius *= BOUNCE_FACTOR;
        // Cambiar el color de las bolas cuando colisionan
        ball1.r = rand() % 256;
        ball1.g = rand() % 256;
        ball1.b = rand() % 256;
        ball2.r = rand() % 256;
        ball2.g = rand() % 256;
        ball2.b = rand() % 256;
    }
    ball1.start_time_collision = SDL_GetTicks();
    ball2.start_time_collision = SDL_GetTicks();
}