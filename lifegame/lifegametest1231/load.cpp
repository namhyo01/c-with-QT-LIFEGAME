#include "load.h"

Load::Load()//initiate
{
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *buttonRow = setupButtonRow();

	layout->addLayout(buttonRow);
	setLayout(layout);
	loadflag = false;
	copy_cells = NULL;
	row = 50, column = 40;
}

Load::~Load()
{

}

void Load::defaultRun()
{
	initiate();
	return;
}

bool Load::importFile()
{
	row = -1, column = -1;
	int temprow = 0;
	int i;
	bool datainput_flag = false;
	QString filename = QFileDialog::getOpenFileName(
		0,
		tr("Open File"),
		"C://",
		"Text Files (*.txt)"
	);
	//call dialog that can find file, to set file
	if (filename == NULL)
	{
		row = 50, column = 40;
		return loadflag = false;
	}
	//Exception handling, if not set any file, return this function and go to first statement


	//reading input data and doing Exception handling, when exception occured, show error message, return this function and go to first statement
	QFile *fin = new QFile(filename);
	fin->open(QIODevice::ReadOnly);

	QTextStream read(fin);
	do
	{
		QString tmp = read.readLine();
		int tmpSize = tmp.length();
		for (i = 0; i < tmpSize; i++)
		{
			if (tmp[i] == '#' || tmp[i] == '\n')
			{
				break;
			}
			else if (row == -1)
			{
				row = (int)tmp.toDouble();
				datainput_flag = false;
				break;
			}
			else if (column == -1)
			{
				column = (int)tmp.toDouble();
				copy_cells = new std::vector<vector<bool> >(row);
				for (int k = 0; k < row; k++)
				{
					copy_cells->at(k).resize(column);
				}
				datainput_flag = false;
				break;
			}
			else if (tmp[i] == 'X')
			{
				copy_cells->at(temprow)[i] = true;
				datainput_flag = true;
			}
			else if (tmp[i] == '-')
			{
				copy_cells->at(temprow)[i] = false;
				datainput_flag = true;
			}
			else//exception handling: other char input
			{
				QMessageBox::warning(0, tr("ERROR"), "FILE HAS CRIT ERROR!");
				row = 50, column = 40;
				return loadflag = false;
			}
		}
		if (datainput_flag)
		{
			if (copy_cells->at(temprow).size() != column)//exception handling: column error
			{
				QMessageBox::warning(0, tr("ERROR"), "FILE HAS CRIT ERROR!");
				row = 50, column = 40;
				return loadflag = false;
			}
			temprow++;
		}
	} while (!read.atEnd());
	if (copy_cells->size() != row)//exception handling: row error
	{
		QMessageBox::warning(0, tr("ERROR"), "FILE HAS CRIT ERROR!");
		row = 50, column = 40;
		return loadflag = false;
	}

	loadflag = true;

	initiate();
	return true;
}



QHBoxLayout* Load::setupButtonRow()
{
	QHBoxLayout *buttonRow = new QHBoxLayout();     // Creates horizontal box for buttons.
	buttonRow->setAlignment(Qt::AlignHCenter);
	QPushButton *Import = new QPushButton("Import");
	Import->setFixedSize(100, 25);
	connect(Import, SIGNAL(clicked()), this, SLOT(importFile()));
	buttonRow->addWidget(Import);
	// Import button: get importdata
	QPushButton *New = new QPushButton("NEW");
	New->setFixedSize(100, 25);
	connect(New, SIGNAL(clicked()), this, SLOT(defaultRun()));
	buttonRow->addWidget(New);
	// NEW button: run default data

	return buttonRow;               // Returns bottom of layout.
}

void Load::initiate()
{

	if (loadflag)//run import mode
	{
		program = new LifeGame(NULL, row, column);
		program->get_cells_copy(copy_cells);
		program->setFixedSize(1280, 760);
		program->show();
		//         program->setFixedSize(1080, 900);
		this->close();
	}
	else//run new mode
	{
		program = new LifeGame(NULL, row, column);
		program->setFixedSize(1280, 760);
		program->show();
		//program->setFixedSize(1080, 900);
		this->close();
	}
}
