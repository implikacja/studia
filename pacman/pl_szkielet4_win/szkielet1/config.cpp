#include "config.h"

config* config::instance=NULL;
bool config::instanceFlag = false;
char config::c = NULL;
float config::width = 1.0f;
int config::end = 0;
config::config()
{
	mode3d = false;


	glfwSetErrorCallback(config::error_callback);//Zarejestruj procedur� obs�ugi b��d�w

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 800, "Pacman", NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL. 

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

	w2d = new world(false);
	w3d = new world(true);

						  //******Koniec przygotowania obiektu************

	//scale = 2.0f/w2d->cMap->h;
	
}

config::~config()
{


	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);

}




//Procedura obs�ugi b��d�w
void config::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obs�ugi klawiatury
void config::key_callback(GLFWwindow* window, int key,int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) config::c = 'l';
		if (key == GLFW_KEY_RIGHT) config::c = 'r';
		if (key == GLFW_KEY_UP) config::c = 'u';
		if (key == GLFW_KEY_DOWN) config::c = 'd';
	}


	if (action == GLFW_RELEASE) {
		//if (key == GLFW_KEY_LEFT) //speed_y = 0;
		//if (key == GLFW_KEY_RIGHT) //speed_y = 0;
		//if (key == GLFW_KEY_UP)
		//if (key == GLFW_KEY_DOWN) //speed_x = 0;
	}
}


void config::mainloop()
{
	//G��wna p�tla
	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		if (mode3d)
		{
			w3d->drawScene(window); //Wykonaj procedur� rysuj�c�
		}
		else
		{
			w2d->drawScene(window); //Wykonaj procedur� rysuj�c�
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