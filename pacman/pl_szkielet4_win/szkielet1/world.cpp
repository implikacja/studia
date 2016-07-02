#include "world.h"



world::world()
{

}

world::world(bool mode)
{
	timer = 0;
	mode3d = mode;
	distance = 5.0f;

	shaderProgram = NULL;
	if(mode3d) shaderProgram = new ShaderProgram("vshader3d.txt", NULL, "fshader3d.txt");
	else shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniuj¹cy 

	cMap = new map();

	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	coins = 0;
	hp = 3;
	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->h; j++)
		{
			if (cMap->m[j][i] == 'm') coins++;

		}
	}
	if (!mode3d)
	{
		cube c;
		wall = new item(c.vertexCount,1,1);
		coin = new item(c.vertexCount, 1, 1);
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
		float colors2[] = {
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
		};
		glBindVertexArray(wall->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		bufColors = makeBuffer(colors2, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(coin->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0);

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
		//tworzenie kostki
		float* vertices = NULL;
		float* normals = NULL;
		float* uvs = NULL;
		int indeks;
		bool res = config::loadObj("3d\\cube.txt", vertices, uvs, normals, &indeks);
		wall = new item(indeks,1,1);
		if (res)
		{
			wall->tex = config::loadTexture("3d\\cube.png");
			createVAO(wall, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d kostki\n");
		}

		//tworzenie podlogi
		res = config::loadObj("3d\\floor.txt", vertices, uvs, normals, &indeks);
		floor = new item(indeks, 1, 1);
		if (res)
		{
			floor->tex = config::loadTexture("3d\\floor.png");
			createVAO(floor, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d podlogi\n");
		}

		//tworzenie monety
		res = config::loadObj("3d\\coin.txt", vertices, uvs, normals, &indeks);
		coin = new item(indeks, 1, 1);
		if (res)
		{
			coin->tex = config::loadTexture("3d\\coin.png");
			createVAO(coin, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d monety\n");
		}

		//tworzenie pacmana
		res = config::loadObj("3d\\kulka.txt", vertices, uvs, normals, &indeks);
		pacman* p = new pacman(indeks, cMap);
		itemList.push_back(p);
		if (res)
		{
			itemList[0]->tex = config::loadTexture("3d\\kulka.png");
			createVAO(itemList[0], vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d pacmana\n");
		}

	}
}

void world::createVAO(item* i, float* vertices, float* uvs, float* normals, int indeks)
{
	bufVertices = makeBuffer(vertices, indeks, sizeof(float) * 4);
	bufNormals = makeBuffer(normals, indeks, sizeof(float) * 4);
	bufUvs = makeBuffer(uvs, indeks, sizeof(float) * 2);

	glBindVertexArray(i->vao); //Uaktywnij nowo utworzony VAO
	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "uv", bufUvs, 2); //"uv" odnosi siê do deklaracji "in vec2 uv;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
	glBindVertexArray(0);

	delete[] vertices;
	delete[] normals;
	delete[] uvs;
}

world::~world()
{
	delete cMap;
	delete wall;
	delete floor;
	delete coin;
	delete itemList[0];
	delete shaderProgram; //Usuniêcie programu cieniuj¹cego
	glDeleteBuffers(1, &bufVertices); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(1, &bufColors); //Usuniêcie VBO z kolorami
	glDeleteBuffers(1, &bufNormals); //Usuniêcie VBO z wektorami normalnymi
	glDeleteBuffers(1, &bufUvs);
}

void world::changeCamera()
{
	float x = (itemList[0]->pos).x;
	float y = (itemList[0]->pos).y;
	cameraTarget = glm::vec3(x, y, 0.0f);
	cameraPos = glm::vec3(x,y-distance, distance);
}

void world::drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów
	timer++;
	if (timer == 20)
	{
		itemList[0]->changePosition(cMap,coins);
		timer = 0;
	}

	if (mode3d) changeCamera();

	V = glm::lookAt( cameraPos, cameraTarget,cameraUp);
	if(!mode3d)drawMap2d(window, V);
	else drawMap3d(window, V);

	drawObject(itemList[0]->vao, itemList[0]->M, itemList[0]->vertexCount);
	glfwSwapBuffers(window);

}


void world::drawObject(GLuint vao, mat4 M, int vertexCount) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));
	glUniform4f(shaderProgram->getUniformLocation("Light0"), 0, 0, 5, 1);

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

									  //Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
}

void world::drawObject(GLuint vao, GLuint tex, mat4 M, int vertexCount) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));
	glUniform1i(shaderProgram->getUniformLocation("tex"), 0);

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
}

void world::drawMap2d(GLFWwindow* window, mat4 V)
{
	//cMap->bottom=
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
			if (cMap->m[j][i] == 'm')
			{
				if (scalex >= float(cMap->h / 2))scalex = float(-cMap->h / 2);
				glm::mat4 M = glm::mat4(1.0f);
				M = glm::translate(M, vec3(scalex, scaley, 0.0f));
				drawObject(coin->vao, M, coin->vertexCount);

			}
	
		scalex	+= config::width;
			
		}
		scaley -= config::width;
	}

	



}

void world::drawMap3d(GLFWwindow* window, mat4 V)
{
	float h = cMap->h / 2;
	float w = -cMap->w / 2;
	glm::mat4 M = glm::mat4(1.0f);

	for (int i = 0; i < cMap->h; i++)
	{
		for (int j = 0; j < cMap->w; j++)
		{
			M = glm::translate(glm::mat4(1.0f), glm::vec3(w+j,h-i,0.0f));
			if (cMap->m[j][i] == 'w')
			{
				//rysowanie kostki
				drawObject(wall->vao, wall->tex, M, wall->vertexCount);
			}
			else
			{
				//rysowanie podlogi
				M = glm::translate(M, glm::vec3(0.0f, 0.0f, -1.0f));
				drawObject(floor->vao, floor->tex, M, floor->vertexCount);
				if (cMap->m[j][i] == 'm')
				{
					//rysowanie monety
					M = glm::translate(M, glm::vec3(0.5f, 0.5f, 0.5f));
					drawObject(coin->vao, coin->tex, M, coin->vertexCount);
				}
			}
		}
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