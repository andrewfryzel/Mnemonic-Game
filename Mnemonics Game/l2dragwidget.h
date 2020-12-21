/* Class taken from
 * https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/draganddrop/draggableicons/dragwidget.h?h=5.13
 */

#ifndef L2DRAGWIDGET_H
#define L2DRAGWIDGET_H

#include <QFrame>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class L2DragWidget : public QFrame
{

      public:
	explicit L2DragWidget(QWidget *parent = nullptr);
	void reset();

      private:
	QWidget *parent;
	QLabel *p, *e, *m, *d, *a, *s, *border;

      protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
};

#endif // L2DRAGWIDGET_H
