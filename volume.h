#ifndef VOLUME_H
#define VOLUME_H

#include <QObject>


class Volume : public QObject {
  Q_OBJECT
private:
  explicit Volume(QObject *parent = nullptr);
signals:
  void changed(int volume);
public slots:
  int get() const;
  void set(int volume);
private:
  int m_volume;
};

#define VOLUME Singleton<Volume>::instance()

#endif // VOLUME_H
