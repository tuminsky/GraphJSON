#pragma once

#include <QObject>
#include <QJsonObject>

#include <boost/graph/adjacency_list.hpp>

#include <string>
#include <QTextStream>

namespace util {

using vertex_t = std::string;

using graph_t = boost::adjacency_list<
  boost::vecS,      // OutEdgeList
  boost::vecS,      // VertexList
  boost::directedS, // Directed
  vertex_t          // VertexProperties
>;

using descriptor_t = typename boost::graph_traits<graph_t>::vertex_descriptor;

graph_t json_to_graph(const QJsonObject& root);

std::ostream& operator<< (std::ostream& os, const graph_t& graph);

} // namespace util

namespace util::detail {

QString to_string(const QJsonValue& value);

void json_to_graph_impl(const QJsonValue& value, graph_t& graph, descriptor_t parent_vertex);

void json_to_graph_impl(const QJsonObject& obj, graph_t& graph, descriptor_t parent_vertex);

void json_to_graph_impl(const QJsonArray& array, graph_t& graph, descriptor_t parent_vertex);

} // namespace util::detail
