#pragma once
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <set>
#include "../Graph/Graph.h"
namespace ColoringElements{
  namespace Mesh{
    template<typename T>
    class FunctionSpace{
     private:
      const T _numberOfMesh;
      const T _numberOfFunction;
      std::shared_ptr<Graph::Graph<T>> _graph;

     public:
      const T getNumberOfMesh() const { return _numberOfMesh;}
      const T getNumberOfFunction() const { return _numberOfFunction;}
      // function support on mesh is 2D array where, first index
      // is functionId and the second one is meshId where functionId has nonzero support
      // It's only for class where basis function is the same
      FunctionSpace(std::vector<std::vector<T>> & functionsSupportOnMesh, const T numberOfMesh) {
        _numberOfFunction = functionsSupportOnMesh.size();
        assert(_numberOfFunction > 0);
        assert(_numberOfMesh > 0);

        _numberOfMesh = numberOfMesh;
        std::vector<std::set<T>> meshSetNeighbours(_numberOfMesh);
        for (auto currentFunction = 0; currentFunction < _numberOfFunction; ++currentFunction) {
          auto supportSize = functionsSupportOnMesh[currentFunction].size();
          // todo optimize inner loop
          for (auto currentMesh = 0; currentMesh < supportSize; ++currentMesh) {
            for (auto neighbourMesh = currentMesh; neighbourMesh < supportSize; ++neighbourMesh) {
              if (currentMesh == neighbourMesh) continue; // inner loop at GraphT is not permitted
              meshSetNeighbours[functionsSupportOnMesh[currentFunction][currentMesh]].emplace(functionsSupportOnMesh[currentFunction][neighbourMesh]);
              meshSetNeighbours[functionsSupportOnMesh[currentFunction][neighbourMesh]].emplace(functionsSupportOnMesh[currentFunction][currentMesh]);
            }
          }
        }

        // structure for create GraphT
        std::vector<std::vector<T>> meshNeighbours(_numberOfMesh);
        for (auto currentMesh = 0; currentMesh < _numberOfMesh; ++currentMesh) {
          meshNeighbours[currentMesh].reserve(meshSetNeighbours[currentMesh].size());
          for (auto & neighbors: meshSetNeighbours[currentMesh]) {
            meshNeighbours[currentMesh].emplace_back(neighbors);
          }
        }
        _graph = std::make_shared<T>(Graph::Graph<T>(meshNeighbours));
     }
    };
  }
}
