#pragma once

#include <QList>

#include "AbstractCommandPaletteEngine.hpp"
#include "MatcherBase.h"

class FuzzyCommandPaletteEngine : public AbstractCommandPaletteEngine
{
    Q_OBJECT
  public:
    FuzzyCommandPaletteEngine() : AbstractCommandPaletteEngine() {}
    FuzzyCommandPaletteEngine(FuzzyCommandPaletteEngine&&)      = delete;
    FuzzyCommandPaletteEngine(const FuzzyCommandPaletteEngine&) = delete;
    FuzzyCommandPaletteEngine& operator=(FuzzyCommandPaletteEngine&&) = delete;
    FuzzyCommandPaletteEngine& operator=(const FuzzyCommandPaletteEngine&) = delete;
    virtual ~FuzzyCommandPaletteEngine() {}

    virtual void addAction(QAction* action) override;
    virtual void addActions(QList< QAction* >& actions) override;
    virtual void clearActions() override;
    inline void setMatcherOptions(const MatcherOptions& options) { m_matcherOptions = options; }
    inline MatcherOptions matcherOptions() const { return m_matcherOptions; }

  public slots:
    virtual void onSearchRequest(const QString& searchQuery) override;

  private:
    MatcherBase m_matcherBase;                             ///< String matcher for fuzzy search
    MatcherOptions m_matcherOptions;                       ///< Options for string matcher
    std::map< std::string, QAction* > m_stringToActionMap; ///< Map search results to corresponding QActions
};
