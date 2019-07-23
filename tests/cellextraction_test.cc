/*
 * Copyright 2019 Computer Graphics Group, RWTH Aachen University
 * Author: Max Lyon <lyon@cs.rwth-aachen.de>
 *
 * This file is part of HexEx.
 *
 * HexEx is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * HexEx is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HexEx.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>
#include "common.hh"
#include <HexExtractor.hh>

using namespace HexEx;

TEST(CellExtraction, CellExtractionTest)
{

  for (auto transition : {false, true})
    for (auto size : {1,2,3,4,5})
    {

      TetrahedralMesh mesh;
      if (transition)
        createCubeWithTransition(mesh, size);
      else
        createCube(mesh, size);

      EXPECT_EQ(8u, mesh.n_vertices());

      OpenVolumeMesh::CellPropertyT<std::map<VertexHandle, HexEx::Vec3d>> parametrization = mesh.template request_cell_property<std::map<OpenVolumeMesh::VertexHandle, HexEx::Vec3d>>("Parametrization");
      HexExtractor hexExtractor(mesh, parametrization);
      hexExtractor.extract();

      HexahedralMesh hexMesh;
      hexExtractor.getHexMesh(hexMesh);

      unsigned int expectedNumberOfCells = size*size*size;

      EXPECT_EQ(expectedNumberOfCells, hexMesh.n_cells()) << "Size: " << size;

    }

}


TEST(CellExtraction, CellExtractionMasterVertexTest)
{

  TetrahedralMesh mesh;
  createMasterVertexMesh(mesh);

  OpenVolumeMesh::CellPropertyT<std::map<VertexHandle, HexEx::Vec3d>> parametrization = mesh.template request_cell_property<std::map<OpenVolumeMesh::VertexHandle, HexEx::Vec3d>>("Parametrization");
  HexExtractor hexExtractor(mesh, parametrization);
  hexExtractor.extract();

  HexahedralMesh hexMesh;
  hexExtractor.getHexMesh(hexMesh);

  unsigned int expectedNumberOfCells = 8;

  EXPECT_EQ(expectedNumberOfCells, hexMesh.n_cells());

}

TEST(CellExtraction, CellExtractionPrismTest)
{


  TetrahedralMesh mesh;
  createPrism(mesh);
  OpenVolumeMesh::CellPropertyT<std::map<VertexHandle, HexEx::Vec3d>> parametrization = mesh.template request_cell_property<std::map<OpenVolumeMesh::VertexHandle, HexEx::Vec3d>>("Parametrization");
  HexExtractor hexExtractor(mesh, parametrization);
  hexExtractor.extract();

  HexahedralMesh hexMesh;
  hexExtractor.getHexMesh(hexMesh);

  unsigned int expectedNumberOfCells = 6;

  EXPECT_EQ(expectedNumberOfCells, hexMesh.n_cells());

}

TEST(CellExtraction, CellExtractionFiveAdvancedTest)
{

  std::string filename = "testdata/fiveadvanced.hexex";
  HexExtractor hexExtractor(filename);

  ASSERT_GE(hexExtractor.getInputMesh().n_cells(), 0) << "could not load mesh";

  hexExtractor.extract();

  HexahedralMesh hexMesh;
  hexExtractor.getHexMesh(hexMesh);

  EXPECT_GE(hexMesh.n_cells(), 0) << "nothing extracted";
}


TEST(CellExtraction, CellExtractionFiveFineTest)
{
  std::string filename = "testdata/fiveFine.hexex";
  HexExtractor hexExtractor(filename);

  ASSERT_GE(hexExtractor.getInputMesh().n_cells(), 0) << "could not load mesh";

  hexExtractor.extract();

  HexahedralMesh hexMesh;
  hexExtractor.getHexMesh(hexMesh);

  EXPECT_GE(hexMesh.n_cells(), 0) << "nothing extracted";
}
