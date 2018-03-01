#include "lifegame.h"

LifeGame::LifeGame(QWidget *parent, int row, int column)
	: QWidget(parent)
{
	QGridLayout *set = setup(row, column);    
	QHBoxLayout *button = setbutton();     
	QVBoxLayout *layout = new QVBoxLayout();//이 레이아웃에 다 저장
	layout->addLayout(set);
	layout->addLayout(button);
	setLayout(layout);
}

LifeGame::~LifeGame()
{
}

QGridLayout* LifeGame::setup(int rows, int column)
{
	QGridLayout *set = new QGridLayout();   

	set->setHorizontalSpacing(0); 
	set->setVerticalSpacing(0);//셀은 수직으로던 수평으로던 연속적으로 이어져야해서 이 작업을 하였다.
	set->setSpacing(0);
	set->setAlignment(Qt::AlignHCenter);
	
	for (int i = 0; i < rows; i++)
	{
		vector<Cell*> row;
		this->cells.push_back(row);
		for (int j = 0; j < column; j++) //입력된 row만큼 col만큼 버튼을 넣는 작업을 할것이다.
		{
			Cell *cell = new Cell(NULL, rows, column);        // create new cell.
			this->cells.at(i).push_back(cell);
			set->addWidget(cell, i, j);  //add cell in (i,j)
			set->setColumnStretch(j, 1);
		}
		set->setRowStretch(i, 1);
	}
	return set;                                
}

QHBoxLayout* LifeGame::setbutton()
{
	QHBoxLayout *button = new QHBoxLayout();     //create 수평적인 layout named button.
	button->setAlignment(Qt::AlignHCenter);
		QPushButton *Run = new QPushButton("RUN"); //make pushbutton named "Run"
		Run->setFixedSize(100, 25);
		connect(Run, SIGNAL(clicked()), this, SLOT(run()));//if this button clicked run run function.
		button->addWidget(Run);

	QPushButton *Next = new QPushButton("NEXT");
	Next->setFixedSize(100, 25);
	connect(Next, SIGNAL(clicked()), this, SLOT(next()));//if this clicked run next function.
	button->addWidget(Next);

	QPushButton *Stop = new QPushButton("STOP");
	Stop->setFixedSize(100, 25);
	connect(Stop, SIGNAL(clicked()), this, SLOT(stop()));// if this clicked run stop function
	button->addWidget(Stop);

	QPushButton *Save = new QPushButton("SAVE");
	Save->setFixedSize(100, 25);
	connect(Save, SIGNAL(clicked()), this, SLOT(save()));//if this clicked run save function
	button->addWidget(Save);

	return button;
}

void LifeGame::run()
{
	this->timer = new QTimer(this);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(lifegame()));
	this->timer->start(100);//run after 100ms.
}

void LifeGame::next()
{
	lifegame();
}

void LifeGame::stop()
{
	this->timer->stop(); //stop this timer. so don't run anymore
}

void LifeGame::get_cells_copy(vector<vector<bool> > *copy_cells)//use in load.cpp for check only live cell in file.
{
	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells.at(i).size(); j++) //if this part is live cell.
		{
			if (copy_cells->at(i)[j])
				this->cells[i][j]->settype(LIVE); //settype LIVE
		}
	}
}


void LifeGame::save() //function for saving this information to file
{
	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("save File"),
		"C://",
		"Text Files (*.txt)"
		);
	if (filename == NULL)
	{
		return;
	}
	QFile *fout = new QFile(filename);

	char *temp;
	char line[] = { '\r','\n' };
	fout->open(QIODevice::WriteOnly);
	temp = (char*)malloc(sizeof(char) * 5);

	ltoa(this->cells.size(), temp, 10);
	fout->write(temp);
	fout->write(line);

	ltoa(this->cells[0].size(), temp, 10);
	fout->write(temp);
	fout->write(line);

	free(temp);

	temp = (char*)malloc(sizeof(char) * this->cells[0].size());

	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int k = 0; k < this->cells[i].size(); k++)
		{
			if (this->cells[i][k]->gettype() == LIVE)
			{
				fout->write("X");
			}
			else
			{
				fout->write("-");
			}
		}
		fout->write(line);
	}
	fout->close();
	QMessageBox::information(0, tr("SAVE"), "SAVE COMPLETE!");
	return;
}

void LifeGame::check_live() //this function is check which cell is live.
{
	while (!this->is_live.empty()) {
		this->is_live.clear();
	}
	this->is_live_count = 0;
	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			if (this->cells[i][j]->gettype() == LIVE) {
				this->is_live.push_back(xy(i, j)); // if cell is livem then push its (x,y) to is_live vector.
				this->is_live_count++;
			}
		}
	}
}

void LifeGame::lifegame()//this function run with lifegame's condition.
{
	check_live(); //check only live cell
	//int data_count = is_live.size();
	int i = 0, j = 0, k = 0;
	for (int l = 0; l<this->is_live_count; l++) { //check live cell's next is Live Or Dead
		int neighbor = 0;
		int a = this->is_live[l].first; // a is x
		int b = this->is_live[l].second;// b is y
		if (a >= 1 && b >= 1) {
			if (this->cells[a - 1][b - 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a - 1, b - 1)); //near of this cell is DEAD cell then push it in new_live vector.
				i++;
			}
		}
		if (a >= 1) {
			if (this->cells[a - 1][b]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a - 1, b));
				i++;
			}
		}
		if (a >= 1 && b < this->cells.at(a).size() - 1) {
			if (this->cells[a - 1][b + 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a - 1, b + 1));
				i++;
			}
		}
		if (b< this->cells.at(a).size() - 1) {
			if (this->cells[a][b + 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a, b + 1));
				i++;
			}
		}
		if (b >= 1) {
			if (this->cells[a][b - 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a, b - 1));
				i++;
			}
		}
		if (a < this->cells.size() - 1 && b >= 1) {
			if (this->cells[a + 1][b - 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a + 1, b - 1));
				i++;
			}
		}
		if (a < this->cells.size() - 1) {
			if (this->cells[a + 1][b]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a + 1, b));
				i++;
			}
		}
		if (a < this->cells.size() - 1 && b < this->cells.at(a).size() - 1) {
			if (this->cells[a + 1][b + 1]->gettype() == LIVE)
				neighbor += 1;
			else {
				this->new_live.push_back(xy(a + 1, b + 1));
				i++;
			}
		}
		if (neighbor < 2) { //if neighbor's count is less than 2 or more than 3 then this cell will be Dead.
			this->copy_cells.push_back(_copy(a, b, 0));// So I will push that its type will be change.
			j++;
		}
		else if (neighbor > 3) {
			this->copy_cells.push_back(_copy(a, b, 0));
			j++;
		}
	}
	this->is_live_count = 0;//초기화
	vector<xy>().swap(this->is_live);

	for (int m = 0; m<i; m++) {
		int c = this->new_live[m].first;
		int d = this->new_live[m].second;

		int _neighbor = 0;
		if (c >= 1 && d >= 1)
			if (this->cells[c - 1][d - 1]->gettype() == LIVE)
				_neighbor += 1;
		if (c >= 1)
			if (this->cells[c - 1][d]->gettype() == LIVE)
				_neighbor += 1;
		if (c >= 1 && d < this->cells.at(c).size() - 1)
			if (this->cells[c - 1][d + 1]->gettype() == LIVE)
				_neighbor += 1;
		if (d < this->cells.at(c).size() - 1)
			if (this->cells[c][d + 1]->gettype() == LIVE)
				_neighbor += 1;
		if (d >= 1)
			if (this->cells[c][d - 1]->gettype() == LIVE)
				_neighbor += 1;
		if (c < this->cells.size() - 1 && d >= 1)
			if (this->cells[c + 1][d - 1]->gettype() == LIVE)
				_neighbor += 1;
		if (c < this->cells.size() - 1)
			if (this->cells[c + 1][d]->gettype() == LIVE)
				_neighbor += 1;
		if (c < this->cells.size() - 1 && d < this->cells.at(c).size() - 1)
			if (this->cells[c + 1][d + 1]->gettype() == LIVE)
				_neighbor += 1;

		if (_neighbor == 3) { //if neighbor is 3 then its mean it can born. SO its type will be change so i push it in copy_cells
			this->copy_cells.push_back(_copy(c, d, 1));
			j++;
			//this->is_live.push_back(xy(c, d));
			//this->is_live_count++;
		}
	}
	vector<xy>().swap(this->new_live);
	for (int o = 0; o < j; o++)
	{
		if (get<2>(this->copy_cells[o]) == 0) // if last element is 0 then DEAD 1 is LIVE
			this->cells[get<0>(this->copy_cells[o])][get<1>(this->copy_cells[o])]->settype(DEAD); //get x and y and set this type
		else
			this->cells[get<0>(this->copy_cells[o])][get<1>(this->copy_cells[o])]->settype(LIVE);
	}
	vector<_copy>().swap(this->copy_cells);
}