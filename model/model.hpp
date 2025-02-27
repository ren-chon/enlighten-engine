#pragma once

class RawModel {
public:
  int vaoID, vertexCount;

  RawModel(int vID, int vtxCount) {
    vaoID = vID;
    vertexCount = vtxCount;
  };

  int getVaoID() { return vaoID; }

  int getVertexCount() { return vertexCount; }
};