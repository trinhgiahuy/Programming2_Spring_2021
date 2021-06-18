#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <fstream>
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), play_automatic_(true)
{
    ui->setupUi(this);

    // We need a graphics Scene in which to draw rectangles.
    Scene = new QGraphicsScene(this);

    nextScene = new QGraphicsScene(this);

    holdScene = new QGraphicsScene(this);

    timer_.setSingleShot(false);
    playing_timer_.setSingleShot(false);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::automaticDrop);
    
    //connect(&playing_timer_, &QTimer::timeout, this, &MainWindow::display_playing_time);


    //connect(ui->player_name_line_edit, &QLineEdit::returnPressed, this, &MainWindow::set_player_name);
    //connect(ui->name_edit_push_button, &QPushButton::clicked, this, &MainWindow::set_player_name);

    connect(ui->pause_game_push_button, &QPushButton::clicked, this, &MainWindow::pause_game);
    connect(ui->close_game_push_button, &QPushButton::clicked, this, &MainWindow::quit_game);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.
    initialize_window();
    //get_high_scores();    trash.cpp

    initialize_game();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initialize_window()
{
    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(Scene);

    ui->nextTetrisgraphic_view->setGeometry(226, 80, 114 + 2, 60 + 2);

    ui->nextTetrisgraphic_view->setScene(nextScene);


    ui->holdgraphic_view->setGeometry(350, 150, 70 + 2, 60 + 2);
    ui->holdgraphic_view->setScene(holdScene);

    // The width of the Scene is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the SceneRect,
    // if its upper left corner is inside the SceneRect.
    Scene->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    nextScene->setSceneRect(0, 0, 114 - 1, 60 -1);

    holdScene->setSceneRect(0, 0, 60 - 1, 60- 1);

}
void MainWindow::initialize_game()
{
    Scene->clear();
    nextScene->clear();
    holdScene->clear();

    currentTetris = Tetromino();
    nextTetris  = Tetromino();
    holdTetris = Tetromino();
    gameBoard = std::vector<std::vector<Square>>(ROWS, std::vector<Square>(COLUMNS, Square()));

    leftLimit = 0;
    rightLimit = 0;
    upLimit = 0;
    bottomLimit = 0;
    currentTetris.color = nextTetris.color;


    // Time related information in the game.
    minute_ = 0;
    second_ = 0;
    hour_ = 0;

    // ui->number_hou_lcd->display(0);
    // ui->number_min_lcd->display(0);
    // ui->number_sec_lcd->display(0);

    // // Player related information in the game.
    // playing_level_ = 0;
    // total_lines_removed_ = 0;
    // playing_points_ = 0;
    // tetris_points_ = 0;
    // playing_speed_ = 800;
    // num_turn_ = 0;

    // Setup information for the game.
    // ui->start_game_push_button->setEnabled(true);
    // ui->automatic_radio_button->setChecked(play_automatic_);
    // ui->fall_button->setEnabled(true);
    // ui->name_edit_push_button->setEnabled(true);

    // ui->lines_remove_label->setText(QString("LINE\n0"));
    // ui->player_score_label->setText(QString("SCORE 0"));
    // ui->tetris_point_label->setText(QString("TETRIS\n0"));

    game_started = false;
    game_over = false;
    game_running = false;

    can_hold = true;
    is_holdempty = true;
    holdTetris.type = 0;

    nextTetris.type = distr(randomEng) % 7;

    int colorIndex = distr(randomEng) % 5;
    nextTetris.color = color_code_set.at(colorIndex);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // if (!timer_.isActive())
    // {
    //     if (game_running && !play_automatic_ &&
    //             event->key() == Qt::Key_T)
    //     {
    //         // Drop new tetromino by press key board.
    //         on_fall_button_clicked();
    //     }

    //     return;
    // }

    if (event->key() == Qt::Key_Left)
    {
        if (can_moveLeft())
        {
           // Move to the left one square.
           moveLeft();
        }

        return;
    }

    if (event->key() == Qt::Key_Right)
    {
        if (can_moveRight())
        {
            // Move to the right one square.
            moveRight();
        }

        return;
    }

    if (event->key() == Qt::Key_Up)
    {
        // Rotation
        rotate();

        // Used for calculate points.
        num_turn_ += 1;

        return;
    }

}

void MainWindow::make_new_tetromino()
{
    // Getting information to make new tetromino.
    currentTetris.type = nextTetris.type;
    currentTetris.color = nextTetris.color;

    num_turn_ = 0;

    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).pos.x = coord_info.at(currentTetris.type).at(i).x;
        currentTetris.squares.at(i).pos.y = coord_info.at(currentTetris.type).at(i).y;

        bottomLimit = bottomData.at(currentTetris.type);
        leftLimit = leftData.at(currentTetris.type);
        rightLimit = rightData.at(currentTetris.type);
        upLimit = upData.at(currentTetris.type);
    }

    // Set appearance position of new tetromino.
    set_appear_position();

    // Prepare information of the next tetromino.
    nextTetris.type = distr(randomEng) % 7;
    int colorIndex = distr(randomEng) % 5;
    nextTetris.color = color_code_set.at(colorIndex);
}

void MainWindow::set_appear_position()
{
    // Make appearing option.

    int deltaX = ((COLUMNS - 1) / 2) - (rightLimit - leftLimit) / 2;
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).pos.x += deltaX;
    }

    leftLimit += deltaX;
    rightLimit += deltaX;
}

void MainWindow::make_appear()
{
    if (!game_over)
    {
        // Choosing color for new tetromino from the color of this level.

        for (int i = 0; i < 4; ++i)
        {
            Coord c(currentTetris.squares.at(i).pos);
            currentTetris.squares.at(i).block = Scene->addRect(0, 0, SQUARE_SIDE,
                                                                  SQUARE_SIDE, QPen(Qt::black),
                                                                  QBrush(currentTetris.color));

            currentTetris.squares.at(i).block->setPos(c.x * SQUARE_SIDE,
                                                        c.y * SQUARE_SIDE);
        }
    }
    else
    {
        int moveUp = 1;
        while (bottomLimit - moveUp >= 0)
        {
            bool found_suitable_position = true;
            for (int i = 0; i < 4; ++i)
            {
                Coord c(currentTetris.squares.at(i).pos);
                c.y -= moveUp;

                // Check only part apper on the Scene.
                if (c.y >= 0)
                {
                    if (gameBoard.at(c.y).at(c.x).block!= NULL)
                    {
                        found_suitable_position = false;
                        break;
                    }
                }
            }

            if (found_suitable_position)
            {
                break;
            }

            // Try moving up one unit.
            moveUp += 1;
        }

        if (bottomLimit - moveUp >= 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                Coord c(currentTetris.squares.at(i).pos);

                c.y -= moveUp;

                if (c.y >= 0)
                {
                    gameBoard.at(c.y).at(c.x).block= Scene->addRect(0, 0,SQUARE_SIDE,
                                        SQUARE_SIDE, QPen(), QBrush(currentTetris.squares.at(i).block->brush()));

                    gameBoard.at(c.y).at(c.x).block->setPos(c.x * SQUARE_SIDE, c.y * SQUARE_SIDE);
                }
            }
        }
    }
}

void MainWindow::automaticDrop()
{
    if (can_moveDown())
    {
        moveDown();
    }
    else
    {
        timer_.stop();
        update_game();
    }
}

void MainWindow::moveLeft()
{
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).block->moveBy(-SQUARE_SIDE, 0);
        --currentTetris.squares.at(i).pos.x;
    }

    --leftLimit;
    --rightLimit;
}

void MainWindow::moveRight()
{
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).block->moveBy(SQUARE_SIDE, 0);
        ++currentTetris.squares.at(i).pos.x;
    }

    ++leftLimit;
    ++rightLimit;
}

void MainWindow::moveDown()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
       currentTetris.squares.at(i).block->moveBy(0, SQUARE_SIDE);
       ++currentTetris.squares.at(i).pos.y;
    }

    ++bottomLimit;
    ++upLimit;
}

bool MainWindow::rotation_calculation()
{
    std::vector<Coord> rotation_result;
    std::vector<std::pair<double, double>> coord_conversion;
    std::pair<double, double> rotation_center = std::make_pair(0, 0);

    // Convert coordinates to real number.
    for (int i = 0; i < 4; ++i)
    {
        Coord c(currentTetris.squares.at(i).pos);
        coord_conversion.push_back(std::make_pair(c.x + 0.5, c.y + 0.5));
        rotation_center.first += coord_conversion.at(i).first;
        rotation_center.second += coord_conversion.at(i).second;
    }

    rotation_center.first /= 4;
    rotation_center.second /= 4;

    // Rotation and convert coordinate back to integer.
    for (int i = 0; i < 4; ++i)
    {
        Coord c;
        c.x = ceil(rotation_center.first +
            (coord_conversion.at(i).second - rotation_center.second)) - 1;

        c.y = ceil(rotation_center.second -
            (coord_conversion.at(i).first - rotation_center.first)) - 1;

        rotation_result.push_back(c);
    }

    bool can_rotate = true;
    for (int i = 0; i < 4; ++i)
    {
        Coord c(rotation_result.at(i));

        // There is wall on the left.
        if (c.x < 0)
        {
            can_rotate = false;
            break;
        }

        // There is wall on the right.
        if (c.x >= COLUMNS)
        {
            can_rotate = false;
            break;
        }

        // There is wall above.
        if (c.y < 0)
        {
            can_rotate = false;
            break;
        }

        // There is wall below.
        if (c.y >= ROWS)
        {
            can_rotate = false;
            break;
        }

        // There there is other tetromino.
        if (gameBoard.at(c.y).at(c.x).block!= NULL)
        {
            can_rotate = false;
            break;
        }
    }

    if (can_rotate)
    {
        for (int i = 0; i < 4; ++i)
        {
            currentTetris.squares.at(i).pos.x = rotation_result.at(i).x;
            currentTetris.squares.at(i).pos.y = rotation_result.at(i).y;
        }
    }

    return can_rotate;
}

void MainWindow::game_control()
{
    // Set up other for the new game,
    // Start clock.
    playing_timer_.start(1000);

    make_new_tetromino();

    if (play_automatic_)
    {
        ui->fall_button->setDisabled(true);
        continue_game();
    }
}

void MainWindow::rotate()
{
    // Rotate 90 degree counter-clockwise.
    if (!rotation_calculation())
    {
        return;
    }

    int new_bottom = -1;
    int new_up = ROWS;
    int new_left = COLUMNS;
    int new_right = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (currentTetris.squares.at(i).pos.y < new_up)
        {
            new_up = currentTetris.squares.at(i).pos.y;
        }

        if (currentTetris.squares.at(i).pos.y > new_bottom)
        {
            new_bottom = currentTetris.squares.at(i).pos.y;
        }

        if (currentTetris.squares.at(i).pos.x < new_left)
        {
            new_left = currentTetris.squares.at(i).pos.x;
        }

        if (currentTetris.squares.at(i).pos.x > new_right)
        {
            new_right = currentTetris.squares.at(i).pos.x;
        }

        currentTetris.squares.at(i).block->setPos(currentTetris.squares.at(i).pos.x * SQUARE_SIDE,
                                                    currentTetris.squares.at(i).pos.y * SQUARE_SIDE);
    }

    // Update tetrimino.
    bottomLimit = new_bottom;
    upLimit = new_up;
    rightLimit = new_right;
    leftLimit = new_left;
}

bool MainWindow::can_moveDown()
{
    if (bottomLimit + 1 >= ROWS)
    {
        return false;
    }

    for (int i = 0; i < 4; ++i)
    {
        Coord c(currentTetris.squares.at(i).pos);

        if (gameBoard.at(c.y + 1).at(c.x).block!= NULL)
        {
            return false;
        }
    }

    return true;
}

bool MainWindow::can_moveLeft()
{
    // The border is on the left.
    if (leftLimit - 1 < 0)
    {
        return false;
    }

    // There are other tetrominos on the left.
    for (int i = 0; i < 4; ++i)
    {
        int x_index = currentTetris.squares.at(i).pos.x;
        int y_index = currentTetris.squares.at(i).pos.y;

        if (gameBoard.at(y_index).at(x_index - 1).block!= NULL)
        {
            return false;
        }
    }

    // Can move to the left.
    return true;
}

bool MainWindow::can_moveRight()
{
    // The border is on the right.
    if (rightLimit + 1 >= COLUMNS)
    {
        return false;
    }

    // There are other tetrominos on the right.
    for (int i = 0; i < 4; ++i)
    {
        int x_index = currentTetris.squares.at(i).pos.x;
        int y_index = currentTetris.squares.at(i).pos.y;

        if (gameBoard.at(y_index).at(x_index + 1).block!= NULL)
        {
            return false;
        }
    }

    // Can move to the left.
    return true;
}

void MainWindow::update_game()
{
    update_grid();

    int num_row_remove = remove_full_row();

    update_user_score(num_row_remove);

    update_score_board();

    if (play_automatic_)
    {
        continue_game();
    }
    else
    {
        ui->fall_button->setEnabled(true);
    }
}

void MainWindow::update_grid()
{
    // Update grid.
    for (int i = 0; i < 4; ++i)
    {
        int x_index = currentTetris.squares.at(i).pos.x;
        int y_index = currentTetris.squares.at(i).pos.y;

        gameBoard.at(y_index).at(x_index).pos = Coord(x_index, y_index);
        gameBoard.at(y_index).at(x_index).block= Scene->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, QPen(),
                                            QBrush(currentTetris.squares.at(i).block->brush()));

        gameBoard.at(y_index).at(x_index).block->setPos(x_index * SQUARE_SIDE,
                                                    y_index * SQUARE_SIDE);

        Scene->removeItem(currentTetris.squares.at(i).block);
    }
}

void MainWindow::continue_game()
{
    make_new_tetromino();

    if (is_over())
    {
        make_appear();
        finish_game();
        return;
    }

    timer_.start(playing_speed_);
    can_hold = true;
    game_running = true;
    make_appear();
    draw_nextTetris();
}

void MainWindow::draw_nextTetris()
{
    nextScene->clear();

    for (int i = 0; i < 4; ++i)
    {
        nextTetris.squares.at(i).pos.x = coord_info.at(nextTetris.type).at(i).x;
        nextTetris.squares.at(i).pos.y = coord_info.at(nextTetris.type).at(i).y;

        nextTetris.squares.at(i).block = nextScene->addRect(0, 0, SQUARE_SIDE / 1.2, SQUARE_SIDE / 1.2,
                                                      QPen(), QBrush(nextTetris.color));

        // Align the tetromino.
        Coord c(nextTetris.squares.at(i).pos);
        nextTetris.squares.at(i).block->setPos(c.x * SQUARE_SIDE + 30, c.y * SQUARE_SIDE + 10);
    }

}

bool MainWindow::is_over()
{
    for (int i = 0; i < 4; ++i)
    {
        Coord c(currentTetris.squares.at(i).pos);

        if (gameBoard.at(c.y).at(c.x).block!= NULL)
        {
            game_over = true;
        }
    }

    return game_over;
}

void MainWindow::finish_game()
{
    playing_timer_.stop();
    ui->game_message_label->setText("Game finish.");

    game_running = false;

    ui->start_game_push_button->setText("Play again");
    ui->start_game_push_button->setEnabled(true);

    ui->name_edit_push_button->setEnabled(true);

    // Store highest scores information to a file for next games.
    store_high_scores();
}




void MainWindow::on_start_game_push_button_clicked()
{
    initialize_game();

    ui->start_game_push_button->setDisabled(true);
    //ui->name_edit_push_button->setDisabled(true);
    //ui->game_message_label->setText("Game started.");

    game_started = true;
    game_running = true;

    playing_timer_.start(1000);

    if (play_automatic_)
    {
        ui->fall_button->setDisabled(true);
        continue_game();
    }

}

void MainWindow::on_fall_button_clicked()
{
    // Cannot drop multiple tetriminos at the same time.

    if (game_started)
    {
        ui->fall_button->setDisabled(true);
        continue_game();
    }
    else
    {
        ui->game_message_label->setText("Please start game.");
    }
}



