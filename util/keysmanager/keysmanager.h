#pragma once

#include <QStringList>
#include <QJsonObject>

namespace util {

class KeysManager {
  QStringList keys_;
  QStringList::const_iterator middle_;

public:
  explicit KeysManager(const QJsonObject& obj);

  QStringList keys_not_array_or_object() const;
  QStringList keys_is_array_or_object() const;
};

} // namespace util
