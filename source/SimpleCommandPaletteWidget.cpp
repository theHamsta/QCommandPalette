#include "SimpleCommandPaletteWidget.hpp"
#include "ui_SimpleCommandPaletteWidget.h"

#include "SimpleCommandPaletteEngine.hpp"
#include <QDebug>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QTreeView>

SimpleCommandPaletteWidget::SimpleCommandPaletteWidget( QWidget* parent ) :
	AbstractCommandPaletteWidget( new SimpleCommandPaletteEngine(), parent ),
	ui( new Ui::SimpleCommandPaletteWidget )
{
	ui->setupUi( this );

	setPlaceholderText( tr( "Press <Ctrl+P> to search for possible commands" ) );
	m_listView = new QTreeView( this );

	m_listView->setSelectionBehavior( QAbstractItemView::SelectItems );
// 	m_listView->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
	m_listView->setWindowFlags( Qt::ToolTip );
	m_listView->setSelectionBehavior( QAbstractItemView::SelectRows);
// 	m_listView->verticalHeader()->setVisible(false);
// 	m_listView->horizontalHeader()->setVisible(false);
// 	m_listView->setShowGrid(false);
	m_listView->header()->close();
	m_listView->setRootIsDecorated(false);
	m_listView->hide();
	m_listView->setEditTriggers( QTreeView::NoEditTriggers );

	connect( m_listView, &QTreeView::clicked, this, &SimpleCommandPaletteWidget::onListViewClicked );

}

SimpleCommandPaletteWidget::~SimpleCommandPaletteWidget()
{
	delete m_listView;
	delete ui;
}

void SimpleCommandPaletteWidget::on_lineEdit_textChanged( QString text )
{
	if ( text.length() >= 2 ) {
		m_engine->onSearchRequest( text );
	}
	else {
		m_listView->setModel( nullptr );
		m_listView->hide();
	}
}

void SimpleCommandPaletteWidget::onSearchResultsReady( QList<QAction*> results )
{
	QStandardItemModel* model = new QStandardItemModel();
	m_listView->setModel( model );

	for ( QAction * a : results ) {
		QString commandText;

		if( a->isCheckable() && !a->actionGroup() ) {
			commandText = (a->isChecked() ? tr("Deactivate \"") : tr("Activate \"")) +  a->text().replace( "&", "" ) + "\"";
		}
		else {
			commandText = a->text().replace( "&", "" );
		}
		
		if ( !a->shortcut().isEmpty() ) {
			commandText +=  "      (" + a->shortcut().toString() + ")";
		}

		QList<QStandardItem*> itemRow;
		auto item = new QStandardItem( a->icon(), commandText );
		item->setData( qVariantFromValue( ( void* ) a ) );
		itemRow.append(item);
		
		if ( !a->shortcut().isEmpty() ) {
			 QStandardItem* shortcutItem = new QStandardItem( "(" + a->shortcut().toString() + ")");
			 shortcutItem->setForeground(Qt::gray);
			 shortcutItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter );
			 itemRow.append(shortcutItem);
		}
		model->appendRow( itemRow );
	}

	if ( !results.empty() ) {
		m_listView->setCurrentIndex( model->index( 0, 0 ) );
		showPopup();
	}
	else {
		m_listView->hide();
	}


}

void SimpleCommandPaletteWidget::keyReleaseEvent( QKeyEvent* event )
{
	QStandardItemModel* model = reinterpret_cast<QStandardItemModel*>( m_listView->model() );

	if ( model && m_listView->selectionModel() ) {
		auto selectedIndexes = m_listView->selectionModel()->selectedIndexes();
		QModelIndex* selectedIndex = nullptr;
		QStandardItem* selectedItem = nullptr;
		QAction* selectedCommand = nullptr;


		if ( selectedIndexes.length() > 0 ) {
			selectedIndex = &selectedIndexes[0];
			selectedItem =  model->itemFromIndex( selectedIndexes[0] );
			selectedCommand = ( QAction* ) selectedItem->data().value<void*>();
		}


		if ( ( event->key() ==  Qt::Key_Enter ) || ( event->key() == Qt::Key_Return ) ) {

			if ( selectedCommand ) {
				ui->lineEdit->clear();
				selectedCommand->trigger();
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


void SimpleCommandPaletteWidget::onShortcutPressed()
{
	ui->lineEdit->setFocus();
}


void SimpleCommandPaletteWidget::showPopup()
{
	m_listView->show();
	QPoint localPos( ui->lineEdit->pos().x(),
					 ui->lineEdit->pos().y() + ui->lineEdit->height() );
	QPoint globalPos = this->mapToGlobal( localPos );
	m_listView->setGeometry( QRect( globalPos.x(),
									globalPos.y(),
									ui->lineEdit->width(),
									200 ) );
	m_listView->setColumnWidth( 0, ui->lineEdit->width() * 0.7 );
	m_listView->setColumnWidth( 1, ui->lineEdit->width() * 0.2 );
}

void SimpleCommandPaletteWidget::onNextSuggestionRequested()
{
	qDebug() << "next";
	auto event = new QKeyEvent( QEvent::KeyRelease, Qt::Key_Down, Qt::NoModifier );
	keyPressEvent( event );
	delete event;
}

void SimpleCommandPaletteWidget::onPreviousSuggestionRequested()
{
	qDebug() << "prev";
	auto event = new QKeyEvent( QEvent::KeyRelease, Qt::Key_Up, Qt::NoModifier );
	keyPressEvent( event );
	delete event;
}


void SimpleCommandPaletteWidget::onListViewClicked( const QModelIndex& index )
{
	QStandardItemModel* model = reinterpret_cast<QStandardItemModel*>( m_listView->model() );

	if ( model ) {
		QStandardItem* item = model->itemFromIndex( index );
		QAction* action = reinterpret_cast<QAction*>( item->data().value<void*>() );

		if ( action ) {
			m_listView->hide();
			ui->lineEdit->blockSignals( true );
			ui->lineEdit->clear();
			ui->lineEdit->blockSignals( false );
			action->trigger();
		}
	}

}

void SimpleCommandPaletteWidget::setPlaceholderText( QString text )
{
	ui->lineEdit->setPlaceholderText( text );
}

