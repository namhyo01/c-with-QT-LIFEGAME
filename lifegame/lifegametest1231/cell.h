#ifndef CELL_H_
#define CELL_H_

#include <QPalette>
#include <QColor>
#include <QPushButton>
#include <Qt>
#include <QtWidgets>
#include <QFrame>
#include <QHBoxLayout>
using namespace std;
using namespace Qt;
enum cell_type
{
	DEAD,                  
	LIVE                    
};

class Cell : public QFrame
{
	Q_OBJECT                          
private:
	QPushButton* button;      
	cell_type type;                

	public slots:
	void click();         

public:
	Cell(QWidget *parent = NULL, int row = 1, int column = 1);     
	virtual ~Cell();                   
	void set_color();                      
	cell_type gettype() const;              
	void settype(cell_type type);
private:
	GlobalColor get_color();       
};
#endif