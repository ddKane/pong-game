#include <stdio.h>


int main(void) {
    int paddle_y = 3;
    int paddle2_y = 3;
    int ball_x = 40;
    int ball_y = 12;
    int dx = 1;
    int dy = 1;
    char field[25][80];
    int score1 = 0;
    int score2 = 0;                  
    while (1) {
        int c = getchar();
        ball_y += dy;
        ball_x += dx;
        
        if (ball_y == 0) dy = - dy;
        if (ball_y == 24) dy = -dy;
        
        if (ball_x == 2 && ball_y >= paddle_y && ball_y <= paddle_y + 2)
            dx = -dx;
        if (ball_x == 77 && ball_y >= paddle2_y && ball_y <= paddle2_y + 2) 
            dx = -dx;
        if (ball_x == 0) {
            score2++;
            ball_x = 40;
            ball_y = 12;
            dx = -1;
        }
        if (ball_x == 79) {
            score1++;
            ball_x = 40;
            ball_y = 12;
            dx = 1;
        }
        if ((c == 'a' || c == 'A') && paddle_y > 0) paddle_y--;
        if ((c == 'z' || c == 'Z') && paddle_y < 22) paddle_y++;
        if ((c == 'k' || c == 'K') && paddle2_y > 0) paddle2_y--;
        if ((c == 'm' || c == 'M') && paddle2_y < 22) paddle2_y++;
        if (c == 'q') break;

        for (int y = 0; y < 25; y++)
            for (int x = 0; x < 80; x++)
                field[y][x] = ' ';
                
        field[ball_y][ball_x] = 'o'; 
        field[0][41] = '0' + score2 / 10;
        field[0][42] = '0' + score2 % 10;
        field[0][38] = '0' + score1 / 10;
        field[0][39] = '0' + score1 % 10;
        for (int i = 0; i < 3; i++) {
            field[paddle_y + i][1] = '|';
        }

        for (int i = 0; i < 3; i++) {
            field[paddle2_y + i][78] = '|';
        }
        
        for (int y = 0; y < 25; y++) {
            for (int x = 0; x < 80; x++)
                putchar(field[y][x]);
            putchar('\n');          
        }

        if (score1 == 1 || score2 == 1) {
            if (score1 == 1) printf("Player 1 wins!\n");
        else printf("Player 2 wins!\n");
        break;
}
    }

    return 0;
}