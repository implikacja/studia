#include "world.h"



world::world()
{

}

world::world(bool mode)
{
	mode3d = mode;
	shaderProgram = NULL;
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniuj�cy 
	cMap = new map();
	wall = new item(36);
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania
	/*cube c;
	bufVertices = makeBuffer(c.vertices, c.vertexCount, sizeof(float)*4);
	glBindVertexArray(wall->vao); //Uaktywnij nowo utworzony VAO
	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze
	glBindVertexArray(0); //Dezaktywuj VAO*/


	float* vertices = NULL;
	float* normals = NULL;
	int indeks;
	bool res = config::loadObj("cube.txt", vertices, normals, &indeks);

	if (res)
	{

		bufVertices = makeBuffer(vertices, indeks, sizeof(float) *4);


		glBindVertexArray(wall->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufVertices, 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufVertices, 4); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0);
		printf("Stworzono buffor3d\n");

	}
}

world::~world()
{
	delete cMap;
	delete wall;
	delete shaderProgram; //Usuni�cie programu cieniuj�cego
	glDeleteBuffers(1, &bufVertices); //Usuni�cie VBO z wierzcho�kami
	glDeleteBuffers(1, &bufColors); //Usuni�cie VBO z kolorami
	glDeleteBuffers(1, &bufNormals); //Usuni�cie VBO z wektorami normalnymi
}

void world::drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysuj�cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolor�w

		V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

		drawObject(wall->vao, wall->M, wall->vertexCount);
	glfwSwapBuffers(window);

}


void world::drawObject(GLuint vao, mat4 M, int vertexCount) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi�za� slot�w atrybut�w z tablicami z danymi
	glBindVertexArray(vao);

	//Narysowanie obiektu
	//printf ("%d", vao);
	//printf("Przed glDrawArrays\n");
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);//ostatnie to liczba wierzcho�k�w
									  //printf("Po glDrawArrays\n");

									  //Posprz�tanie po sobie (niekonieczne w sumie je�eli korzystamy z VAO dla ka�dego rysowanego obiektu)
	glBindVertexArray(0);
}

//Tworzy bufor VBO z tablicy
GLuint world::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablic� do VBO

	return handle;
}

//Przypisuje bufor VBO do atrybutu 
void world::assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slot�w dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj� by� brane z aktywnego VBO
}