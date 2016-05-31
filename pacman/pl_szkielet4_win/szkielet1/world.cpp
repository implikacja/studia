#include "world.h"



world::world()
{
	printf("Konstruktor world/n");
	//itemList = new item[5];
	a = new item;
}


world::~world()
{
	printf("Destruktor world/n");
	delete a;
	//delete[] (itemList);
}

void world::drawScene(GLFWwindow* window, GLuint vao, ShaderProgram *shaderProgram) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

	glm::mat4 P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	glm::mat4 V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Wylicz macierz modelu rysowanego obiektu
	glm::mat4 M = glm::mat4(1.0f);
	//item a;
	//Narysuj obiekt
	for (int i = 0; i < 9; i++)
	{
		
	}
	a->drawObject(vao, shaderProgram, P, V, M);
	//Przerzuæ tylny bufor na przedni
	glfwSwapBuffers(window);

}