#ifndef LIFEGAME_H_
#define LIFEGAME_H_

#include <vector>
#include <QtWidgets>
#include <QTimer>
#include <QGridLayout>
#include <QApplication>
#include "cell.h"
#include <utility>
#include <tuple>
using namespace std;
using namespace Qt;
typedef pair<int, int> xy;
typedef tuple<int, int, bool> _copy;

class LifeGame : public QWidget
{
	Q_OBJECT                       

private:
	vector<vector<Cell*> > cells;     
	QTimer *timer;
	unsigned int is_live_count = 0;

	vector<xy> is_live; // 살아있는 셀 저장
	vector<xy> new_live; // 살아있는 셀의 주변의 죽어있는 셀들을 저장
	vector<_copy> copy_cells;//타입이 변할때 저장 3번째 값으로 인해 0이면 DIE 1이면 LIVE로 계산

	public slots:
	void run();         
	void next();              
	void lifegame();
	void stop();
	void save();

public:
	LifeGame(QWidget *parent = NULL, int row = 50, int column = 40);       
	virtual ~LifeGame();                                    
	void get_cells_copy(vector<vector<bool> > *copy_cells);
private:
	QGridLayout* setup(int row, int column);      
	QHBoxLayout* setbutton();  
	void check_live();
};

#endif
