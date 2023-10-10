#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>  // Pour la fonction sleep

// Taille de la grille
#define GRID_WIDTH 20
#define GRID_HEIGHT 10

// Taille maximale du serpent
#define MAX_LENGTH 100

// Codes de direction
#define UP 'e'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

// Structures de données pour le serpent et la nourriture
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[MAX_LENGTH];
    int length;
    char direction;
} Snake;

Point food;
bool gameOver = false;

// Fonction pour générer de la nourriture aléatoirement
void generateFood() {
    food.x = rand() % GRID_WIDTH;
    food.y = rand() % GRID_HEIGHT;
}

// Fonction pour dessiner la grille
void drawGrid(Snake snake) {
    system("clear");  // Efface l'écran (commande pour macOS)

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            // Dessine la nourriture
            if (x == food.x && y == food.y) {
                putchar('F');
            }
            // Dessine la tête du serpent
            else if (x == snake.body[0].x && y == snake.body[0].y) {
                putchar('O');
            }
            // Dessine le corps du serpent
            else {
                bool isBodyPart = false;
                for (int i = 1; i < snake.length; i++) {
                    if (x == snake.body[i].x && y == snake.body[i].y) {
                        putchar('o');
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart) {
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }
}

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    Snake snake;
    snake.length = 1;
    snake.body[0].x = GRID_WIDTH / 2;
    snake.body[0].y = GRID_HEIGHT / 2;
    snake.direction = RIGHT;

    generateFood();

    while (!gameOver) {
        // Gestion de l'entrée utilisateur
        char input;
        scanf(" %c", &input);

        // Mise à jour de la direction
        switch (input) {
            case UP:
                if (snake.direction != DOWN) {
                    snake.direction = UP;
                }
                break;
            case DOWN:
                if (snake.direction != UP) {
                    snake.direction = DOWN;
                }
                break;
            case LEFT:
                if (snake.direction != RIGHT) {
                    snake.direction = LEFT;
                }
                break;
            case RIGHT:
                if (snake.direction != LEFT) {
                    snake.direction = RIGHT;
                }
                break;
        }

        // Mise à jour de la position du serpent
        Point newHead = snake.body[0];
        switch (snake.direction) {
            case UP:
                newHead.y--;
                break;
            case DOWN:
                newHead.y++;
                break;
            case LEFT:
                newHead.x--;
                break;
            case RIGHT:
                newHead.x++;
                break;
        }

        // Vérification des collisions avec la nourriture
        if (newHead.x == food.x && newHead.y == food.y) {
            snake.length++;
            generateFood();
        }

        // Déplacement du serpent (mise à jour du corps)
        for (int i = snake.length - 1; i > 0; i--) {
            snake.body[i] = snake.body[i - 1];
        }
        snake.body[0] = newHead;

        // Vérification des collisions avec les bords de la grille
        if (newHead.x < 0 || newHead.x >= GRID_WIDTH || newHead.y < 0 || newHead.y >= GRID_HEIGHT) {
            gameOver = true;
        }

        // Vérification des collisions avec le corps du serpent
        for (int i = 1; i < snake.length; i++) {
            if (newHead.x == snake.body[i].x && newHead.y == snake.body[i].y) {
                gameOver = true;
                break;
            }
        }

        // Dessin de la grille
        drawGrid(snake);

        // Pause pour contrôler la vitesse du jeu
        usleep(100000);  // 100 millisecondes
    }

    printf("Game Over! Score: %d\n", snake.length - 1);

    return 0;
}
