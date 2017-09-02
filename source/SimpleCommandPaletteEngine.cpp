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
	QList<QAction*> results;
	QStringList words = searchQuery.toLower().split( " ", QString::SkipEmptyParts );

	for ( QAction * a : m_actions ) {
		QString actionToLower = a->text().toLower().replace( "&", "" );

		if ( a->isEnabled() ) {
			bool matches = true;

			for ( auto & word : words ) {
				matches &= actionToLower.contains( word );
			}

			if ( matches ) {
				results.append( a );
			}
		}
	}

	emit actionsFound( results );
}
