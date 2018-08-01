#include "FuzzyCommandPaletteEngine.hpp"

#include <QAction>
#include <QDebug>
#include <QMenu>

#include <iostream>

void FuzzyCommandPaletteEngine::addAction( QAction* action )
{
	AbstractCommandPaletteEngine::addAction( action );
	m_matcherOptions.case_sensitive = false;
	m_matcherOptions.num_threads = 3;
	m_matcherOptions.max_results = 10;
	m_matcherOptions.max_gap = 0;
	QString searchString = action->text().toLower();
	QMenu* parentMenu = dynamic_cast<QMenu*>( action->parent() );

	if ( parentMenu ) {
		searchString = parentMenu->title().toLower().replace( "&", "" ) + " "+ searchString;
	}
	searchString += " " + action->shortcut().toString() + " " + action->toolTip();

	m_matcherBase.addCandidate( searchString.toStdString() );
	m_stringToActionMap[ searchString.toStdString()] = action ;
}
void FuzzyCommandPaletteEngine::addActions( QList<QAction*>& actions )
{
	AbstractCommandPaletteEngine::addActions( actions );


	for ( auto action : actions ) {

		QString searchString = action->text().toLower();
		QMenu* parentMenu = dynamic_cast<QMenu*>( action->parent() );

		if ( parentMenu ) {
			searchString += parentMenu->title().toLower().replace( "&", "" );
		}

		m_matcherBase.addCandidate( searchString.toStdString() );
		m_stringToActionMap[ searchString.toStdString()] = action ;
	}



}
void FuzzyCommandPaletteEngine::clearActions()
{
	m_matcherBase.clear();
	m_stringToActionMap.clear();
}

void FuzzyCommandPaletteEngine::onSearchRequest( const QString& searchQuery )
{

	std::vector<MatchResult> resultsStaticActions =  m_matcherBase.findMatches( searchQuery.toStdString(), m_matcherOptions );

	for ( auto& r : resultsStaticActions ) {
		auto find = m_stringToActionMap.find( *r.value );

		if ( find != m_stringToActionMap.end() ) {
			QAction* candidate = find->second;

			if ( candidate->isEnabled() ) {
				results.append( candidate );
			}
		}
	}

	// Delete dynamically generated from last search
	for ( QAction* a : m_temporalActions ) {
		delete a;
	}

	m_temporalActions.clear();

	QList<QAction*> results;

	for ( auto f : m_dynamicActions ) {
		m_temporalActions.append( f( searchQuery ) );
	}

	results.append( m_temporalActions );



	emit actionsFound( results );
}
