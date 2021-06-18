#include "peg.hh"
#include "disk.hh"
#include <QWidget>
#include <QPainter>
#include <QDebug>
/* Initialize a peg.
 *
 * Parameters:
 *  index   	index of the peg
 *  space   	the space of 1 peg can cover
 *	disk_num	number of disks on peg
 *	peg_color	color of peg
 *	parent		parent of this widget
 *
 * 
 */
peg::peg(int index, int space, int disk_num, QColor peg_color, QWidget * parent){
    this->index_ = index;
    this->space_ = space;
	// position of peg is calculated base on its index and space given
    this->peg_pos_= index*space + space/2;
    this->peg_color_ = peg_color;
    this->setParent(parent);
	// resize space of this widget to match graphicView scene
    this->resize(this->parentWidget()->width(),this->parentWidget()->height());
	// define disks on peg in correct order and different color
	// the game defines only 9 colors for 9 disks, so maximum 9 disks 
	// can be given
	if (disk_num <= 9){
		for(int i = 0; i < disk_num; ++i){
			QColor chosen_color = COLOR_.at(static_cast<size_t>(i));
			disk* new_disk =
				new disk(i, chosen_color, this, disk_num, space, PEG_WIDTH_, parent);
			disk_in_peg_.push_back(new_disk);
		}
	}
    
    show();
}
peg::~peg(){

}
/*
 * Returns:
 *  The peg index.
 */
int peg::getIndex(){
    return index_;
}

/*
 * Returns:
 *  The peg position.
 */
int peg::getPos(){
    return peg_pos_;
}

/*
 * Returns:
 *  The number of disks on peg.
 */
int peg::getDiskNum(){
    return static_cast<int> (disk_in_peg_.size());
}

/*
 * Returns:
 *  The top disk size (in order to decide if the lifted disk 
 * 	can be put or not.
 *	If there is no disk, return MAX_INT
 */
int peg::getSizeOfTopDisk(){
    if (disk_in_peg_.empty()){
        return INT_MAX;
    }
    return disk_in_peg_.back()->getSize();
}

/* Lift the top disk on peg
 *
 * Returns:
 *  Data of top disk
 * 	Remove the top disk from peg data 
 */
disk* peg::liftTopDisk(){
    disk* lifted_disk = nullptr;
    if (disk_in_peg_.size() != 0 ){
		// get top disk data
        lifted_disk = disk_in_peg_.back();
		// remove top disk from peg
        disk_in_peg_.back()=nullptr ;
        disk_in_peg_.pop_back();
        lifted_disk->liftDisk();
    }
    return lifted_disk;
}

/* Add a new disk as top disk into peg/ lifted disk is put on peg
 *
 * Parameters:
 * new_disk		lifted disk
 *
 * Returns:
 *  Modify the location of disk
 *  Put the lifted on top of the peg
 */
void peg::addNewDisk(disk* new_disk){
    new_disk->putDisk(static_cast<int> (disk_in_peg_.size()),this);
    disk_in_peg_.push_back(new_disk);
}

/* Set up pen and brush to draw the peg
 *
 */

void peg::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)
    QPainter peg_painter(this);
    peg_painter.setRenderHint(QPainter::Antialiasing);

    peg_painter.setPen(Qt::black);
    peg_painter.setBrush(peg_color_);
	// draw peg as rounded rectangle with given size and position
    peg_painter.drawRoundedRect(peg_pos_-PEG_WIDTH_/2,BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH_,PEG_HEIGHT,PEG_WIDTH_/3,PEG_WIDTH_/3);
    //raise();

}
