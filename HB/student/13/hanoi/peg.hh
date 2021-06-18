#ifndef PEG_HH
#define PEG_HH
#include<QWidget>
#include "disk.hh"
#include <map>
#include <vector>
class disk;
class peg: public QWidget
{
private:
	// parameters of a peg:
	// index, space (x coordinates), position, color
	// vector of all disks in that peg
    int index_;
    int space_; 
    int peg_pos_ = 0;
    QColor peg_color_ = Qt::white;
    std::vector<disk*> disk_in_peg_;
	
	// color to initialize all disks in the peg
    const std::vector<QColor> COLOR_ = { Qt::white,  Qt::black, Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray};

    // scene parameters
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
	// size of peg
	const int PEG_WIDTH_ = 10;
    const int PEG_HEIGHT = 3*BORDER_DOWN/4;

public:
	// define a peg
    peg(int index, int space, int disk_num, QColor peg_color, QWidget * parent);
	// return index of peg
    int getIndex();
	// return position (x coordinates in scene) of peg 
    int getPos();
	// return how many disks that peg contains
    int getDiskNum();
	// lift the top disk of peg
    disk* liftTopDisk();
	// return size of top disk
    int getSizeOfTopDisk();
	// receive the new disk (a lifted disk is put down on this peg)
    void addNewDisk(disk* new_disk);
	// paint the peg
    void paintEvent(QPaintEvent *event);
     ~peg();


};
#endif // PEG_HH
