#include "SimpleCommandPaletteEngine.hpp"
#include <QAction>

SimpleCommandPaletteEngine::SimpleCommandPaletteEngine() : AbstractCommandPaletteEngine()
{

}

SimpleCommandPaletteEngine::~SimpleCommandPaletteEngine()
{

}


void SimpleCommandPaletteEngine::onSearchRequest( const QString& searchQuery )
{
	QList<QAction*> results;
	
	for ( QAction* a : m_actions ){
		if( a->text().contains(searchQuery) ) {
			results.append(a);
		}
	}
	
	emit actionsFound(results);
}
