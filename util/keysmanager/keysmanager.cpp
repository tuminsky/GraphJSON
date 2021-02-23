#include "keysmanager.h"

#include <QJsonValue>

namespace util {

KeysManager::KeysManager(const QJsonObject& obj)
  : keys_(obj.keys())
{
  middle_ = std::partition(keys_.begin(), keys_.end(),
    [&obj](const auto& key) {
      return !(obj[key].isArray() || obj[key].isObject());
    }
  );
}

QStringList KeysManager::keys_not_array_or_object() const
{
  return {keys_.begin(), middle_};
}

QStringList KeysManager::keys_is_array_or_object() const
{
  return {middle_, keys_.end()};
}

} // namespace util
