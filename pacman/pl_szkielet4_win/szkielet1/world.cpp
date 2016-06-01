#include "world.h"



world::world()
{
	cMap = new map();
	wall = new item();
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania
}


world::~world()
{
	delete cMap;
	delete wall;
}

void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram) {
	//************Tutaj umieszczaj kod rysuj�cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolor�w

		V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	drawObject(vao, shaderProgram, wall->M);
	glfwSwapBuffers(window);

}

void world::drawScene2d(GLFWwindow* window, GLuint vao2d, ShaderProgram *shaderProgram) {
	//************Tutaj umieszczaj kod rysuj�cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolor�w

	V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Narysuj obiekt
	drawObject(vao2d, shaderProgram, wall->M);
	//Przerzu� tylny bufor na przedni
	glfwSwapBuffers(window);

}

void world::drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 M) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));

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