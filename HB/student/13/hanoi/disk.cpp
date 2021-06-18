#include "disk.hh"
#include "peg.hh"
#include <QWidget>
#include <QPainter>
#include <QDebug>

/* Initialize a disk.
 *
 * Parameters:
 *  index   		index of the disk
 *  color   		color of the disk
 *	containning_peg	peg containing the disk
 *	space_of_peg	the space that a peg can cover
 *	peg_width		width of peg
 *	parent		parent of this widget
 *
 * 
 */
disk::disk(int index, QBrush color, peg* containning_peg, int number_of_disks, int space_of_peg, int peg_width, QWidget* parent){
    this->index_ = index;
    this->brush_ = color;
    this->containning_peg_ = containning_peg;
    this->setParent(parent);
    this->resize(this->parentWidget()->width(),this->parentWidget()->height());
	// Calculate general value of disks include thickness, size difference
	// and biggest disk size
    setDiskParameters(number_of_disks, space_of_peg, peg_width);
	// Calculate location and size of a specific disk
    calculateDisk(index, containning_peg);
    show();
}

disk::~disk(){
}

/*
 * Returns:
 *  The disk size 
 */
int disk::getSize(){
    return size_;
}

/*
 * Returns:
 *  The peg containing this disk 
 */
peg* disk::getPeg(){
    return containning_peg_;
}

/* Calculate disk size difference based on the number of disk in source peg
 * and peg width
 * biggest disk based on space that a peg can cover
 *
 * Parameters:
 *  number_of_disks   	index of the peg
 *  space_of_peg   	the space of 1 peg can cover
 *	peg_width	number of disks on peg
 * 
 */
void disk::setDiskParameters(int number_of_disks, int space_of_peg, int peg_width){
   this->DISK_WIDTH_DIFFERENCE_ = (space_of_peg-4*peg_width)/(number_of_disks+3);
   this->DISK_THICKNESS_ = 15;
   this->BIGGEST_DISK_WIDTH_ = space_of_peg - 3*DISK_WIDTH_DIFFERENCE_;
}

/* Calculate disk size difference based on the number of disk in source peg
 * and peg width
 * biggest disk based on space that a peg can cover
 *
 * Parameters:
 *  number_of_disks   	index of the peg
 *  space_of_peg   	the space of 1 peg can cover
 *	peg_width	number of disks on peg
 * 
 */
void disk::calculateDisk(int index, peg* containning_peg){
    this->size_ = BIGGEST_DISK_WIDTH_ - index*DISK_WIDTH_DIFFERENCE_;
    this->x_coord_ = containning_peg->getPos()-size_/2;
    this->y_coord_ = SCENE_Y_COORDINATE - (index+1)*DISK_THICKNESS_;

}

/* Modify y coordinate of a disk to simulate it is lifted
 * 
 */
void disk::liftDisk(){
   y_coord_ = SCENE_Y_COORDINATE/8;
   update();
   //repaint();
}

/* Modify coordinates of a disk to simulate it is put on 
 * a peg
 */
void disk::putDisk(int index, peg* new_peg){
   x_coord_ = new_peg->getPos()-size_/2;
   y_coord_ = SCENE_Y_COORDINATE - (index+1)*DISK_THICKNESS_;
   update();
   //repaint();
}

/* Set up pen and brush to draw the disk
 *
 */
void disk::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)
    QPainter disk_painter(this);
    disk_painter.setRenderHint(QPainter::Antialiasing);

    QPen disk_pen(QColor(0, 0, 0));
    disk_pen.setWidth(1);
    disk_painter.setPen(disk_pen);

    disk_painter.setBrush(brush_);
	// draw disk as rounded rectangle with given size and position
    disk_painter.drawRoundedRect(x_coord_,y_coord_,size_,DISK_THICKNESS_,30,30,Qt::RelativeSize);

    raise();

}
