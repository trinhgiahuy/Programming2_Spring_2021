#ifndef DISK_HH
#define DISK_HH
#include<QWidget>
#include <QGraphicsItem>
class peg;
class disk: public QWidget
{
private:
	// disk index (where it is on peg)
    int index_ = 0;
	// location and size of disk (for drawing)
    int x_coord_ = 0;
    int y_coord_ = 0;
    int size_ = 0;
	// color of disk
    QBrush brush_;
	// which peg is containing this disk
    peg* containning_peg_;
	
	// parent (graphicView scene parameters)
    const int SCENE_Y_COORDINATE = 260;
    const int SCENE_X_COORDINATE = 680;

	// Disk size, will be  calculated when disk is defined
    int BIGGEST_DISK_WIDTH_ = INT_MAX;
    int DISK_THICKNESS_ = 0;
    int DISK_WIDTH_DIFFERENCE_ = 0;
	
public:
	// define a disk
    disk(int index, QBrush color, peg* containning_peg, 
		 int number_of_disks, int space_of_peg, int peg_width, QWidget* parent);
	// Return disk size
    int getSize();
	// Return which peg is containing this disk
    peg* getPeg();
	// Calculate general value of disks include thickness, size difference
	// and biggest disk size
    void setDiskParameters(int number_of_disks, int space_of_peg, int peg_width);
	// Calculate location and size of a specific disk
    void calculateDisk(int index, peg* containning_peg);
	// Modify value to draw a lifted disk
    void liftDisk();
	// Modify value to draw a lifted disk is now put on a peg
    void putDisk(int index, peg* new_peg);
    void paintEvent(QPaintEvent *event);
    ~disk();

};
#endif // DISK_HH
