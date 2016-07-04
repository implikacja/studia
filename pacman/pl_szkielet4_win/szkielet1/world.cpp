#include "world.h"
#include "Windows.h"



world::world()
{

}

world::world(bool mode)
{
	timer = 0;
	mode3d = mode;

	shaderProgram = NULL;
	shaderProgramA = NULL;
	if (mode3d)
	{
		shaderProgram = new ShaderProgram("vshader3d.txt", NULL, "fshader3d.txt");
		shaderProgramA = new ShaderProgram("vshader3dA.txt", NULL, "fshader3d.txt");
		shaderProgramC = new ShaderProgram("vshader3dC.txt", NULL, "fshader3dC.txt");
	}
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
			1.0f, 1.0f, 1.0f, 1.0f,
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
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors2, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(coin->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0);

		pacman *p = new pacman(6,cMap);
		itemList.push_back(p);
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors, c.vertexCount, sizeof(float) * 4);
	glBindVertexArray(itemList[0]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		float colors3[] = {
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
		};
		ghost *g1 = new ghost(6, cMap, 1);
		itemList.push_back(g1);
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[1]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g2 = new ghost(6, cMap, 2);
		itemList.push_back(g2);
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[2]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g3 = new ghost(6, cMap, 3);
		itemList.push_back(g3);
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[3]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g4 = new ghost(6, cMap, 4);
		itemList.push_back(g4);
		glDeleteBuffers(1, &bufColors);
		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[4]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO
		glDeleteBuffers(1, &bufVertices);
		glDeleteBuffers(1, &bufColors);
		glDeleteBuffers(1, &bufNormals);

	}

	else
	{
		float* vertices = NULL;
		float* normals = NULL;
		float* uvs = NULL;
		int indeks;


		
		//tworzenie kostki
		bool res = config::loadObj("3d\\cube.txt", vertices, uvs, normals, &indeks);
		wall = new item(indeks,1,1);
		wall->shine = WALL_SHINE;
		if (res)
		{
			wall->tex = config::loadTexture("3d\\cube.png");
			createVAO(wall, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d kostki z uchwytem do tekstury %d\n",wall->tex);
		}

		//tworzenie podlogi
		res = config::loadObj("3d\\floor.txt", vertices, uvs, normals, &indeks);
		floor = new item(indeks, 1, 1);
		floor->shine = FLOOR_SHINE;
		if (res)
		{
			floor->tex = config::loadTexture("3d\\floor.png");
			createVAO(floor, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d podlogi z uchwytem do tekstury %d\n", floor->tex);
		}

		//tworzenie monety
		res = config::loadObj("3d\\coin.txt", vertices, uvs, normals, &indeks);
		coin = new item(indeks, 1, 1);
		coin->shine = COIN_SHINE;
		coin->t_max = COIN_SPEED;
		if (res)
		{
			coin->tex = config::loadTexture("3d\\coin.png");
			createVAO(coin, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d monety z uchwytem do tekstury %d\n", coin->tex);
		}

		//tworzenie pacmana
		float* vertices2 = NULL;
		float* normals2 = NULL;
		float* uvs2 = NULL;
		res = config::loadObj("3d\\pacman0.txt", vertices, uvs, normals, &indeks);
		bool res2 = config::loadObj("3d\\pacman1.txt", vertices2, uvs2, normals2, &indeks);
		pacman* p = new pacman(indeks, cMap);
		itemList.push_back(p);
		if (res && res2)
		{
			itemList[0]->tex = config::loadTexture("3d\\pacman.png");
			createVAO(itemList[0], vertices, vertices2, uvs2, normals, normals2, indeks);
			printf("Stworzono buffor3d pacmana z uchwytem do tekstury %d\n", itemList[0]->tex);
		}

		//tworzenie duchów
		char file[] = "3d\\ghost1.txt";
		char file2[] = "3d\\ghost1.png";
		for (int i = 0; i < 4; i++)
		{
			file[8] = i + 49;
			file2[8] = i + 49;
			res = config::loadObj(file, vertices, uvs, normals, &indeks);
			ghost* g = new ghost(indeks, cMap, i+1);
			itemList.push_back(g);
			if (res)
			{
				itemList[i+1]->tex = config::loadTexture(file2);
				createVAO(itemList[i+1], vertices, uvs, normals, indeks);
				printf("Stworzono buffor3d ducha %d z uchwytem do tekstury %d\n", i, itemList[i+1]->tex);
			}

		}

	}
}

void world::loadText(const char* path, vec4 color)
{
	delete text;
	textColor = color;

	float* vertices = NULL;
	float* normals = NULL;
	int indeks;

	//tworzenie kostki
	bool res = config::loadObj(path, vertices, normals, &indeks);
	text = new item(indeks, 1, 1);
	text->t_max = TEXT_SPEED;
	if (res)
	{
		bufVertices = makeBuffer(vertices, indeks, sizeof(float) * 4);
		bufNormals = makeBuffer(normals, indeks, sizeof(float) * 4);

		glBindVertexArray(text->vao); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgramC, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgramC, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0);

		glDeleteBuffers(1, &bufVertices);
		glDeleteBuffers(1, &bufNormals);

		delete[] vertices;
		delete[] normals;
		printf("Stworzono buffor3d tekstu z pliku %s\n", path);
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

	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufNormals);
	glDeleteBuffers(1, &bufUvs);

	delete[] vertices;
	delete[] normals;
	delete[] uvs;
}

void world::createVAO(item* i, float* vertices1, float* vertices2, float* uvs, float* normals1, float* normals2, int indeks)
{
	bufVertices = makeBuffer(vertices1, indeks, sizeof(float) * 4);
	bufNormals = makeBuffer(normals1, indeks, sizeof(float) * 4);
	bufUvs = makeBuffer(uvs, indeks, sizeof(float) * 2);

	glBindVertexArray(i->vao); //Uaktywnij nowo utworzony VAO
	assignVBOtoAttribute(shaderProgramA, "vertex1", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgramA, "uv", bufUvs, 2); //"uv" odnosi siê do deklaracji "in vec2 uv;" w vertex shaderze
	assignVBOtoAttribute(shaderProgramA, "normal1", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
	glBindVertexArray(0);


	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufNormals);
	glDeleteBuffers(1, &bufUvs);
	delete[] vertices1;
	delete[] normals1;
	delete[] uvs;

	bufVertices = makeBuffer(vertices2, indeks, sizeof(float) * 4);
	bufNormals = makeBuffer(normals2, indeks, sizeof(float) * 4);

	glBindVertexArray(i->vao); //Uaktywnij nowo utworzony VAO
	assignVBOtoAttribute(shaderProgramA, "vertex2", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgramA, "normal2", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
	glBindVertexArray(0);


	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufNormals);
	glDeleteBuffers(1, &bufUvs);
	delete[] vertices2;
	delete[] normals2;

}

world::~world()
{
	delete cMap;
	delete wall;
	delete floor;
	delete coin;
	delete text;
	delete itemList[0];
	delete itemList[1];
	delete itemList[2];
	delete itemList[3];
	delete itemList[4];
	delete shaderProgram; //Usuniêcie programu cieniuj¹cego
	if (mode3d)
	{
		delete shaderProgramC;
		delete shaderProgramA;
	}

	glDeleteBuffers(1, &bufVertices); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(1, &bufColors); //Usuniêcie VBO z kolorami
	glDeleteBuffers(1, &bufNormals); //Usuniêcie VBO z wektorami normalnymi
	glDeleteBuffers(1, &bufUvs);
}

void world::changeCamera()
{
	float x = itemList[0]->getRealX() - 0.5f;
	float y = itemList[0]->getRealY() - 0.5f;
	cameraTarget = glm::vec3(x, y, 0.5f);
	cameraPos = glm::vec3(x,y-config::cam, config::cam);
}

glm::vec3 world::setLight0()
{
	vec3 l;
	l.x = 0.0f;
	l.y = 2 * float(cMap->h);
	l.z = -float(cMap->h) / 2;
	return l;
}

glm::vec3 world::setLight1()
{
	vec3 l;
	l.x = cameraTarget.x;
	l.y = cameraTarget.y + 2.0f;
	l.z = cameraTarget.z + 0.0f;
	return l;
}

void world::drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów


	if (mode3d) changeCamera();

	V = glm::lookAt( cameraPos, cameraTarget,cameraUp);


	if (mode3d)
	{
		if (config::end != 0)
		{
			float angle = (float)text->t / text->t_max;
			drawObject(text->vao, angle, mat4(1.0f) ,text->vertexCount);
		}
		else
		{
			drawMap3d(window, V);

			float t = (float)itemList[0]->t / itemList[0]->t_max;
			drawObject(itemList[0]->vao, itemList[0]->tex, itemList[0]->shine, t*PI, itemList[0]->getRealMatrix(), itemList[0]->vertexCount);

			for (int i = 1; i<itemList.size(); i++)
				drawObject(itemList[i]->vao, itemList[i]->tex, itemList[i]->shine, itemList[i]->getRealMatrix(), itemList[i]->vertexCount);
		}
		
	}
	else
	{
		drawMap2d(window, V);
		for (int i = 0; i<itemList.size(); i++)
		drawObject(itemList[i]->vao, itemList[i]->M, itemList[i]->vertexCount);
	}

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

void world::drawObject(GLuint vao, GLuint tex, float s, mat4 M, int vertexCount) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));

	vec3 l0 = setLight0();
	vec3 l1 = setLight1();

	glUniform4f(shaderProgram->getUniformLocation("Light1"), l1.x, l1.y, l1.z, 1); //œwiat³o wydzielane przez pakmana
	glUniform4f(shaderProgram->getUniformLocation("Light0"), l0.x, l0.y, l0.z, 1); //œwiat³o podstawowe, sta³e dla œwiata
	glUniform1f(shaderProgram->getUniformLocation("shine"), s);
	glUniform1f(shaderProgram->getUniformLocation("alpha"), ALPHA); //udzia³ œwiat³a 0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(shaderProgram->getUniformLocation("tex"), 0); //0-numer jednostki teksturuj¹cej

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void world::drawObject(GLuint vao, GLuint tex, float s, float t, mat4 M, int vertexCount) {

	shaderProgramA->use();

	glUniformMatrix4fv(shaderProgramA->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgramA->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgramA->getUniformLocation("M"), 1, false, glm::value_ptr(M));

	vec3 l0 = setLight0();
	vec3 l1 = setLight1();

	glUniform4f(shaderProgramA->getUniformLocation("Light1"), l1.x, l1.y, l1.z, 1); //œwiat³o wydzielane przez pakmana
	glUniform4f(shaderProgramA->getUniformLocation("Light0"), l0.x, l0.y, l0.z, 1); //œwiat³o podstawowe, sta³e dla œwiata
	glUniform1f(shaderProgramA->getUniformLocation("shine"), s);
	glUniform1f(shaderProgramA->getUniformLocation("alpha"), ALPHA); //udzia³ œwiat³a 0
	glUniform1f(shaderProgramA->getUniformLocation("t"), t); //zmienna do interpolowania wierzcho³ków

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(shaderProgramA->getUniformLocation("tex"), 0); //0-numer jednostki teksturuj¹cej

															  //Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void world::drawObject(GLuint vao, float t, mat4 M, int vertexCount) 
{

	shaderProgramC->use();

	mat4 tmp_V = glm::lookAt(vec3(0.0f,-5.0f,0.0f),vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,1.0f));
	mat4 tmp_M = glm::rotate(glm::mat4(1.0f),t*360,vec3(0,0,1));

	glUniformMatrix4fv(shaderProgramC->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgramC->getUniformLocation("V"), 1, false, glm::value_ptr(tmp_V));
	glUniformMatrix4fv(shaderProgramC->getUniformLocation("M"), 1, false, glm::value_ptr(tmp_M));
	glUniform4f(shaderProgramC->getUniformLocation("light"), 0.0f, 2.0f, 0.0f, 1);

	glUniform4f(shaderProgramC->getUniformLocation("color"), textColor.x, textColor.y, textColor.z, 1);

															   //Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

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
				if (scalex > float(cMap->h/2) )scalex = float(-cMap->h/2);
				glm::mat4 M = glm::mat4(1.0f);
				M = glm::translate(M, vec3(scalex , scaley, 0.0f));
				drawObject(wall->vao, M, wall->vertexCount);

			}
			if (cMap->m[j][i] == 'm')
			{


					if (j != itemList[1]->pos.intX || i != itemList[1]->pos.intY)
						if(j != itemList[2]->pos.intX || i != itemList[2]->pos.intY)
							if(j != itemList[3]->pos.intX || i != itemList[3]->pos.intY)
								if(j != itemList[4]->pos.intX || i != itemList[4]->pos.intY)
								{
									if (scalex > float(cMap->h / 2))scalex = float(-cMap->h / 2);
									glm::mat4 M = glm::mat4(1.0f);
									M = glm::translate(M, vec3(scalex, scaley, 0.0f));
									drawObject(coin->vao, M, coin->vertexCount);
								}

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
				glm::mat4 Mw = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
				drawObject(wall->vao, wall->tex, wall->shine, Mw, wall->vertexCount);
			}
			else
			{
				//rysowanie podlogi
				glm::mat4 Mf = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
				drawObject(floor->vao, floor->tex, floor->shine, Mf, floor->vertexCount);
				if (cMap->m[j][i] == 'm')
				{
					//rysowanie monety
					float angle = float(coin->t) / float(coin->t_max)*360;
					glm::mat4 Mc = glm::translate(M, glm::vec3(-0.5f, -0.5f, 0.5f));
					Mc = glm::rotate(Mc, angle, vec3(0, 0, 1));
					drawObject(coin->vao, coin->tex, coin->shine, Mc, coin->vertexCount);
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


void world::testowanie(const char* path,float* vertices, float* uvs, float* normals, int indeks)
{
	FILE* file = fopen(path, "w");
	fprintf(file, "vertices[] = \n");
	for (int i = 0; i < indeks; i++) 
	{
		if (i % 3 == 0) fprintf(file, "\n");
		for (int j = 0; j < 4; j++)
			fprintf(file, "\t%f", vertices[i * 4 + j]);
		fprintf(file, "\n");
	}

	fprintf(file, "uvs[] = \n");
	for (int i = 0; i < indeks; i++)
	{
		if (i % 3 == 0) fprintf(file, "\n");
		for (int j = 0; j < 2; j++)
			fprintf(file, "\t%f", uvs[i * 2 + j]);
		fprintf(file, "\n");
	}

	fprintf(file, "normals[] = \n");
	for (int i = 0; i < indeks; i++)
	{
		if (i % 3 == 0) fprintf(file, "\n");
		for (int j = 0; j < 4; j++)
			fprintf(file, "\t%f", normals[i * 4 + j]);
		fprintf(file, "\n");
	}

	fclose(file);
}

void world::logic()
{
	if (!mode3d)
	{
		timer++;
			if (timer == 20)
			{
				itemList[0]->changePosition(cMap, coins);
				for (int i = 1; i<itemList.size(); i++)
					itemList[i]->changePosition(cMap, hp);
				timer = 0;
			}

	}
	else
	{
		if(itemList[0]->t==0) itemList[0]->changePosition(cMap, coins);
		for (int i = 1; i<itemList.size(); i++)
			if (itemList[i]->t == 0) itemList[i]->changePosition(cMap, hp);
		for (int i = 0; i<itemList.size(); i++)
			itemList[i]->nextFrame();
		coin->nextFrame();

		//Sleep(2000);
	}
}