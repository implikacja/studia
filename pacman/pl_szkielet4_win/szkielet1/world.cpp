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

		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[1]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g2 = new ghost(6, cMap, 2);
		itemList.push_back(g2);

		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[2]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g3 = new ghost(6, cMap, 3);
		itemList.push_back(g3);

		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[3]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

		ghost *g4 = new ghost(6, cMap, 4);
		itemList.push_back(g4);

		bufColors = makeBuffer(colors3, c.vertexCount, sizeof(float) * 4);
		glBindVertexArray(itemList[4]->vao);
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0); //Dezaktywuj VAO

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
		wall->shine = 500.0f;
		if (res)
		{
			wall->tex = config::loadTexture("3d\\cube.png");
			createVAO(wall, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d kostki z uchwytem do tekstury %d\n",wall->tex);
		}

		//tworzenie podlogi
		res = config::loadObj("3d\\floor.txt", vertices, uvs, normals, &indeks);
		floor = new item(indeks, 1, 1);
		floor->shine = 400.0f;
		if (res)
		{
			floor->tex = config::loadTexture("3d\\floor.png");
			createVAO(floor, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d podlogi z uchwytem do tekstury %d\n", floor->tex);
		}

		//tworzenie monety
		res = config::loadObj("3d\\coin.txt", vertices, uvs, normals, &indeks);
		coin = new item(indeks, 1, 1);
		coin->shine = 5.0f;
		coin->t_max = 5000;
		if (res)
		{
			coin->tex = config::loadTexture("3d\\coin.png");
			createVAO(coin, vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d monety z uchwytem do tekstury %d\n", coin->tex);
		}

		//tworzenie pacmana
		res = config::loadObj("3d\\ghost1.txt", vertices, uvs, normals, &indeks);
		pacman* p = new pacman(indeks, cMap);
		p->shine = 300.0f;
		itemList.push_back(p);
		if (res)
		{
			itemList[0]->tex = config::loadTexture("3d\\ghost1.png");
			createVAO(itemList[0], vertices, uvs, normals, indeks);
			printf("Stworzono buffor3d pacmana z uchwytem do tekstury %d\n", itemList[0]->tex);
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
	delete itemList[1];
	delete itemList[2];
	delete itemList[3];
	delete itemList[4];
	delete shaderProgram; //Usuniêcie programu cieniuj¹cego
	glDeleteBuffers(1, &bufVertices); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(1, &bufColors); //Usuniêcie VBO z kolorami
	glDeleteBuffers(1, &bufNormals); //Usuniêcie VBO z wektorami normalnymi
	glDeleteBuffers(1, &bufUvs);
}

void world::changeCamera()
{
	float x = (itemList[0]->pos).x - 0.5f;
	float y = (itemList[0]->pos).y - 0.5f;
	cameraTarget = glm::vec3(x, y, 0.0f);
	cameraPos = glm::vec3(x,y-distance, distance);
}

void world::drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów


	if (mode3d) changeCamera();

	V = glm::lookAt( cameraPos, cameraTarget,cameraUp);
	if(!mode3d)drawMap2d(window, V);
	else drawMap3d(window, V);


	if (mode3d)
	{
		for(int i = 0; i<itemList.size(); i++)
		drawObject(itemList[i]->vao, itemList[i]->tex, itemList[i]->shine, itemList[i]->M, itemList[i]->vertexCount);
	}
	else
	{
		for (int i = 0; i<itemList.size(); i++)
		drawObject(itemList[i]->vao, itemList[i]->M, itemList[i]->vertexCount);
	}

	glfwSwapBuffers(window);

	if (mode3d)
	{
		coin->nextFrame();
	}

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
	float x1 = cameraTarget.x;
	float y1 = cameraTarget.y+2.0f;
	float z1 = cameraTarget.z+0.0f;
	float x0 = 0.0f;
	float y0 = 2*float(cMap->h);
	float z0 = -float(cMap->h)/2;
	glUniform4f(shaderProgram->getUniformLocation("Light1"), x1, y1, z1, 1); //œwiat³o wydzielane przez pakmana
	glUniform4f(shaderProgram->getUniformLocation("Light0"), x0, y0, z0, 1); //œwiat³o podstawowe, sta³e dla œwiata
	glUniform1f(shaderProgram->getUniformLocation("shine"), s);
	glUniform1f(shaderProgram->getUniformLocation("alpha"), 0.7f); //udzia³ œwiat³a 0

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
		itemList[0]->changePosition(cMap, coins);
		for (int i = 1; i<itemList.size(); i++)
			itemList[i]->changePosition(cMap, hp);
		for (int i = 0; i<itemList.size(); i++)
			itemList[i]->nextFrame();
	}
}