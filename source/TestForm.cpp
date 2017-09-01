#include "TestForm.hpp"
#include "ui_TestForm.h"

TestForm::TestForm(QWidget *parent) :
    AbstractCommandPaletteWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
}

TestForm::~TestForm()
{
    delete ui;
}

