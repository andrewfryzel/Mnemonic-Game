#ifndef LEVEL1NAV_H
#define LEVEL1NAV_H

#include <QWidget>
#include <level1.h>

namespace Ui
{
	class Level1Nav;
}

class Level1Nav : public QWidget
{
	Q_OBJECT

      public:
	explicit Level1Nav(QWidget *parent = nullptr);
	~Level1Nav();

      private:
	Ui::Level1Nav *ui;

      signals:

      private slots:
};

#endif // LEVEL1NAV_H
