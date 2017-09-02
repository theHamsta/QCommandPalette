#ifndef TESTFORM_HPP
#define TESTFORM_HPP

#include <QWidget>
#include "AbstractCommandPaletteWidget.hpp"

namespace Ui
{
class TestForm;
}

class QListView;

class TestForm : public AbstractCommandPaletteWidget
{
	Q_OBJECT

public:
	explicit TestForm( QWidget* parent = 0 );
	~TestForm();

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
	
	Ui::TestForm* ui;
	QListView* m_listView = nullptr; ///< Popup-list with suggestions
};

#endif // TESTFORM_HPP
