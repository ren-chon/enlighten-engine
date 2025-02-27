#include "renderer.hpp"
#include "../toolbox/maths.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

void Renderer::prepare() {
  glClear(GL_COLOR_BUFFER_BIT);
  // cornflower blue
  glClearColor(0.392f, 0.584f, 0.929f, 0.0f);
}
void Renderer::render(Entity entity, StaticShader shader) {
  TexturedModel model = entity.getModel();
  RawModel rawModel = model.getRawModel();
  // when to do something to vao bind it
  glBindVertexArray(rawModel.getVaoID());
  // enable that attrib list
  glEnableVertexAttribArray(0);
  // use attrib vao 1 enable before rendering
  glEnableVertexAttribArray(1);
  Maths meth;
  glm::mat4 transformationMatrix = meth.createTransformationMatrix(
      entity.getPositions(), entity.getRotX(), entity.getRotY(),
      entity.getRotZ(), entity.getScale());
  shader.LoadTransformationMatrix(transformationMatrix);
  // setting and acitiving the texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
  glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
  // disable unbind
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}