#include "TestForm.hpp"
#include "ui_TestForm.h"

#include "SimpleCommandPaletteEngine.hpp"
#include <QDebug>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QListView>

TestForm::TestForm( QWidget* parent ) :
	AbstractCommandPaletteWidget( new SimpleCommandPaletteEngine(), parent ),
	ui( new Ui::TestForm )
{
	ui->setupUi( this );

	setPlaceholderText( tr( "Press <Ctrl+P> to search for possible commands" ) );
	m_listView = new QListView( this );

	m_listView->setSelectionBehavior( QAbstractItemView::SelectItems );
	m_listView->setSelectionMode( QAbstractItemView::SingleSelection );
// 	m_listView->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
	m_listView->setWindowFlags( Qt::ToolTip );
// 	m_listView->setAttribute( Qt::WA_ShowWithoutActivating );
	m_listView->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );
	m_listView->hide();
	m_listView->setEditTriggers( QListView::NoEditTriggers );

	connect( m_listView, &QListView::clicked, this, &TestForm::onListViewClicked );

}

TestForm::~TestForm()
{
	delete m_listView;
	delete ui;
}

void TestForm::on_lineEdit_textChanged( QString text )
{
	if ( text.length() >= 2 ) {
		m_engine->onSearchRequest( text );
	}
	else {
		m_listView->setModel( nullptr );
		m_listView->hide();
	}
}

void TestForm::onSearchResultsReady( QList<QAction*> results )
{
	QStandardItemModel* model = new QStandardItemModel();
	m_listView->setModel( model );

	for ( QAction * a : results ) {
		QString commandText = a->text().replace( "&", "" );

		if ( !a->shortcut().isEmpty() ) {
			commandText +=  "\t(" + a->shortcut().toString() + ")";
		}

		auto item = new QStandardItem( a->icon(), commandText );
		item->setData( qVariantFromValue( ( void* ) a ) );
		model->appendRow( item );
	}

	if ( !results.empty() ) {
		m_listView->setCurrentIndex( model->index( 0, 0 ) );
		showPopup();
	}
	else {
		m_listView->hide();
	}


}

void TestForm::keyReleaseEvent( QKeyEvent* event )
{
	QStandardItemModel* model = reinterpret_cast<QStandardItemModel*>( m_listView->model() );

	if ( model && m_listView->selectionModel() ) {
		auto selectedIndexes = m_listView->selectionModel()->selectedIndexes();
		QModelIndex* selectedIndex = nullptr;
		QStandardItem* selectedItem = nullptr;
		QAction* selectedCommand = nullptr;


		if ( selectedIndexes.length() == 1 ) {
			selectedIndex = &selectedIndexes[0];
			selectedItem =  model->itemFromIndex( selectedIndexes[0] );
			selectedCommand = ( QAction* ) selectedItem->data().value<void*>();
		}


		if ( ( event->key() ==  Qt::Key_Enter ) || ( event->key() == Qt::Key_Return ) ) {

			if ( selectedCommand ) {
				selectedCommand->trigger();
				ui->lineEdit->clear();
			}

		}
		else if ( event->key() == Qt::Key_Escape ) {
			ui->lineEdit->clear();
		}
		else if ( event->key() == Qt::Key_Down ) {

			if ( selectedIndex ) {
				int numRows = model->rowCount();
				int curRow = selectedIndex->row();

				if ( curRow + 1 < numRows ) {
					m_listView->setCurrentIndex( model->index( curRow + 1, 0 ) );
				}
			}
		}
		else if ( event->key() == Qt::Key_Up ) {

			if ( selectedIndex ) {
				int curRow = selectedIndex->row();

				if ( curRow - 1 >= 0 ) {
					m_listView->setCurrentIndex( model->index( curRow - 1, 0 ) );
				}
			}
		}
	}
}


void TestForm::onShortcutPressed()
{
	qDebug() << "Shortcut pressed";
	ui->lineEdit->setFocus();
}


void TestForm::showPopup()
{
	m_listView->show();
	QPoint localPos( ui->lineEdit->pos().x(),
					 ui->lineEdit->pos().y() + ui->lineEdit->height() );
	QPoint globalPos = this->mapToGlobal( localPos );
	m_listView->setGeometry( QRect( globalPos.x(),
									globalPos.y(),
									ui->lineEdit->width(),
									100 ) );
}

void TestForm::onNextSuggestionRequested()
{
	qDebug() << "next";
	auto event = new QKeyEvent( QEvent::KeyRelease, Qt::Key_Down, Qt::NoModifier );
	keyPressEvent( event );
	delete event;
}

void TestForm::onPreviousSuggestionRequested()
{
	qDebug() << "prev";
	auto event = new QKeyEvent( QEvent::KeyRelease, Qt::Key_Up, Qt::NoModifier );
	keyPressEvent( event );
	delete event;

}


void TestForm::onListViewClicked( const QModelIndex& index )
{
	QStandardItemModel* model = reinterpret_cast<QStandardItemModel*>( m_listView->model() );

	if ( model ) {
		QStandardItem* item = model->itemFromIndex( index );
		QAction* action = reinterpret_cast<QAction*>( item->data().value<void*>() );

		if ( action ) {
			action->trigger();
			m_listView->hide();
			ui->lineEdit->blockSignals( true );
			ui->lineEdit->clear();
			ui->lineEdit->blockSignals( false );
		}
	}

}

void TestForm::setPlaceholderText( QString text )
{
	ui->lineEdit->setPlaceholderText( text );
}

