#include "volume.h"

Volume::Volume(QObject *parent) :
  QObject(parent), m_volume(0) {
}

void Volume::set(int volume) {
  if (m_volume == volume)
    return;
  m_volume = volume;
  emit changed(m_volume);
}

int Volume::get() const {
  return m_volume;
}
