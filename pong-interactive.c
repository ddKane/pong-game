#include <ncurses.h>

#define HEIGHT 25
#define WIDTH 80
#define PADDLE 3
int main(void)
{
    initscr();   // включить ncurses-режим
    noecho();    // не показывать нажатые клавиши
    curs_set(0); // спрятать курсор
    nodelay(stdscr, TRUE);

    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int dy = 1;
    int dx = 1;
    int paddle_y = PADDLE;
    int paddle2_y = PADDLE;
    int score1 = 0, score2 = 0;
    while (1)
    {
        int c = getch();
        if (c == 'q')
            break;
        if (ball_y == 0)
            dy = -dy;
        if (ball_y == HEIGHT - 1)
            dy = -dy;
        ball_x = ball_x + dx;
        ball_y = ball_y + dy;
        if (ball_x == 2 && ball_y >= paddle_y && ball_y <= paddle_y + PADDLE - 1)
            dx = -dx;
        if (ball_x == WIDTH - 3 && ball_y >= paddle2_y && ball_y <= paddle2_y + PADDLE - 1)
            dx = -dx;
        if (ball_x == 0)
        {
            score2++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dx = -1;
        }
        if (ball_x == WIDTH - 1)
        {
            score1++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dx = 1;
        }
        if (score1 == 21 || score2 == 21)    
            break;
        if ((c == 'a' || c == 'A') && paddle_y > 0)
            paddle_y--;
        if ((c == 'z' || c == 'Z') && paddle_y < HEIGHT - 3)
            paddle_y++;
        if ((c == 'k' || c == 'K') && paddle2_y > 0)
            paddle2_y--;
        if ((c == 'm' || c == 'M') && paddle2_y < HEIGHT - 3)
            paddle2_y++;
        clear();

        mvaddch(ball_y, ball_x, 'o');
        mvaddch(0, WIDTH / 2 - 3, '0' + score1 / 10);
        mvaddch(0, WIDTH / 2 - 2, '0' + score1 % 10);
        mvaddch(0, WIDTH / 2 + 1, '0' + score2 / 10);
        mvaddch(0, WIDTH / 2 + 2, '0' + score2 % 10);

        for (int i = 0; i < PADDLE; i++)
        {
            mvaddch(paddle_y + i, 1, '|');
        }

        for (int i = 0; i < PADDLE; i++)
        {
            mvaddch(paddle2_y + i, WIDTH - 2, '|');
        }

        refresh();
        napms(1);
    }

    if (score1 == 21 || score2 == 21) {
        if (score1 == 21) {
            clear();
            mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "Player 1 win!!!");
        }
        if (score2 == 21) {
            clear();
            mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "Player 2 win!!!");
        }

        refresh();
        napms(5000);
    }

    endwin();
    return 0;
}