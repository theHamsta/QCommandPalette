#ifndef TESTFORM_HPP
#define TESTFORM_HPP

#include <QWidget>
#include "AbstractCommandPaletteWidget.hpp"

namespace Ui
{
class SimpleCommandPaletteWidget;
}

class QListView;

class SimpleCommandPaletteWidget : public AbstractCommandPaletteWidget
{
	Q_OBJECT

public:
	explicit SimpleCommandPaletteWidget( QWidget* parent = 0 );
	~SimpleCommandPaletteWidget();

	void setPlaceholderText( QString text );
	
private slots:
	void on_lineEdit_textChanged( QString text );
	void onSearchResultsReady( QList<QAction*> results ) override;
	void onShortcutPressed() override;
	void onListViewClicked( const QModelIndex& index );
	void onNextSuggestionRequested() override;
	void onPreviousSuggestionRequested() override;


protected:
	virtual void keyReleaseEvent( QKeyEvent* event ) override;

private:
	void showPopup();
	
	Ui::SimpleCommandPaletteWidget* ui;
	QListView* m_listView = nullptr; ///< Popup-list with suggestions
};

#endif // TESTFORM_HPP
