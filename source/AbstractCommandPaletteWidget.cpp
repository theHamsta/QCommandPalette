#include "AbstractCommandPaletteWidget.hpp"

#include <QKeyEvent>

AbstractCommandPaletteWidget::AbstractCommandPaletteWidget( AbstractCommandPaletteEngine* engine, QWidget* parent ) : QWidget( parent )
{
	setCommandPaletteEngine( engine );
	m_shortcut = new QShortcut( QKeySequence( "Ctrl+P" ), this );
	// 	m_shortcutNextSuggestion = new QShortcut( QKeySequence( "Ctrl+N" ), this );
	// 	m_shortcutPreviousSuggestion = new QShortcut( QKeySequence( "Ctrl+X" ), this );

	connect( m_shortcut, &QShortcut::activated, this, &AbstractCommandPaletteWidget::onShortcutPressed );
	connect( m_engine, &AbstractCommandPaletteEngine::actionsFound, this, &AbstractCommandPaletteWidget::onSearchResultsReady );
	// 	connect( m_shortcutNextSuggestion, &QShortcut::activated, this, &AbstractCommandPaletteWidget::onNextSuggestionRequested );
	// 	connect( m_shortcutPreviousSuggestion, &QShortcut::activated, this, &AbstractCommandPaletteWidget::onPreviousSuggestionRequested );
}

AbstractCommandPaletteWidget::~AbstractCommandPaletteWidget()
{
	if ( m_engine ) delete m_engine;

	if ( m_shortcut ) delete m_shortcut;

	// 	if ( m_shortcutNextSuggestion ) delete m_shortcutNextSuggestion;
	//
	// 	if ( m_shortcutPreviousSuggestion ) delete m_shortcutPreviousSuggestion;


}

void AbstractCommandPaletteWidget::keyReleaseEvent( QKeyEvent* event )
{
	event->accept();
}


void AbstractCommandPaletteWidget::setShortcut( QString keySequence )
{
	if ( m_shortcut ) {
		delete m_shortcut;
		m_shortcut = nullptr;
	}

	if ( !keySequence.isEmpty() ) {
		m_shortcut = new QShortcut( QKeySequence( keySequence ), this );
		connect( m_shortcut, &QShortcut::activated, this, &AbstractCommandPaletteWidget::onShortcutPressed );
	}
}

void AbstractCommandPaletteWidget::removeShortcut()
{
	if ( m_shortcut ) {
		delete m_shortcut;
		m_shortcut = nullptr;
	}
}

void AbstractCommandPaletteWidget::setCommandPaletteEngine( AbstractCommandPaletteEngine* engine )
{
	if ( m_engine ) {
		delete m_engine;
	}

	m_engine = engine;
	connect( m_engine, &AbstractCommandPaletteEngine::actionsFound, this, &AbstractCommandPaletteWidget::onSearchResultsReady );
}
