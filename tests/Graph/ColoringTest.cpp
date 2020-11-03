#include "gtest/gtest.h"
#include "../../src/Graph/Coloring.h"


TEST(Coloring, colorCompleteGraphK10) {
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
  auto coloringGraph = ColoringElements::Graph::Coloring<int>(testGraph);
  auto coloringElement = coloringGraph.getColorVertices();
  EXPECT_EQ(coloringGraph.getColorCount(), VERTICES_COUNT);
  auto coloringClass = coloringGraph.getColorClasses();
  EXPECT_EQ(coloringClass.size(), VERTICES_COUNT);
  for (auto currentColor = 0; currentColor < VERTICES_COUNT; ++currentColor) {
    EXPECT_EQ(coloringClass[currentColor].size(), 1);
  }

}


TEST(Coloring, colorCycleC5) {
  const int VERTICES_COUNT = 5;
  std::vector<std::vector<int>> vertices(VERTICES_COUNT);
  // create complete graph K10
  for (auto currentVertex = 0; currentVertex < VERTICES_COUNT; ++currentVertex) {
    vertices[currentVertex].reserve(2);
    vertices[currentVertex].push_back((currentVertex + 1) % VERTICES_COUNT);
    vertices[currentVertex].push_back((VERTICES_COUNT + currentVertex - 1) % VERTICES_COUNT);
  }

  auto testGraph = ColoringElements::Graph::Graph<int>(vertices);
  auto coloringGraph = ColoringElements::Graph::Coloring<int>(testGraph);
  auto coloringElement = coloringGraph.getColorVertices();
  EXPECT_EQ(coloringGraph.getColorCount(), 3);
  auto coloringClass = coloringGraph.getColorClasses();
  EXPECT_EQ(coloringClass.size(), 3);

  EXPECT_EQ(coloringClass[0].size(), 2);
  EXPECT_EQ(coloringClass[1].size(), 2);
  EXPECT_EQ(coloringClass[2].size(), 1);
}
