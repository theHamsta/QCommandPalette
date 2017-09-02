#include "SimpleCommandPaletteEngine.hpp"
#include <QAction>
#include <QDebug>



SimpleCommandPaletteEngine::SimpleCommandPaletteEngine() : AbstractCommandPaletteEngine()
{

}

SimpleCommandPaletteEngine::~SimpleCommandPaletteEngine()
{

}


void SimpleCommandPaletteEngine::onSearchRequest( const QString& searchQuery )
{
	qDebug() << "Recieved search request:" << searchQuery;
	QList<QAction*> results;
	
	for ( QAction* a : m_actions ){
		if( a->text().toLower().contains(searchQuery.toLower()) ) {
			results.append(a);
		}
	}
	
	emit actionsFound(results);
}
