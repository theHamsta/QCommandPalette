#ifndef TESTFORM_HPP
#define TESTFORM_HPP

#include <QWidget>

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();

private:
    Ui::TestForm *ui;
};

#endif // TESTFORM_HPP
