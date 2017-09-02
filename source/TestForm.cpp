#include "TestForm.hpp"
#include "ui_TestForm.h"

#include "SimpleCommandPaletteEngine.hpp"
#include <QDebug>
#include <QStandardItemModel>

TestForm::TestForm( QWidget* parent ) :
	AbstractCommandPaletteWidget( parent ),
	ui( new Ui::TestForm )
{
	ui->setupUi( this );
	m_engine = new SimpleCommandPaletteEngine();
	connect( m_engine, &AbstractCommandPaletteEngine::actionsFound, this, &TestForm::onSearchResultReady );
}

TestForm::~TestForm()
{
	delete ui;
}

void TestForm::on_lineEdit_textChanged( QString text )
{
	qDebug() << "on_lineEdit_textChanged:" << text;
	if ( text.length() >= 2 ) {
		m_engine->onSearchRequest( text );
	}
	else {
		ui->listView->setModel( nullptr );
	}
}

void TestForm::onSearchResultReady( QList<QAction*> results )
{
	QStandardItemModel* model = new QStandardItemModel();
	ui->listView->setModel( model );
	for ( QAction * a : results ) {
		model->appendRow( new QStandardItem( a->icon(), a->text().replace( "&", "" ) ) );
	}

}
