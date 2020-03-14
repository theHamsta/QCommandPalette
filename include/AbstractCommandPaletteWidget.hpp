/**
 * \file   AbstractCommandPaletteWidget.hpp
 * \brief  Defines pure-virtual class AbstractCommandPaletteWidget
 *
 * \author Stephan Seitz (stephan.seitz@fau.de)
 * \date   01.09.2017
 */

#ifndef ABSTRACTCOMMANDPALETTEWIDGET_HPP
#define ABSTRACTCOMMANDPALETTEWIDGET_HPP

#include <QAction>
#include <QShortcut>
#include <QWidget>

#include "AbstractCommandPaletteEngine.hpp"

class AbstractCommandPaletteWidget : public QWidget
{
    Q_OBJECT
  public:
    virtual ~AbstractCommandPaletteWidget();

    void setCommandPaletteEngine(AbstractCommandPaletteEngine* engine);
    inline AbstractCommandPaletteEngine* commandPaletteEngine() const { return m_engine; }
    virtual void setShortcut(QString keySequence);
    const QShortcut* shortcut() const { return m_shortcut; }
    void removeShortcut();

    virtual void addAction(QAction* action) { m_engine->addAction(action); }
    virtual void addActions(QList< QAction* >& actions) { m_engine->addActions(actions); }
    void addActionsFromMenu(const QMenuBar* menubar) { m_engine->addActionsFromMenu(menubar); }
    void addActionsFromMenu(const QMenu* menu) { m_engine->addActionsFromMenu(menu); }

  signals:
    void userInteractionFinished();

  protected slots:
    virtual void onSearchResultsReady(QList< QAction* > results) = 0;
    virtual void onShortcutPressed()                             = 0;
    // 	virtual void onNextSuggestionRequested() = 0;
    // 	virtual void onPreviousSuggestionRequested() = 0;

  protected:
    explicit AbstractCommandPaletteWidget(AbstractCommandPaletteEngine* engine, QWidget* parent = nullptr);
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    AbstractCommandPaletteEngine* m_engine = nullptr; ///< Engine to find suggestions
    QShortcut* m_shortcut                  = nullptr; ///< Shortcut to activate widget
    // 	QShortcut* m_shortcutNextSuggestion = nullptr; ///< Shortcut to select next suggestion
    // 	QShortcut* m_shortcutPreviousSuggestion = nullptr; ///< Shortcut to select previous suggestion
};

#endif // ABSTRACTCOMMANDPALETTEWIDGET_HPP
