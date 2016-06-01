#include "world.h"



world::world()
{
	cMap = new map();
	a = new item();
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania
}


world::~world()
{
	delete cMap;
	delete a;
}

void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

		V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Narysuj obiekt
	a->drawObject(vao, shaderProgram, P, V);
	//Przerzuæ tylny bufor na przedni
	glfwSwapBuffers(window);

}

void world::drawScene2d(GLFWwindow* window, GLuint vao2d, ShaderProgram *shaderProgram) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

	glm::mat4 V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Narysuj obiekt

	a->drawObject(vao2d, shaderProgram, P, V);
	//Przerzuæ tylny bufor na przedni
	glfwSwapBuffers(window);

}