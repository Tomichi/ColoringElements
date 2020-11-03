#include "gtest/gtest.h"
#include "../../src/Graph/Graph.h"

TEST(Graph, createCompleteGraphK10) {
  const int VERTICES_COUNT = 10;
  std::vector<std::vector<int>> vertices(VERTICES_COUNT);
  // create complete graph K10
  for (auto currentVertex = 0; currentVertex < VERTICES_COUNT; ++currentVertex) {
    vertices[currentVertex].reserve(VERTICES_COUNT - 1);
    for(auto currentNeighbours = 0; currentNeighbours < VERTICES_COUNT; ++currentNeighbours) {
      if (currentVertex == currentNeighbours) continue; // skip self loop in graph
      vertices[currentVertex].emplace_back(currentNeighbours);
    }
  }

  auto testGraph = ColoringElements::Graph::Graph<int>(vertices);

  EXPECT_EQ(testGraph.getMaxVerexDegree(), VERTICES_COUNT - 1);

  const int SELECT_NEIGHBOUR = 2;
  auto neighboursCopy = std::vector<int>();
  auto neighbours = testGraph.getVertexNeighbours(SELECT_NEIGHBOUR);
  testGraph.getVertexNeighbours(SELECT_NEIGHBOUR, neighboursCopy);
  auto currentVertex = 0;
  for (auto indexPosition = 0; indexPosition < VERTICES_COUNT -1; ++indexPosition) {
    if (indexPosition == SELECT_NEIGHBOUR) {
      currentVertex += 1;
    }
    EXPECT_EQ(neighbours[indexPosition], currentVertex);
    EXPECT_EQ(neighbours[indexPosition], neighboursCopy[indexPosition]);
    currentVertex += 1;
  }

}
