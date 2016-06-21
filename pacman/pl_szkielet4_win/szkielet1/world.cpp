#include "world.h"



world::world()
{

}

world::world(bool mode)
{
	mode3d = mode;
	shaderProgram = NULL;
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniuj¹cy 
	cMap = new map();

	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	if (!mode3d)
	{
		cube c;
		wall = new item(c.vertexCount,1,1);
		bufVertices = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4);
		bufColors = makeBuffer(c.colors, c.vertexCount, sizeof(float) * 4);
		float colors[] = {
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
		};
		glBindVertexArray(wall->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO
		pacman *p = new pacman(6,cMap);
		itemList.push_back(p);

		bufColors = makeBuffer(colors, c.vertexCount, sizeof(float) * 4);
	glBindVertexArray(itemList[0]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

	}

	else
	{
		float* vertices = NULL;
		float* normals = NULL;
		int indeks;
		bool res = config::loadObj("cube.txt", vertices, normals, &indeks);
		wall = new item(indeks,1,1);
		if (res)
		{

			bufVertices = makeBuffer(vertices, indeks, sizeof(float) * 4);


			glBindVertexArray(wall->vao); //Uaktywnij nowo utworzony VAO
			assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
			assignVBOtoAttribute(shaderProgram, "color", bufVertices, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
			assignVBOtoAttribute(shaderProgram, "normal", bufVertices, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
			glBindVertexArray(0);
			printf("Stworzono buffor3d\n");

		}
	}


}

world::~world()
{
	delete cMap;
	delete wall;
	delete shaderProgram; //Usuniêcie programu cieniuj¹cego
	glDeleteBuffers(1, &bufVertices); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(1, &bufColors); //Usuniêcie VBO z kolorami
	glDeleteBuffers(1, &bufNormals); //Usuniêcie VBO z wektorami normalnymi
}

void world::drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów
	itemList[0]->changePosition();
		V = glm::lookAt( cameraPos, cameraTarget,cameraUp);
		if(!mode3d)drawMap2d(window, V);

		drawObject(itemList[0]->vao, itemList[0]->M, itemList[0]->vertexCount);
	glfwSwapBuffers(window);

}


void world::drawObject(GLuint vao, mat4 M, int vertexCount) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

									  //Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
}
void world::drawMap2d(GLFWwindow* window, mat4 V)
{
	cameraPos = glm::vec3(0.0f, 0.0f, cMap->h+4.0f);
	float scalex = float(-cMap->h/2);
	float scaley = float(cMap->h/2);

	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->w; j++)
		{
			if (cMap->m[j][i] == 'w')
			{
				if (scalex >= float(cMap->h/2) )scalex = float(-cMap->h/2);
				glm::mat4 M = glm::mat4(1.0f);
				M = glm::translate(M, vec3(scalex , scaley, 0.0f));
				drawObject(wall->vao, M, wall->vertexCount);

			}
	
		scalex	+= wall->width;
			
		}
		scaley -= wall->height;
	}

	


}

//Tworzy bufor VBO z tablicy
GLuint world::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który bêdzie zawiera³ tablicê danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicê do VBO

	return handle;
}

//Przypisuje bufor VBO do atrybutu 
void world::assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}