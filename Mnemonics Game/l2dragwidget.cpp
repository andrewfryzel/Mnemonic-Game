#include <QtWidgets>

#include "l2dragwidget.h"
#include "level2.h"
#include <iostream>

L2DragWidget::L2DragWidget(QWidget *parent) : QFrame(parent)
{
	this->parent = parent;

	// setMinimumSize(200, 200);
	setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
	setAcceptDrops(true);

	p = new QLabel(this);
	QPixmap mapP(":/alden/images/P.png");
	p->setPixmap(mapP.scaled(100, 100, Qt::KeepAspectRatio));
	p->move(10, 250);
	p->show();
	p->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	e = new QLabel(this);
	QPixmap mapE(":/alden/images/E.png");
	e->setPixmap(mapE.scaled(100, 100, Qt::KeepAspectRatio));
	e->move(160, 250);
	e->show();
	e->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	m = new QLabel(this);
	QPixmap mapM(":/alden/images/M.png");
	m->setPixmap(mapM.scaled(100, 100, Qt::KeepAspectRatio));
	m->move(325, 250);
	m->show();
	m->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	d = new QLabel(this);
	QPixmap mapD(":/alden/images/D.png");
	d->setPixmap(mapD.scaled(100, 100, Qt::KeepAspectRatio));
	d->move(550, 250);
	d->show();
	d->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	a = new QLabel(this);
	QPixmap mapA(":/alden/images/A.png");
	a->setPixmap(mapA.scaled(100, 100, Qt::KeepAspectRatio));
	a->move(750, 250);
	a->show();
	a->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	s = new QLabel(this);
	QPixmap mapS(":/alden/images/S.png");
	s->setPixmap(mapS.scaled(100, 100, Qt::KeepAspectRatio));
	s->move(900, 250);
	s->show();
	s->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	border = new QLabel(this);
	QPixmap mapBox(":/alden/images/Border.png");
	border->setPixmap(mapBox.scaled(200, 200, Qt::KeepAspectRatio));
	border->move(400, 0);
	border->show();
	border->setAttribute(
	    Qt::WA_DeleteOnClose); // Auto delete so I don't have to
}

void L2DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata"))
	{
		if (event->source() == this)
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void L2DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata"))
	{
		if (event->source() == this)
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void L2DragWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata"))
	{
		QByteArray itemData =
		    event->mimeData()->data("application/x-dnditemdata");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPixmap pixmap;
		QPoint offset;
		QString pl;
		dataStream >> pixmap >> offset >> pl;

		QLabel *newIcon = new QLabel(this);
		newIcon->setPixmap(pixmap);
		newIcon->move(event->pos() - offset);
		newIcon->show();
		newIcon->setAttribute(Qt::WA_DeleteOnClose);

		if (event->source() == this)
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else
		{
			event->acceptProposedAction();
		}

		// std::cout << newIcon->pos().x() << " " << newIcon->pos().y()
		// << std::endl;
		bool inRange =
		    390 <= newIcon->pos().x() && newIcon->pos().x() <= 550 &&
		    15 <= newIcon->pos().y() && newIcon->pos().y() <= 110;
		if (!QString::compare(QString("P"), pl))
		{
			p = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    0);
			}
		}
		else if (!QString::compare(QString("E"), pl))
		{
			e = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    1);
			}
		}
		else if (!QString::compare(QString("M"), pl))
		{
			m = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    2);
			}
		}
		else if (!QString::compare(QString("D"), pl))
		{
			d = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    3);
			}
		}
		else if (!QString::compare(QString("A"), pl))
		{
			a = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    4);
			}
		}
		else if (!QString::compare(QString("S"), pl))
		{
			s = newIcon;
			if (inRange)
			{
				reset();
				static_cast<Level2 *>(parent)->load_letterMenu(
				    5);
			}
		}
	}
	else
	{
		event->ignore();
	}
}

void L2DragWidget::mousePressEvent(QMouseEvent *event)
{
	QLabel *child = static_cast<QLabel *>(childAt(event->pos()));
	if (!child || child == border)
		return;

	QPixmap pixmap = *child->pixmap();

	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << pixmap << QPoint(event->pos() - child->pos());

	if (child == p)
	{
		dataStream << QString("P");
	}
	else if (child == e)
	{
		dataStream << QString("E");
	}
	else if (child == m)
	{
		dataStream << QString("M");
	}
	else if (child == d)
	{
		dataStream << QString("D");
	}
	else if (child == a)
	{
		dataStream << QString("A");
	}
	else if (child == s)
	{
		dataStream << QString("S");
	}

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("application/x-dnditemdata", itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(pixmap);
	drag->setHotSpot(event->pos() - child->pos());

	QPixmap tempPixmap = pixmap;
	QPainter painter;
	painter.begin(&tempPixmap);
	painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
	painter.end();

	child->setPixmap(tempPixmap);

	if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) ==
	    Qt::MoveAction)
	{
		child->close();
	}
	else
	{
		child->show();
		child->setPixmap(pixmap);
	}
}

void L2DragWidget::reset()
{
	p->move(10, 250);
	e->move(160, 250);
	m->move(325, 250);
	d->move(550, 250);
	a->move(750, 250);
	s->move(900, 250);
	border->move(400, 0);
}
