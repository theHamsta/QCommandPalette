#include "AbstractCommandPaletteEngine.hpp"

#include <QMenuBar>
#include <QDebug>
#include <QAction>

#include "assert.h"



void AbstractCommandPaletteEngine::addAction(QAction* action)
{
	m_actions.append(action);
}

void AbstractCommandPaletteEngine::addActions(QList< QAction* >& actions )
{
	m_actions.append(actions);
}


void AbstractCommandPaletteEngine::addActionsFromMenu(const QMenu* menu)
{
	foreach (QAction *action, menu->actions()) {
		if (action->isSeparator()) {
		} else if (action->menu()) {
			addActionsFromMenu(action->menu());
			m_menus.append(action->menu());
		} else {
			addAction( action );
		}
	}
}

void AbstractCommandPaletteEngine::addActionsFromMenu(const QMenuBar* menubar )
{
	foreach (QAction *action, menubar->actions()) {
		if (action->isSeparator()) {
			// pass
		} else if (action->menu()) {
			addActionsFromMenu(action->menu());
			m_menus.append(action->menu());
		} else {
			addAction( action );
		}
	}
}

void AbstractCommandPaletteEngine::clearActions()
{
	m_actions.clear();
}

void AbstractCommandPaletteEngine::clearDynamicActions()
{
	m_dynamicActions.clear();
}

void AbstractCommandPaletteEngine::addFunctionForDynamicActions(const std::function< QList< QAction* >(QString) > function)
{
	m_dynamicActions.append(function);
}

AbstractCommandPaletteEngine::~AbstractCommandPaletteEngine()
{
	for( QAction* a : m_temporalActions ) {
		delete a;
	}
}






