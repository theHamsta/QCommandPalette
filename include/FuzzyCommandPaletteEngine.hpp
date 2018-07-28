#pragma once

#include "AbstractCommandPaletteEngine.hpp"
#include "MatcherBase.h"

class FuzzyCommandPaletteEngine : public AbstractCommandPaletteEngine
{
		Q_OBJECT
	public:
		FuzzyCommandPaletteEngine(): AbstractCommandPaletteEngine() {}
		FuzzyCommandPaletteEngine( FuzzyCommandPaletteEngine&& ) = default;
		FuzzyCommandPaletteEngine( const FuzzyCommandPaletteEngine& ) = default;
		FuzzyCommandPaletteEngine& operator=( FuzzyCommandPaletteEngine&& ) = default;
		FuzzyCommandPaletteEngine& operator=( const FuzzyCommandPaletteEngine& ) = default;
		virtual ~FuzzyCommandPaletteEngine() {}

		virtual void addAction( QAction* action ) override;
		virtual void addActions( QList<QAction*>& actions ) override;
		virtual void clearActions() override;
		inline void setMatcherOptions( const MatcherOptions& options ) {m_matcherOptions = options; }
		inline void matcherOptions() const {return m_matcherOptions;}

	public slots:
		virtual void onSearchRequest( const QString& searchQuery ) override;


	private:
		MatcherBase m_matcherBase; ///< String matcher for fuzzy search
		MatcherOptions m_matcherOptions{false, 3, 10, 0, false}; ///< Options for string matcher
		std::map<std::string, QAction*> m_stringToActionMap; ///< Map search results to corresponding QActions

};
