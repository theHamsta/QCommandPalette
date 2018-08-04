#ifndef TESTFORM_HPP
#define TESTFORM_HPP

#include <QWidget>
#include "AbstractCommandPaletteWidget.hpp"

namespace Ui
{
	class SimpleCommandPaletteWidget;
}

class QTreeView;

class SimpleCommandPaletteWidget : public AbstractCommandPaletteWidget
{
		Q_OBJECT

	public:
		explicit SimpleCommandPaletteWidget( QWidget* parent = 0 );
		~SimpleCommandPaletteWidget();

		inline qreal minimumPopUpWidth() const { return m_minPopUpWidth; }

		void setPlaceholderText( QString text );
		inline void setMinimumPopUpWidth( int width ) { m_minPopUpWidth = width; }

	private slots:
		void on_lineEdit_textChanged( QString text );
		void onSearchResultsReady( QList<QAction*> results ) override;
		void onShortcutPressed() override;
		void onListViewClicked( const QModelIndex& index );
		// 	void onNextSuggestionRequested() override;
		// 	void onPreviousSuggestionRequested() override;


	protected:
		virtual void keyReleaseEvent( QKeyEvent* event ) override;
		virtual void focusInEvent( QFocusEvent* event ) override;

	private:
		void showPopup();

		Ui::SimpleCommandPaletteWidget* ui;
		QTreeView* m_listView = nullptr; ///< Popup-list with suggestions
		int m_minPopUpWidth =  300; ///< Minimum width up of popup widget
};

#endif // TESTFORM_HPP
