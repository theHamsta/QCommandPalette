#include "AbstractCommandPaletteWidget.hpp"

#include <QKeyEvent>

void AbstractCommandPaletteWidget::keyReleaseEvent(QKeyEvent* event)
{
	event->accept();
// 	if (event->j( QKeySequence(Qt::CTRL, Qt::Key_P ) )) {
// 		this->textWidget()->focus();
// 	}
}
