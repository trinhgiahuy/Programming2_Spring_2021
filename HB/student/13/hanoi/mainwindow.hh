#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <map>
#include <vector>
#include "disk.hh"
#include "peg.hh"
class peg;
class disk;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	// This function sets 3 buttons of 3 pegs
    void setButtonGeometry();
	// This generates initial colored text
    void initializeText();
	// This generates initial peg
    void initializePeg();
	// Calculate autoplay algorithm
    void moveAutoplay(int disk_num, int from,  int to, int aux);
	// Write history on scene
    void setHistoryText(std::pair<int,int> making_move);
	// Count the move and compare to the suggested ones
    void setMovingText();
	// Check if the game is won
    bool checkVictory();
	// main control of the game
    void controlState(int button_index);
	// Enable and disable buttons in different situations
    void changeButtonStates();

private slots:

    void update_Time();

    void on_button_A_clicked();

    void on_button_B_clicked();

    void on_button_C_clicked();

    void on_button_AutoPlay_clicked();

private:
    Ui::MainWindow *ui_;
	
	// define max disks on one peg
	// Modify this will change the number of disks on a peg
	// MAX_DISK <= 9 due to limited color range of disk (in peg.hh)
	const int MAX_DISK = 7;
	
	// game scene
    QGraphicsScene* scene_;          
	// scene to show history
    QGraphicsScene* history_scene_;
	// text to write on history scene
    QGraphicsTextItem* history_text_;
	// timer is used to get time of the game and autoplay mode
    QTimer* timer_;          

	// parameters of the scene 
	const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
	// space (x coordinate) of 1 peg 
    const int SPACE_OF_PEG = BORDER_RIGHT/3;
	// peg color
    const QColor SOURCE_PEG_COLOR = Qt::white;
    const QColor TARGET_PEG_COLOR = QColor(255,128,0);
    const QColor OTHER_PEG_COLOR = QColor(98,38,30);

	// current time in seconds
    unsigned int current_time_ = 0;
    
	// define different types of peg 
    int source_peg_index_ = 0;
    int target_peg_index_ = 0;
    int aux_peg_index_ = 0;
	
	// flag to check auto play is chosen
    bool auto_play_flag_ = false;
	
    // game states
    enum class STATES_ {SCOURCE_PEG_CHOSING, TARGET_PEG_CHOSING, READY, PLAYING, VICTORY};
    STATES_ game_state_ = STATES_::SCOURCE_PEG_CHOSING;
    STATES_ next_state_ = STATES_::SCOURCE_PEG_CHOSING;
	
	// flag to check if any disk is lifted
    bool disk_picked_ = false;   
	
	// lifted disk data
    disk* picked_disk_ = nullptr;
	
	// all history data is stored 
    std::vector<std::pair<int,int>> history_data_;
	// elements of history data which includes 2 int variables 
	// of "moving from which peg" and "moving to which peg"
    std::pair<int,int> history_move_;
	
	// this contains all move that should be done in autoplay mode,
	// which includes 2 int variables 
	// of "moving from which peg" and "moving to which peg"
    std::vector<std::pair<int,int>> autoplay_moves_;
	
	// peg data
    std::vector<peg*> peg_;
};

#endif // MAINWINDOW_HH
