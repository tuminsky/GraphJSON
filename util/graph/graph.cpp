#include "graph.h"
#include "util/keysmanager/keysmanager.h"

#include <QJsonArray>

#include <boost/graph/graphviz.hpp>

#include <limits>

namespace util {

std::ostream& operator<< (std::ostream& os, const graph_t& graph) {
  const auto vertex_writer = [&](std::ostream& os, const descriptor_t& vertex) {
    os << " [label=\"" << boost::get(boost::vertex_bundle, graph)[vertex] << "\"]";
  };

  boost::write_graphviz(os, graph, vertex_writer);

  return os;
}

void json_to_graph_impl(const QJsonObject& obj, graph_t& graph, descriptor_t parent_vertex = std::numeric_limits<descriptor_t>::max())
{
  KeysManager km(obj);
  QStringList text;

  for (const auto& key : km.keys_not_array_or_object()) {
    const auto value = obj.value(key);
    auto line = key + ": ";

    if (value.isBool())        line += value.toBool() ? "true" : "false";
    else if (value.isString()) line += value.toString();
    else if (value.isDouble()) line += QString::number(value.toDouble());

    text << line;
  }

  const auto vertex = boost::add_vertex(vertex_t{text.join("\n").toStdString()}, graph);

  if (parent_vertex < boost::num_vertices(graph))
    boost::add_edge(parent_vertex, vertex, graph);

  for (const auto& child_key : km.keys_is_array_or_object()) {
    const auto child = obj.value(child_key);

    if (child.isArray()) {
      for (const auto item : child.toArray())
        json_to_graph_impl(item.toObject(), graph, vertex);
    } else { // isObject
      json_to_graph_impl(child.toObject(), graph, vertex);
    }
  }
}

graph_t json_to_graph(const QJsonObject& root)
{
  graph_t graph;

  json_to_graph_impl(root, graph);

  return graph;
}

} // namespace util
