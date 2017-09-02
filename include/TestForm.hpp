#ifndef TESTFORM_HPP
#define TESTFORM_HPP

#include <QWidget>
#include "AbstractCommandPaletteWidget.hpp"

namespace Ui {
class TestForm;
}

class TestForm : public AbstractCommandPaletteWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();
	
private slots:
	void on_lineEdit_textChanged( QString text );
	void onSearchResultReady(QList<QAction*> results);

private:
    Ui::TestForm *ui;
};

#endif // TESTFORM_HPP
