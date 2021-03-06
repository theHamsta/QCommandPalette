/**
 * \file   AbstractCommandPaletteEngine.hpp
 * \brief  Defines class AbstractCommandPaletteEngine
 *
 * \author Stephan Seitz (stephan.seitz@fau.de)
 * \date   01.09.2017
 */

#ifndef ABSTRACTCOMMANDPALETTEENGINE_HPP
#define ABSTRACTCOMMANDPALETTEENGINE_HPP

#include <QList>
#include <QWidget>
#include <functional>

class QAction;
class QMenu;
class QMenuBar;

struct SearchResult
{
    QAction* command;
    int score;
};

class AbstractCommandPaletteEngine : public QObject
{
    Q_OBJECT
  public:
    virtual ~AbstractCommandPaletteEngine();

    virtual void addAction(QAction* action);
    virtual void addActions(QList< QAction* >& actions);
    void addActionsFromMenu(const QMenuBar* menubar);
    void addActionsFromMenu(const QMenu* menu);
    void addFunctionForDynamicActions(const std::function< QList< QAction* >(QString searchQuery) > function);
    virtual void clearActions();
    void clearDynamicActions();

  signals:
    void actionsFound(QList< QAction* > actions);

  public slots:
    virtual void onSearchRequest(const QString& searchQuery) = 0;

  protected:
    QList< QAction* > m_actions; ///< List of available commands
    QList< QAction* >
        m_temporalActions;   ///< List of dynamically generated commands (will be deleted after each user interaction)
    QList< QMenu* > m_menus; ///< List of menus (used as categories of commands)
    QList< std::function< QList< QAction* >(QString searchQuery) > >
        m_dynamicActions; ///< Functions to generate dynamic commands

    AbstractCommandPaletteEngine(){};
};

#endif