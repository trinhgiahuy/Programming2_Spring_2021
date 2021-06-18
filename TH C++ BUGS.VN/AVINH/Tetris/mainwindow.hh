#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QTimer>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

struct Coord
{
    int x = 0;
    int y = 0;

    Coord():
        x(0), y(0)
    {
    }

    Coord(int p_x, int p_y):
        x(p_x), y(p_y)
    {
    }
};

struct Square
{
    QGraphicsRectItem* block = NULL;
    Coord pos;
};

struct Tetromino
{
    std::vector<Square> squares = std::vector<Square>(4, Square());
    int type = 0;
    QColor tetro_color = Qt::white;

    Tetromino():
        squares(4, Square()),
        type(0),
        tetro_color(Qt::white)
    {
    }


};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:

    // Functions related to initialize the game.
    void initialize_window();
    void initialize_game();

    // Functions related to status of the game.
    void game_control();
    void update_game();
    void update_grid();
    int remove_full_row();
    void continue_game();
    bool is_over();
    void finish_game();
    int calculate_point(int num_row_remove, int num_turn);
    void update_user_score(int num_row_remove);
    void update_level();
    void pause_game();
    void quit_game();


    // Functions related to generate and display tetromino.
    void make_new_tetromino();
    void set_appear_position();
    void make_appear();
    void draw_nexttTetris();

    // Functions related to condition of moving of tetromino.
    bool can_move_down();
    bool can_move_left();
    bool can_move_right();

    // Functions related to move tetromino.
    void make_drop_down_automatic();
    void move_left();
    void move_right();
    void move_down();
    void move_soft_fall();
    void move_hard_fall();
    bool rotation_calculation();
    void rotate_counterclockwise();
    bool reflect_calculation();
    void reflect_vertical_axis();
    void exchange_tetromino();

    // Functions related to button on main window.
    void on_automatic_radio_button_toggled(bool checked);
    void on_manual_radio_button_toggled(bool checked);
    void on_start_game_push_button_clicked();
    void on_fall_button_clicked();

    // Fuctions related to score boards.
    void get_high_scores();
    void sort_score_board();
    void update_score_board();
    void display_score_board();
    void store_high_scores();

    // Function related to playing time.
    void display_playing_time();

    void set_player_name();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;

    QGraphicsScene* nextScene;

    QGraphicsScene* holdScene;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Number of levels in the game.
    const int NUM_LEVELS = 6;

    // File name to get the highest scores.
    // Remeber to build the proram in the same folder of this file.
    const std::string HIGHEST_SCORES_FILE = "highest_scores.txt";

    const int HIGHEST_SCORES_DISPLAY_NUM = 3;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods

    // For tetronimo continuous moving
    QTimer timer_;

    // For calculate time of playing.
    QTimer playing_timer_;

    int bottom_;
    int left_;
    int right_;
    int up_;

    bool game_started = false;
    bool game_running = false;
    bool game_over = false;

    Tetromino currentTetris;
    Tetromino nexttTetris;
    Tetromino holdTetris;

    bool can_hold;
    bool is_hold_empty;

    std::vector<Coord> HORIZONTAL_TETRIS = {Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(3, 0)};
    std::vector<Coord> LEFT_CORNER_TETRIS = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(2, 1)};
    std::vector<Coord> RIGHT_CORNER_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(2, 1), Coord(2, 0)};
    std::vector<Coord> SQUARE_TETRIS = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(1, 0)};
    std::vector<Coord> STEP_UP_RIGHT_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(1, 0), Coord(2, 0)};
    std::vector<Coord> PYRAMID_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(1, 0), Coord(2, 1)};
    std::vector<Coord> STEP_UP_LEFT_TETRIS = {Coord(0, 0), Coord(1, 0), Coord(1, 1), Coord(2, 1)};


    std::vector<std::vector<Coord>> coordinateData = {HORIZONTAL_TETRIS,  LEFT_CORNER_TETRIS,RIGHT_CORNER_TETRIS
    ,SQUARE_TETRIS ,STEP_UP_RIGHT_TETRIS,PYRAMID_TETRIS,STEP_UP_LEFT_TETRIS}
                                                  

    std::vector<int> bottomData = {0, 1, 1, 1, 1, 1, 1};
    std::vector<int> leftData = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> rightData = {3, 2, 2, 1, 2, 2, 2};
    std::vector<int> upData = {0, 0, 0, 0, 0, 0, 0};


    std::vector<std::vector<QString>> color_code_set = {{"#0444BF", "#0584F2", "#0AAFF1", "#EDF259", "#A79674"},
                                                        {"#04060F", "#03353E", "#0294A5", "#A79C93", "#C1403D"},
                                                        {"#BE3B45", "#F07995", "#F3F1F3", "#A58E87", "#BE302B"},
                                                        {"#A4A4BF", "#16235A", "2A3457", "#888C46", "#F2EAED"},
                                                        {"#55D9C0", "#C7F6EC", "#107050", "#02231C", "#4DD8AD"},
                                                        {"#C2D3DA", "#81A3A7", "#585A56", "#F1F3F2", "#272424"}};

    std::vector<int> LEVEL_THRESHOLD = {4000, 10000, 20000, 30000, 50000, 80000};

    // Highest scores read from HIGHEST_SCORES_FILE.
    // First element in the pair represents the player name.
    // First part of the second element represents the points and
    // the second part of second element is time of playing in second.
    std::vector<std::pair<std::string, std::pair<int, int>>> score_board_;


    bool play_automatic_;

    std::vector<std::vector<Square>> grid_;

    // For storing point and update level.
    std::string player_name_ = "";
    int playing_points_ = 0;
    int playing_level_ = 0;
    int playing_speed_ = 0;
    int total_lines_removed_ = 0;
    int tetris_points_ = 0;
    int num_turn_ = 0;


    // For display playing time.
    int min = 0;
    int sec = 0;
    int hour = 0;

};

#endif // MAINWINDOW_HH


