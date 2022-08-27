#ifndef Q_COLOR_BOX_H
#define Q_COLOR_BOX_H

#include <QLabel>
#include <QPainter>


class QColorBox : public QLabel
{
public:
	QColorBox(QPen const & pen = QPen(Qt::black), QBrush const & brush = QBrush(Qt::white), 
		QWidget * parent = nullptr);

	void set(QPen const & pen);
	void set(QBrush const & brush);
	void set(QPen const & pen, QBrush const & brush);
	void paintEvent(QPaintEvent * event) override;

protected:
	QPen mPen;
	QBrush mBrush;
};

#endif // Q_COLOR_BOX_H