#pragma once
#include <QtWidgets>

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget* parent = 0) :
        QWidget(parent) {}
    const QPixmap* getPixmap() const {
        return &pix;
    }

public slots:
    void setPixmap(const QPixmap& pixmap) {
        pix = pixmap;
        repaint();
    }

protected:
    void paintEvent(QPaintEvent* event) {
        QWidget::paintEvent(event);

        if (pix.isNull())
            return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QSize pixSize = pix.size();
        pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

        QPixmap scaledPix = pix.scaled(pixSize,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        QPoint drawPointStart;
        drawPointStart.setX((event->rect().size().width() - scaledPix.width()) / 2);
        drawPointStart.setY((event->rect().size().height() - scaledPix.height()) / 2);
        painter.drawPixmap(drawPointStart, scaledPix);
    }


private:
    QPixmap pix;
};
