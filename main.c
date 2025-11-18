#include "raylib.h"
#include "raymath.h"

#define BARRA 150 // O limite de retângulos que vamos guardar
#define MAX_PROJETEIS 1000 // Nosso "estoque"

typedef struct Disco {
    Vector2 posicao;    // Onde ele está na mesa (x, y)
    Vector2 velocidade; // O vetor de movimento (quanto ele anda em x e y por frame)
    float raio;         // Tamanho do disco (para colisão)
    bool ativo;         // Se ele existe ou não
    
    
} Disco;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const Vector2 jogadorPos = { screenWidth/2,screenHeight/2};


    InitWindow(screenWidth, screenHeight, "Desenhando e Guardando - Raylib");
    SetTargetFPS(60);

    Rectangle rec = { jogadorPos.x, jogadorPos.y, 50, 50 };
    Disco disc;

    Disco projeteis[MAX_PROJETEIS]; 


    for (int i = 0; i < MAX_PROJETEIS; i++) {
        projeteis[i].ativo = false;
    }

    Vector2 pivo = { 25, 25 };
    float mousePos;

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---

        Vector2 delta = Vector2Subtract(GetMousePosition(), jogadorPos);

        float angulo = atan2f(delta.y, delta.x) * RAD2DEG;

        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // LOOP DE BUSCA: Procura o primeiro slot vazio
            for (int i = 0; i < MAX_PROJETEIS; i++)
            {
                if (!projeteis[i].ativo) // Achou um slot livre?
                {
                    projeteis[i].ativo = true;
                    projeteis[i].posicao = jogadorPos; // Sai do jogador
                    
                    // Calcula a direção (Matemática vetorial que vimos antes)
                    Vector2 mousePos = GetMousePosition();
                    Vector2 direcao = Vector2Subtract(mousePos, jogadorPos);
                    direcao = Vector2Normalize(direcao);
                    
                    float velocidadeTiro = 600.0f;
                    projeteis[i].velocidade = Vector2Scale(direcao, velocidadeTiro);
                    projeteis[i].raio = 10.0f;

                    break; // IMPORTANTE: Pare o loop assim que atirar uma bala!
                        // Se não tiver esse break, ele vai disparar as 1000 de uma vez.
                }
            }
        }
       
       for (int i = 0; i < MAX_PROJETEIS; i++){
            if (projeteis[i].ativo)
            {
                // Move a bala
                projeteis[i].posicao.x += projeteis[i].velocidade.x * dt;
                projeteis[i].posicao.y += projeteis[i].velocidade.y * dt;

               
                if (projeteis[i].posicao.x < 0 || projeteis[i].posicao.x > screenWidth ||
                    projeteis[i].posicao.y < 0 || projeteis[i].posicao.y > screenHeight)
                {
                    projeteis[i].ativo = false;
                }
            }
        }


        // --- DESENHO ---
        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            
            DrawRectanglePro(rec,pivo,angulo,BLUE);

            DrawRectangleLines(750,10,20,150,WHITE);
            

           for (int i = 0; i < MAX_PROJETEIS; i++)
            {
                if (projeteis[i].ativo)
                {
                    DrawCircleV(projeteis[i].posicao, projeteis[i].raio, BLACK);
                }
            }

           

        EndDrawing();
    }

    

    CloseWindow();
    return 0;
}