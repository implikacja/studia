#include "config.h"



config::config()
{

	mode3d = true;

	glfwSetErrorCallback(config::error_callback);//Zarejestruj procedur� obs�ugi b��d�w

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL. 

	if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
	{
		fprintf(stderr, "Nie mo�na utworzy� okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
	glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
		exit(EXIT_FAILURE);
	}


	//************Tutaj umieszczaj kod, kt�ry nale�y wykona� raz, na pocz�tku programu************
	glClearColor(0, 0, 0, 1); //Czy�� ekran na czarno	
	glEnable(GL_DEPTH_TEST); //W��cz u�ywanie Z-Bufora
	glfwSetKeyCallback(window, config::key_callback); //Zarejestruj procedur� obs�ugi klawiatury


	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniuj�cy 
	cube c;


																		   //*****Przygotowanie do rysowania pojedynczego obiektu*******
																		//Zbuduj VBO z danymi obiektu do narysowania
	//Trojkat na razie tak oszukuj�
	/*float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f,  0.5f, 0.0f, 1.0f,
	};*/

	//bufVertices[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobi� wszystkie obiekty :(
	bufVertices2d[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobi� wszystkie obiekty :(

																		//Zbuduj VAO wi���cy atrybuty z konkretnymi VBO
	glGenVertexArrays(5, vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej
	/*
	glBindVertexArray(vao[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices[0], 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors[0], 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals[0], 4); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze

	glBindVertexArray(0); //Dezaktywuj VAO
	*/
	glGenVertexArrays(7, vao2d); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao2d[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices2d[0], 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors2d[0], 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze

	glBindVertexArray(0);

						  //******Koniec przygotowania obiektu************

	//std::vector< glm::vec4 > vertices;
	//std::vector< glm::vec4 > normals; // Won't be used at the moment.
	float* vertices = NULL;
	float* normals = NULL;
	int indeks;
	bool res = loadObj("cube.txt", vertices, normals, &indeks);

	if (res)
	{
		for (int i = 0; i < indeks; i++)
		{
			printf("Wierzcholek %d: %f\t%f\t%f\t%f\n", i, vertices[i*4], vertices[i*4+1], vertices[i*4+2], vertices[i*4+3]);
		}

		for (int i = 0; i < indeks; i++)
		{
			printf("Wierzcholek normalny %d: %f\t%f\t%f\t%f\n", i, normals[i*4], normals[i*4+1], normals[i*4+2], normals[i*4+3]);
		}


		printf("Rozmiar %d", indeks);
		bufVertices[0] = makeBuffer(vertices, indeks, sizeof(float));


		glBindVertexArray(vao[0]); //Uaktywnij nowo utworzony VAO
		assignVBOtoAttribute(shaderProgram, "vertex", bufVertices[0], 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "color", bufVertices[0], 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
		assignVBOtoAttribute(shaderProgram, "normal", bufVertices[0], 4); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze
		glBindVertexArray(0);
		printf("Stworzono buffor3d\n");

	}

}


config::~config()
{
	delete shaderProgram; //Usuni�cie programu cieniuj�cego

	glDeleteVertexArrays(5, vao); //Usuni�cie vao
	glDeleteBuffers(5, bufVertices); //Usuni�cie VBO z wierzcho�kami
	glDeleteBuffers(5, bufColors); //Usuni�cie VBO z kolorami
	glDeleteBuffers(5, bufNormals); //Usuni�cie VBO z wektorami normalnymi
	glDeleteVertexArrays(7, vao2d); //Usuni�cie vao
	glDeleteBuffers(7, bufVertices2d); //Usuni�cie VBO z wierzcho�kami
	glDeleteBuffers(7, bufColors2d); //Usuni�cie VBO z kolorami

	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);

}


//Tworzy bufor VBO z tablicy
GLuint config::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablic� do VBO

	return handle;
}

//Przypisuje bufor VBO do atrybutu 
void config::assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slot�w dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj� by� brane z aktywnego VBO
}

//Procedura obs�ugi b��d�w
void config::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obs�ugi klawiatury
void config::key_callback(GLFWwindow* window, int key,int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {

	}


	if (action == GLFW_RELEASE) {

	}
}

void config::mainloop(world w)
{
	//G��wna p�tla
	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		if (mode3d)
		{
			w.drawScene(window, vao[0], shaderProgram); //Wykonaj procedur� rysuj�c�
		}
		else
		{
			w.drawScene2d(window, vao2d[0], shaderProgram); //Wykonaj procedur� rysuj�c�
		}


		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
	}
}

bool config::loadObj(const char * path, std::vector < glm::vec4 > & out_vertices, std::vector < glm::vec4 > & out_normals)
{
	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<glm::vec4> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Nie po�na otworzy� pliku %s!\n", path);
		return false;
	}

	while (1)
	{

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.0;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec4 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal.w = 1.0;
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6)
			{
				printf("%s: niew�a�ciwy format face w pliku. Sprobuj u�y� innej metody loadObj\n", path);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			printf("%s: niew�a�ciwy format w pliku. Znaleziono symbol inny ni� v, vn, f\n", path);
			return false;
		}

	}



	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec4 vertex = temp_vertices[vertexIndex - 1]; //-1,  bo w .obj wierzcho�ki s� indeksowane od 1
		out_vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec4 normal = temp_normals[normalIndex - 1]; //-1,  bo w .obj wierzcho�ki s� indeksowane od 1
		out_normals.push_back(normal);
	}

	return true;

}

bool config::loadObj(const char * path, float*& out_vertices, float*& out_normals, int* indeks)
{
	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<glm::vec4> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Nie po�na otworzy� pliku %s!\n", path);
		return false;
	}

	while (1)
	{

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.0;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec4 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal.w = 1.0;
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6)
			{
				printf("%s: niew�a�ciwy format face w pliku. Sprobuj u�y� innej metody loadObj\n", path);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			printf("%s: niew�a�ciwy format w pliku. Znaleziono symbol inny ni� v, vn, f\n", path);
			return false;
		}

	}

	*indeks = vertexIndices.size();
	out_vertices = new float[4 * (*indeks)];
	out_normals = new float[4 * (*indeks)];


	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec4 vertex = temp_vertices[vertexIndex - 1]; //-1,  bo w .obj wierzcho�ki s� indeksowane od 1
		out_vertices[i * 4] = vertex.x;
		out_vertices[i * 4 + 1] = vertex.y;
		out_vertices[i * 4 + 2] = vertex.z;
		out_vertices[i * 4 + 3] = vertex.w;
	}


	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec4 normal = temp_normals[normalIndex - 1]; //-1,  bo w .obj wierzcho�ki s� indeksowane od 1
		out_normals[i * 4] = normal.x;
		out_normals[i * 4 + 1] = normal.y;
		out_normals[i * 4 + 2] = normal.z;
		out_normals[i * 4 + 3] = normal.w;
	}

	return true;

}