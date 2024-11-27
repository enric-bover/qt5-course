#ifndef PIXMAPMIME_H
#define PIXMAPMIME_H

#include <QMimeData>
#include <QPixmap>

class PixmapMime : public QMimeData
{
    Q_OBJECT
public:
    explicit PixmapMime(QObject *parent = nullptr);

signals:

};

#endif // PIXMAPMIME_H
