#pragma once
#include <vector>
#include <cassert>
#include <algorithm>

namespace ColoringElements {
  namespace Graph {

  template<typename T>
  class Graph {
    private:
      std::vector<std::vector<T>> _vertices = {};
      T _maxVertexDegree = 0;

    void putVerticesNeighbours(const std::vector<std::vector<T>> & graphNeighbours) {
      auto verticesCount = static_cast<T>(graphNeighbours.size());
      assert(verticesCount >= 1);
      _vertices.reserve(verticesCount);
      for (auto currentVertex = 0; currentVertex < verticesCount; ++currentVertex) {
        _vertices.emplace_back(std::vector<T>());
        auto size = graphNeighbours[currentVertex].size();
        if (size == 0) continue;
        _maxVertexDegree = std::max(_maxVertexDegree, static_cast<T>(size));
        _vertices[currentVertex].resize(size);
        std::copy(graphNeighbours[currentVertex].begin(), graphNeighbours[currentVertex].end(), _vertices[currentVertex].begin());
      }
    }
   public:

    explicit Graph(const std::vector<std::vector<T>> & graphNeighbours) {
      this->putVerticesNeighbours(graphNeighbours);
    }

    ~Graph() {
      auto size = _vertices.size();
      for(auto currentVertex = 0; currentVertex < size; ++currentVertex) {
        _vertices[currentVertex].shrink_to_fit();
      }
      _vertices.shrink_to_fit();
    }

    inline T getVerticesCount() const {
      return static_cast<T>(_vertices.size());
    }

    inline T getMaxVerexDegree() const {
      return _maxVertexDegree;
    }

    std::vector<T> getVertexNeighbours(const T vertex) {
      assert(vertex >= 0 && vertex < _vertices.size());
      std::vector<T> neighbours(_vertices[vertex].size());
      this->getVertexNeighbours(vertex, neighbours);
      return neighbours;
    }

    void getVertexNeighbours(const T vertex, std::vector<T> & neighbours) {
      assert(vertex >= 0 && vertex < _vertices.size());
      if (neighbours.size() != _vertices[vertex].size()) {
        neighbours.resize(_vertices[vertex].size() - neighbours.size());
      }
      std::copy(_vertices[vertex].begin(), _vertices[vertex].end(), neighbours.begin());
    }
    };
  }
}
