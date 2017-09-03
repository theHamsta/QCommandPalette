#include "SimpleCommandPaletteEngine.hpp"
#include <QAction>
#include <QDebug>
#include <QMenu>



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
		QMenu* parentMenu = dynamic_cast<QMenu*>(a->parent());
		QString parentMenuTitle;
		if (parentMenu) {
			parentMenuTitle = parentMenu->title().toLower().replace( "&", "" );
		}
		

		if ( a->isEnabled() ) {
			bool matches = true;

			for ( auto & word : words ) {
				matches &= actionToLower.contains( word ) || parentMenuTitle.contains(word);
			}

			if ( matches ) {
				results.append( a );
				a->setData( true );
			}
		}
	}

	for ( QMenu * m : m_menus ) {
		QString menu = m->title().toLower().replace( "&", "" );

		if ( m->isEnabled() ) {
			bool matches = true;

			for ( auto & word : words ) {
				matches &= menu.contains( word );
			}

			if ( matches ) {
				for ( QAction * a : m->actions() ) {
					if ( !a->menu() && !a->isSeparator()  && !a->data().toBool() ) {
						results.append( a );
					}
				}
			}
		}
	}
	
	for ( QAction* a : m_actions ) {
		a->setData(false);
	}

	emit actionsFound( results );
}
