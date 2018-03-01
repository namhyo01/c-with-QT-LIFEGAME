#ifndef LOAD_H
#define LOAD_H_
#include <QtWidgets>
#include <QtGui/QGuiApplication>
#include "lifegame.h"
#include <vector>
#include <QApplication>

using namespace std;
class Load :public QWidget
{
	Q_OBJECT
public:
	Load();
	virtual ~Load();
	public slots:
	bool importFile();//start to import
	void defaultRun();//run default set
private:
	vector<vector<bool> > *copy_cells;//data point which record input file data
	QHBoxLayout* setupButtonRow();//button set up function
	bool loadflag;//flag that load is success of not
	LifeGame* program;//class point that call main game
	void initiate();//show program(main game) to play
	int row, column;//data which decide cell size

};
#endif