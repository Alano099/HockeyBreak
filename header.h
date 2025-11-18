#include "raylib.h"

typedef struct Retangulo{

    Rectangle rect;
    float vel;

}Retangulo;

typedef struct Bola {
    Rectangle rect;
    Vector2 vel; // Velocidade X e Y
} Bola;

Retangulo inicializarRec(float x, float y, float h, float w,float v);
Bola inicializarBola(float x, float y, float size, Vector2 v);