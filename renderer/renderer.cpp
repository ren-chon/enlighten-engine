#include "renderer.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

void Renderer::prepare() {
  glClear(GL_COLOR_BUFFER_BIT);
  // cornflower blue
  glClearColor(0.392f, 0.584f, 0.929f, 0.0f);
}
void Renderer::render(TexturedModel tModel) {
  RawModel model = tModel.getRawModel();
  // when to do something to vao bind it
  glBindVertexArray(model.getVaoID());
  // enable that attrib list
  glEnableVertexAttribArray(0);
  // use attrib vao 1 enable before rendering
  glEnableVertexAttribArray(1);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tModel.getTexture().getID());
  glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}