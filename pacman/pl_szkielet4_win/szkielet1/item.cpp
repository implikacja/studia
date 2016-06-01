#include "item.h"



item::item()
{
	mM = glm::mat4(1.0f);

}


item::~item()
{
}


void item::drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(mM));

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi�za� slot�w atrybut�w z tablicami z danymi
	glBindVertexArray(vao);
		
	//Narysowanie obiektu
	//printf ("%d", vao);
	//printf("Przed glDrawArrays\n");
	glDrawArrays(GL_TRIANGLES, 0, 36);//ostatnie to liczba wierzcho�k�w
	//printf("Po glDrawArrays\n");

	//Posprz�tanie po sobie (niekonieczne w sumie je�eli korzystamy z VAO dla ka�dego rysowanego obiektu)
	glBindVertexArray(0);
}