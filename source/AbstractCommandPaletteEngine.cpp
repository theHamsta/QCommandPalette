#include "AbstractCommandPaletteEngine.hpp"

#include <QMenuBar>
#include <QDebug>

#include "assert.h"

void AbstractCommandPaletteEngine::addAction(QAction* action)
{
	qDebug() << "Adding action" << action->text();
	m_actions.append(action);
}

void AbstractCommandPaletteEngine::addActions(QList< QAction* >& actions )
{
	assert( false );
	m_actions.append(actions);
}


void AbstractCommandPaletteEngine::addActionsFromMenu(const QMenu* menu)
{
	qDebug() << "Adding menu" << menu->title();
	foreach (QAction *action, menu->actions()) {
		if (action->isSeparator()) {
		} else if (action->menu()) {
			addActionsFromMenu(action->menu());
		} else {
			addAction( action );
		}
	}
}

void AbstractCommandPaletteEngine::addActionsFromMenu(const QMenuBar* menubar )
{
	qDebug() << "Adding menubar";
	foreach (QAction *action, menubar->actions()) {
		if (action->isSeparator()) {
			// pass
		} else if (action->menu()) {
			addActionsFromMenu(action->menu());
		} else {
			addAction( action );
		}
	}
}





