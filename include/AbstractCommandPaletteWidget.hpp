/**
 * \file   AbstractCommandPaletteWidget.hpp
 * \brief  Defines pure-virtual class AbstractCommandPaletteWidget
 *
 * \author Stephan Seitz (stephan.seitz@fau.de)
 * \date   01.09.2017
 */

#ifndef ABSTRACTCOMMANDPALETTEWIDGET_HPP
#define ABSTRACTCOMMANDPALETTEWIDGET_HPP

#include <QWidget>
#include "AbstractCommandPaletteEngine.hpp"


class QAction;

class AbstractCommandPaletteWidget: public QWidget
{
	Q_OBJECT
public:
	virtual ~AbstractCommandPaletteWidget() { if(m_engine) delete m_engine; }

	inline void setCommandPaletteEngine( AbstractCommandPaletteEngine* engine ) { m_engine = engine; }
	inline AbstractCommandPaletteEngine* commandPaletteEngine() const { return m_engine; }
	
// 	virtual QWidget* textWidget() = 0;

	
protected:
	explicit AbstractCommandPaletteWidget(QWidget* parent = nullptr ) : QWidget(parent) { }
	virtual void keyReleaseEvent( QKeyEvent* event) override;
	
	AbstractCommandPaletteEngine* m_engine = nullptr; ///< Engine to find suggestions

};

#endif // ABSTRACTCOMMANDPALETTEWIDGET_HPP
