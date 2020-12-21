#ifndef LAYER_H
#define LAYER_H
#include <QLabel>

class layer : public QLabel
{
	Q_OBJECT
      public:
	layer();

	~layer();
	void mousePressEvent(QMouseEvent *event);

      signals:
	void clicked();
};

#endif // LAYER_H
