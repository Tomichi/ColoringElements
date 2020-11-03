#pragma once

#include <memory>
#include "Graph.h"
#include "../Utils/BitArray.h"

namespace ColoringElements{
  namespace Graph{
    template<typename T>
    class Coloring{
     private:
      std::shared_ptr<Graph<T>> _graph;
      std::vector<T> _colorVertices;
      std::vector<std::vector<T>> _colorClasses;
      T _maxColor;

      void coloringGraph() {
        auto verticesCount = _graph.get()->getVerticesCount();
        _colorVertices.resize(verticesCount);
        std::fill(_colorVertices.begin(), _colorVertices.end(), 0);
        std::vector<T> neighbours;
        auto bitArray = ColoringElements::Utils::BitArray();
        for (auto currentVertex = 0; currentVertex < verticesCount; ++currentVertex) {
          _graph.get()->getVertexNeighbours(currentVertex, neighbours);
          auto neighboursSize = static_cast<T>(neighbours.size());
          //mask neighbour
          for (auto currentNeighbour = 0; currentNeighbour < neighboursSize; ++currentNeighbour) {
            bitArray.setBit(_colorVertices[neighbours[currentNeighbour]]);
          }
          _colorVertices[currentVertex] = bitArray.findFirstFalse();
          _maxColor = std::max(static_cast<T>(_maxColor), _colorVertices[currentVertex]);
          bitArray.Clear();
        }
      }

      void makeColorClass() {
        _colorClasses.reserve(_maxColor);
        for (auto currentClass = 0; currentClass < _maxColor; ++currentClass) {
          _colorClasses.push_back(std::vector<T>());
        }
        auto verticesCount = _graph.get()->getVerticesCount();
        for (auto currentVertex = 0; currentVertex < verticesCount; ++currentVertex) {
          const T currentVertexColor = _colorVertices[currentVertex] - 1;
          _colorClasses[currentVertexColor].push_back(currentVertex);
        }
      }

     public:
      Coloring(Graph<T> & graph) {
        _graph = std::make_shared<Graph<T>>(graph);
        _maxColor = 0;
      }

      std::vector<T> getColorVertices() {
        if (_colorVertices.size() == 0) {
          this->coloringGraph();
        }
        auto verticesCount = _graph.get()->getVerticesCount();
        std::vector<T> colorVertices(verticesCount);
        std::copy(_colorVertices.begin(), _colorVertices.end(), colorVertices.begin());
        return colorVertices;
      }

      std::vector<std::vector<T>> getColorClasses() {
        if (_colorVertices.size() == 0) {
          this->coloringGraph();
        }

        if (_colorClasses.size() == 0) {
          this->makeColorClass();
        }
        std::vector<std::vector<T>> colorClasses(_maxColor);
        for (auto currentColor = 0; currentColor < _maxColor; ++currentColor) {
          auto currentColorSize = _colorClasses[currentColor].size();
          colorClasses[currentColor].resize(currentColorSize);
          std::copy(_colorClasses[currentColor].begin(), _colorClasses[currentColor].end(), colorClasses[currentColor].begin());
        }
        return colorClasses;
      }

      inline const T getColorCount() const {
        return _maxColor;
      }


    };
  }
}

