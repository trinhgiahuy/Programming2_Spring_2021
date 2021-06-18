 /* Tower of Hanoi Project!
 * In this project, I implemented:
 *	+ 2 subclasses: peg, disk to manage information 
 *	+ a vector of peg is used as database (disk data belongs to peg)
 *	+ player is able to choose source and target peg
 *  + move counter to count how many move that player has made
 *	+ history scene to display the moves that were made
 *		and a vector contain history moves.
 *	+ timer to show the time of game
 *	+ an auto-play mode
 *
 * Student's name: Anh Huy Bui
 * Student's number: 293257
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
	
	// initiate scene for the game and history
    scene_ = new QGraphicsScene(this);
    history_scene_ = new QGraphicsScene(this);
    history_text_ = new QGraphicsTextItem;
    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);
    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);
	
	//set button locations
    setButtonGeometry();
	//set color and text for the time and game status
    initializeText();

	// set parameters for history scene and initial text
    ui_->historyView->setScene(history_scene_);
    QRect history_rect = ui_->historyView->rect();
    history_scene_->setSceneRect(history_rect.x(),history_rect.y(),
                                 history_rect.width(),history_rect.height()*5);
    history_text_ = history_scene_->addText("");
    // Timer is used to get the time and in autoplay mode
	// timer cycle is 1 second
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::update_Time);
	
	// First guidance
    ui_->label_Guide->setText("Click button to choose a source peg");
}

MainWindow::~MainWindow()
{
    delete ui_;
}

/* Initialize text of time and status with colors
 *
 */
void MainWindow::initializeText(){
	// add color for time 
    QPalette pal_for_time = ui_->label_Time->palette();

    pal_for_time.setColor(QPalette::Normal, QPalette::WindowText, Qt::blue);

    ui_->label_Time->setAutoFillBackground(true);
    ui_->label_Time->setPalette(pal_for_time);
    ui_->label_Time->setText("0 : 0");

	// add color for status 
    QPalette pal_for_status = ui_->label_Status->palette();

    pal_for_status.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);

    ui_->label_Status->setAutoFillBackground(true);
    ui_->label_Status->setPalette(pal_for_status);
    ui_->label_Status->setText("Choose source peg");
}

/* Set location and size for 3 buttons that control 3 pegs
 *
 */
void MainWindow::setButtonGeometry(){
    ui_->button_A->setGeometry(10,100,SPACE_OF_PEG,160  );
    ui_->button_B->setGeometry(SPACE_OF_PEG+ 10,100,SPACE_OF_PEG,160  );
    ui_->button_C->setGeometry(2*SPACE_OF_PEG + 10,100,SPACE_OF_PEG,160  );
}

/* Initialize a vector of 3 pegs in orders, from left to right,
 * button A, B, C
 */
void MainWindow::initializePeg(){
    peg* temp_peg = nullptr;
	// create a for-loop from 0 to 2
    for (int i=0; i <3; ++i){
		// if it is source peg, get the color of source peg
        if (i == source_peg_index_){
            temp_peg = new peg(source_peg_index_,SPACE_OF_PEG,MAX_DISK, 
								SOURCE_PEG_COLOR ,ui_->graphicsView);

        }
		// if it is target peg, get the color of target peg
        else if (i == target_peg_index_){
            temp_peg = new peg(target_peg_index_,SPACE_OF_PEG,0, 
								TARGET_PEG_COLOR ,ui_->graphicsView);
        }
		// if it is auxiliary peg, get the color of auxiliary peg
        else{
            aux_peg_index_ = i;
            temp_peg = new peg(i,SPACE_OF_PEG,0, 
								OTHER_PEG_COLOR, ui_->graphicsView);
        }
        peg_.push_back(temp_peg);
    }
}

/* Timer slot for:
 * + giving time of the game from first move to victory
 * + executing each auto-play action each cycle
 */

void MainWindow::update_Time()
{
    if (timer_->isActive()){
		// increase time with 1 second
        current_time_ += 1;
		// calculate the minutes and seconds at that point of time
        QString minutes = QString::fromStdString(std::to_string(current_time_/60));
        QString seconds = QString::fromStdString(std::to_string((current_time_/1)%60));
        ui_->label_Time->setText(minutes + " : " +seconds);
    }
	// if auto-play mode is activated
    if (auto_play_flag_){
        static size_t step = 0;
		// get 1 moving action in the auto-play data and execute it
        std::pair<int,int> moving_action = autoplay_moves_.at(step);
        controlState(moving_action.first);
        controlState(moving_action.second);
		// move to next action, if reaching the end, stop
        if(++step ==autoplay_moves_.size())
            auto_play_flag_ = false;
    }

}

/* Calculate moves to solve the game :
 * Parameters:
 *  disk_num   	number of disks that is used in the game
 *  from   		source peg index
 *	to			target peg index
 *  aux 		auxiliary peg index
 *
 * Returns:
 *  moveAutoplay 	vector contains pairs of peg to "take disk from" and "put disk on"
 */
void MainWindow::moveAutoplay(int disk_num, int from,  int to, int aux){
    if(disk_num <1){
        return;
    }else{
        moveAutoplay(disk_num-1,from,aux,to);
        std::pair<int,int> move = {from,to};
        autoplay_moves_.push_back(move);
        moveAutoplay(disk_num-1,aux,to,from);
    }

}

/* Enable and disable buttons in different situations
 * 
 */
void MainWindow::changeButtonStates(){
	// If player is choosing a source peg
    if (game_state_ == STATES_::SCOURCE_PEG_CHOSING){
		// disable button of the chosen source peg to start
		// choosing target peg in order for not choosing the same peg 
		// for source and target
        if (source_peg_index_ == 0){
             ui_->button_A->setEnabled(false);
        }
        if (source_peg_index_ == 1){
             ui_->button_B->setEnabled(false);
        }
        if (source_peg_index_ == 2){
             ui_->button_C->setEnabled(false);
        }

    }
	// Disable all buttons when victory
    else if (game_state_ == STATES_::VICTORY){
        ui_->button_A->setEnabled(false);
        ui_->button_B->setEnabled(false);
        ui_->button_C->setEnabled(false);
    }
	// if player is playing
    else{
		// if a disk is lifted
		// check possible peg that the lifted disk can be put down
		// following the rule of the game, 
		// disable button if the move is not possible
        if(disk_picked_){
            if (picked_disk_->getSize() > peg_.at(0)->getSizeOfTopDisk()){
                ui_->button_A->setEnabled(false);
            }
            if (picked_disk_->getSize() > peg_.at(1)->getSizeOfTopDisk()){
                ui_->button_B->setEnabled(false);
            }
            if (picked_disk_->getSize() > peg_.at(2)->getSizeOfTopDisk()){
                ui_->button_C->setEnabled(false);
            }
        }
		// no disk is lifted
        else{
            ui_->button_A->setEnabled(true);
            ui_->button_B->setEnabled(true);
            ui_->button_C->setEnabled(true);
        }
    }
	// disable all buttons in auto-play mode
	if (!auto_play_flag_ and 
			(game_state_ == STATES_::PLAYING or
			next_state_ == STATES_::PLAYING)){
		ui_->button_AutoPlay->setEnabled(false);
	}
    if (auto_play_flag_ and 
		(next_state_ == STATES_::READY or game_state_ == STATES_::PLAYING)){
        ui_->button_A->setEnabled(false);
        ui_->button_B->setEnabled(false);
        ui_->button_C->setEnabled(false);
    }
}

/* Display history move:
 * Parameters:
 *  making_move   	the action of player 
 *
 */
void MainWindow::setHistoryText(std::pair<int,int> making_move){
    QString from = "";
    QString to = "";
	// first element is the original peg of a moved disk
	// second element is the destination peg of that disk
    if (making_move.first == 0){
        from = "A";
    }
    if (making_move.second == 0){
        to = "A";
    }
    if (making_move.first == 1){
        from = "B";
    }
    if (making_move.second == 1){
        to = "B";
    }
    if (making_move.first == 2){
        from = "C";
    }
    if (making_move.second == 2){
        to = "C";
    }
    static QString item5 = "";
    item5 += "\n  Move from " + from + " to "+ to ;
    history_text_->setPlainText(item5);
}

/* Display move count compare to the minimal number of moves:
 *
 */
void MainWindow::setMovingText(){
	// the number of moves is size of history
    QString number_of_move = 
			QString::fromStdString(std::to_string(history_data_.size()));
	// the minial number of moves is size of the auto play data
    QString number_of_suggested_move = 
			QString::fromStdString(std::to_string(autoplay_moves_.size()));
    ui_->label_Move_count->setText(number_of_move + "/" + number_of_suggested_move);
}

/* Check if the player won
 *
 */
bool MainWindow::checkVictory(){
	// compare the disk number of target peg and MAX_DISK
    return peg_.at(static_cast<size_t> (target_peg_index_))->getDiskNum()
				== MAX_DISK;
}

/* Main Control of the game
 * Parameters:
 *  peg_pick   	the button/peg that is clicked/chosen
 */
void MainWindow::controlState(int peg_pick){
	// initial stage is for choosing source peg
    if (game_state_ == STATES_::SCOURCE_PEG_CHOSING){
        source_peg_index_ = peg_pick;
        next_state_ = STATES_::TARGET_PEG_CHOSING;
        ui_->label_Status->setText("Choose Target Peg");
        ui_->label_Guide->setText("Click button to choose a target peg");
    }
	// second stage is for choosing target peg
    if (game_state_ == STATES_::TARGET_PEG_CHOSING){
        target_peg_index_ = peg_pick;

        initializePeg();
        moveAutoplay(MAX_DISK, source_peg_index_,  target_peg_index_, aux_peg_index_);
        next_state_ = STATES_::READY;
        ui_->label_Status->setText("Ready");
        ui_->label_Guide->setText("Click auto play if you want");
        if(auto_play_flag_) {
            next_state_ = STATES_::PLAYING;
            timer_->start();
            ui_->label_Status->setText("Playing");
        }



    }
	// next stage is ready, timer will start when player make the first move
	// state will change to playing
	// auto-play button can only be clicked before making the first move
    if (game_state_ == STATES_::READY or game_state_ == STATES_::PLAYING){
        if (game_state_ == STATES_::READY){
            timer_->start();
            next_state_ = STATES_::PLAYING;
            ui_->label_Status->setText("Playing");
        }
        std::size_t peg_index = static_cast<size_t> (peg_pick);
		// if no disk is lifted
        if(!disk_picked_){
			// if there is disk on chosen peg
            if (peg_.at(peg_index)->getDiskNum() != 0){
				// lift top disk of that peg and record to history
                picked_disk_ = peg_.at(peg_index)->liftTopDisk();
                disk_picked_ = true;
                history_move_.first = peg_pick;
            }
        }
		// if there is a disk that is lifted 
        else{
			// if the destination peg has no disk
			// or the its top disk is larger in size
            if (peg_.at(peg_index)->getDiskNum() == 0  or
				picked_disk_->getSize() < peg_.at(peg_index)->getSizeOfTopDisk()){
				//put the lifted disk into that peg and remove lifted disk
                peg_.at(peg_index)->addNewDisk(picked_disk_);
                picked_disk_ = nullptr;
                disk_picked_ = false;
				//when one disk is lifted and put, a complete move has been done
				// record to history and display it
                history_move_.second = peg_pick;
                setHistoryText(history_move_);
                history_data_.push_back(history_move_);
				// moving count increase by 1
                setMovingText();
            }

        }
		ui_->label_Guide->setText("Target peg is the orange one");
		// check if player has won the game
        if (checkVictory()){
			// change state and text
			// stop timer
            game_state_ = STATES_::VICTORY;
            next_state_ = STATES_::VICTORY;
            ui_->label_Status->setText("VICTORY");
            timer_->stop();
        }
    }
	// update button state
    changeButtonStates();
    game_state_ = next_state_;
}
// button slots put peg index to main control
void MainWindow::on_button_A_clicked()
{
    controlState(0);
}

void MainWindow::on_button_B_clicked()
{
    controlState(1);
}

void MainWindow::on_button_C_clicked()
{
    controlState(2);
}

// auto play button slot
void MainWindow::on_button_AutoPlay_clicked()
{
	// activate auto play and disable the button
    if(!auto_play_flag_) {
        auto_play_flag_ = true;
        ui_->button_AutoPlay->setEnabled(false);
		// if the game is in ready state 
		//(source and target have been chosen)
		// change the state to playing immediately
		// (instead of waiting for player's first move)
        if (game_state_ == STATES_::READY){
            timer_->start();
            next_state_ = STATES_::PLAYING;
            ui_->label_Status->setText("Playing");
        }
    }


}
