#include <rendering/Light.hpp>

namespace rendering
{

    void Light::drawDirectionnal(rendering::Camera *camera, rendering::ShaderManager &LightProgram, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, game::Player &player)
    {

        glm::mat4 ViewMatrix = camera->getViewMatrix();
        LightProgram.use();
        LightProgram.uniform3f("uKdiffuseD", 0.4,0.4,1.0);
        LightProgram.uniform3f("uKspecularD", 0.2,0.5,0.8);
        LightProgram.uniform1i("uShininess", 10);
        
        glm::vec4 LightDir = camera->getViewMatrix() * glm::vec4(0.0, 1.0, 0.0, 0.0);
        LightProgram.uniform3f("uLightDir_vs", LightDir.x, LightDir.y, LightDir.z);

        LightProgram.uniform3f("uLightIntensity", 0.6, 0.6, 0.6);

        LightProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
        LightProgram.uniformMatrix4fv("uMVMatrix", ViewMatrix);
        LightProgram.uniformMatrix4fv("uNormalMatrix", NormalMatrix);

        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(1., 0.6, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
    }

    void Light::drawPonctual(rendering::Camera *camera, rendering::ShaderManager &LightProgram, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, game::Player &player)
    {

        glm::mat4 ViewMatrix = camera->getViewMatrix();
        LightProgram.use();
        LightProgram.uniform3f("uKdiffuseP", 1,0.5,0);
        LightProgram.uniform3f("uKspecularP", 1,0.5,0);
        LightProgram.uniform1i("uShininess", 10);

        glm::vec4 LightPos =  camera->getViewMatrix() * glm::vec4(player.convertCoord(),1.0);        
        LightProgram.uniform3f("uLightPos_vs", LightPos.x, LightPos.y, LightPos.z);

        LightProgram.uniform3f("uLightIntensity", 0.6, 0.6, 0.6);

        LightProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
        LightProgram.uniformMatrix4fv("uMVMatrix", ViewMatrix);
        LightProgram.uniformMatrix4fv("uNormalMatrix", NormalMatrix);

        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(1., 0.6, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
    }

}