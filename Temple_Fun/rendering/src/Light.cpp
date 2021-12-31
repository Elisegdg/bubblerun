#include <rendering/Light.hpp>

namespace rendering
{

    void Light::draw(rendering::Camera *camera, rendering::ShaderManager &LightProgram, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix)
    {

        glm::mat4 ViewMatrix = camera->getViewMatrix();
        LightProgram.use();
        LightProgram.uniform3f("uKd", 0.4, 0.4, 1.0);
        LightProgram.uniform3f("uKs", 0.2, 0.5, 0.8);
        LightProgram.uniform3f("uKd2", 0.5, 0.0, 0);
        LightProgram.uniform3f("uKs2", 0.5, 0, 0);
        LightProgram.uniform1i("uShininess", 10);

        glm::vec4 LightDir = camera->getViewMatrix() * glm::vec4(0.0, 1.0, 0.0, 0.0);
        LightProgram.uniform3f("uLightDir_vs", LightDir.x, LightDir.y, LightDir.z);

        glm::vec4 LightPos = glm::vec4(0.5, 0.5, 0.5, 0.0) * camera->getViewMatrix();
        LightProgram.uniform3f("uLightPos_vs", LightPos.x, LightPos.y, LightPos.z);

        LightProgram.uniform3f("uLightIntensity", 0.6, 0.6, 0.6);

        LightProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
        LightProgram.uniformMatrix4fv("uMVMatrix", ViewMatrix);
        LightProgram.uniformMatrix4fv("uNormalMatrix", NormalMatrix);

        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(1., 0.6, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
    }

}