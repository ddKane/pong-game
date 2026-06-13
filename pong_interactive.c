#include <ncurses.h>

#define HEIGHT 25
#define WIDTH 80
#define PADDLE 3
#define WIN_SCORE 21

typedef struct {
    int ball_x;
    int ball_y;
    int dx;
    int dy;
    int paddle1_y;
    int paddle2_y;
    int score1;
    int score2;
} GameState;

void init_screen(void) {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

GameState init_game(void) {
    GameState g;
    g.ball_x = WIDTH / 2;
    g.ball_y = HEIGHT / 2;
    g.dx = 1;
    g.dy = 1;
    g.paddle1_y = PADDLE;
    g.paddle2_y = PADDLE;
    g.score1 = 0;
    g.score2 = 0;
    return g;
}

GameState move_ball(GameState g) {
    if (g.ball_y == 0 || g.ball_y == HEIGHT - 1) {
        g.dy = -g.dy;
    }
    g.ball_x = g.ball_x + g.dx;
    g.ball_y = g.ball_y + g.dy;
    return g;
}

GameState bounce_paddles(GameState g) {
    if (g.ball_x == 2 && g.ball_y >= g.paddle1_y && g.ball_y <= g.paddle1_y + PADDLE - 1) {
        g.dx = -g.dx;
    }
    if (g.ball_x == WIDTH - 3 && g.ball_y >= g.paddle2_y && g.ball_y <= g.paddle2_y + PADDLE - 1) {
        g.dx = -g.dx;
    }
    return g;
}

GameState update_score(GameState g) {
    if (g.ball_x == 0) {
        g.score2 = g.score2 + 1;
        g.ball_x = WIDTH / 2;
        g.ball_y = HEIGHT / 2;
        g.dx = -1;
    }
    if (g.ball_x == WIDTH - 1) {
        g.score1 = g.score1 + 1;
        g.ball_x = WIDTH / 2;
        g.ball_y = HEIGHT / 2;
        g.dx = 1;
    }
    return g;
}

GameState move_paddles(GameState g, int key) {
    if ((key == 'a' || key == 'A') && g.paddle1_y > 0) {
        g.paddle1_y = g.paddle1_y - 1;
    }
    if ((key == 'z' || key == 'Z') && g.paddle1_y < HEIGHT - PADDLE) {
        g.paddle1_y = g.paddle1_y + 1;
    }
    if ((key == 'k' || key == 'K') && g.paddle2_y > 0) {
        g.paddle2_y = g.paddle2_y - 1;
    }
    if ((key == 'm' || key == 'M') && g.paddle2_y < HEIGHT - PADDLE) {
        g.paddle2_y = g.paddle2_y + 1;
    }
    return g;
}

void draw_scoreboard(GameState g) {
    mvaddch(0, WIDTH / 2 - 3, '0' + g.score1 / 10);
    mvaddch(0, WIDTH / 2 - 2, '0' + g.score1 % 10);
    mvaddch(0, WIDTH / 2 + 1, '0' + g.score2 / 10);
    mvaddch(0, WIDTH / 2 + 2, '0' + g.score2 % 10);
}

void draw_paddles(GameState g) {
    for (int i = 0; i < PADDLE; i = i + 1) {
        mvaddch(g.paddle1_y + i, 1, '|');
    }
    for (int i = 0; i < PADDLE; i = i + 1) {
        mvaddch(g.paddle2_y + i, WIDTH - 2, '|');
    }
}

void draw_frame(GameState g) {
    clear();
    mvaddch(g.ball_y, g.ball_x, 'o');
    draw_scoreboard(g);
    draw_paddles(g);
    refresh();
}

int is_game_over(GameState g) { return g.score1 == WIN_SCORE || g.score2 == WIN_SCORE; }

void show_winner(GameState g) {
    clear();
    if (g.score1 == WIN_SCORE) {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "Player 1 win!!!");
    }
    if (g.score2 == WIN_SCORE) {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "Player 2 win!!!");
    }
    refresh();
    napms(5000);
}

int main(void) {
    init_screen();
    GameState g = init_game();
    int running = 1;
    while (running) {
        int key = getch();
        if (key == 'q') {
            running = 0;
        } else {
            g = move_ball(g);
            g = bounce_paddles(g);
            g = update_score(g);
            if (is_game_over(g)) {
                running = 0;
            } else {
                g = move_paddles(g, key);
                draw_frame(g);
                napms(50);
            }
        }
    }
    if (is_game_over(g)) {
        show_winner(g);
    }
    endwin();
    return 0;
}