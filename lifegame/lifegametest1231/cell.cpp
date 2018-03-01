#include "cell.h"

Cell::Cell(QWidget *parent,int row, int column)
	: QFrame(parent)
{
	this->type = DEAD;          //all is DEAD(initializing) 
	setFrameStyle(QFrame::Box);    

	this->button = new QPushButton(this);  //make button
	this->button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);      
	this->button->setFixedSize(1280/column, 720/row);
	QHBoxLayout *layout = new QHBoxLayout();    //가로로저장하는 레이아웃을 만듬      
	layout->addWidget(this->button); //버튼을 레이아웃에 넣기
	setLayout(layout);//

	layout->setStretchFactor(this->button, 1);   //버튼의 늘림인자를 1로 조정

	layout->setContentsMargins(0, 0, 0, 0);//여백 0
	layout->setSpacing(0);//space = 0

	connect(this->button, SIGNAL(clicked()), this, SLOT(click()));  // 버튼이 눌렸을 때 작업
	set_color();           
}

Cell::~Cell()
{
	delete this->button;
}

void Cell::click() //when button clicked, this event will occur
{                                   
	if (this->type == DEAD)        
		type = LIVE;
	else
		type = DEAD;                 

	settype(type);   
}

cell_type Cell::gettype() const
{
	return(this->type);
}

void Cell::settype(cell_type type)
{
	this->type = type;
	set_color();
}

GlobalColor Cell::get_color()
{
	switch (this->type)
	{
	default:
	case DEAD:
		return white;
	case LIVE:
		return black;
	}
}

void Cell::set_color() //click을 하면  type이 변한다. 그리고 그 타입이 변했으니 색깔도 그에 맞춰서 변해야 한다. 그 작업을 하는 것이다.
{
	GlobalColor color = get_color();        
	this->button->setPalette(QPalette(color, color));        
	this->button->setAutoFillBackground(true);
	this->button->setFlat(true);                        
}
