#include "config.h"
#include "lodepng.h"

config* config::instance=NULL;
bool config::instanceFlag = false;
char config::c = NULL;
float config::width = 1.0f;
int config::end = 0;
float config::cam = CAMERA;
config::config()
{
	//mode3d = false;
	mode3d = true;

	glfwSetErrorCallback(config::error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 800, "Pacman", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL. 

	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
		exit(EXIT_FAILURE);
	}


	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	glClearColor(0, 0, 0, 1); //Czyœæ ekran na czarno	
	glEnable(GL_DEPTH_TEST); //W³¹cz u¿ywanie Z-Bufora
	glfwSetKeyCallback(window, config::key_callback); //Zarejestruj procedurê obs³ugi klawiatury

	w2d = new world(false);
	w3d = new world(true);

						  //******Koniec przygotowania obiektu************

	//scale = 2.0f/w2d->cMap->h;
	
}

config::~config()
{


	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);

}




//Procedura obs³ugi b³êdów
void config::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obs³ugi klawiatury
void config::key_callback(GLFWwindow* window, int key,int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) config::c = 'l';
		if (key == GLFW_KEY_RIGHT) config::c = 'r';
		if (key == GLFW_KEY_UP) config::c = 'u';
		if (key == GLFW_KEY_DOWN) config::c = 'd';
		if (key == GLFW_KEY_Q) if (config::cam < 15.0f) cam += 0.1f;
		if (key == GLFW_KEY_A) if (config::cam > 2.0f) cam -= 0.1f;

	}
	if (action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_Q) if (config::cam < 15.0f) cam += 0.1f;
		if (key == GLFW_KEY_A) if (config::cam > 2.0f) cam -= 0.1f;
	}


}


void config::mainloop()
{
	//G³ówna pêtla
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		if (mode3d)
		{
			w3d->drawScene(window); //Wykonaj procedurê rysuj¹c¹
			w3d->logic();
		}
		else
		{
			w2d->drawScene(window); //Wykonaj procedurê rysuj¹c¹
			w2d->logic();
		}


		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}
}

bool config::loadObj(const char * path, std::vector < glm::vec4 > & out_vertices, std::vector < glm::vec4 > & out_normals)
{
	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<glm::vec4> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Nie po¿na otworzyæ pliku %s!\n", path);
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
				printf("%s: niew³aœciwy format face w pliku. Sprobuj u¿yæ innej metody loadObj\n", path);
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
			printf("%s: niew³aœciwy format w pliku. Znaleziono symbol inny ni¿ v, vn, f\n", path);
			return false;
		}

	}



	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec4 vertex = temp_vertices[vertexIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec4 normal = temp_normals[normalIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
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
		printf("Nie po¿na otworzyæ pliku %s!\n", path);
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
				printf("%s: niew³aœciwy format face w pliku. Sprobuj u¿yæ innej metody loadObj\n", path);
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
			printf("%s: niew³aœciwy format w pliku. Znaleziono symbol inny ni¿ v, vn, f\n", path);
			return false;
		}

	}

	*indeks = vertexIndices.size();
	out_vertices = new float[4 * (*indeks)];
	out_normals = new float[4 * (*indeks)];


	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec4 vertex = temp_vertices[vertexIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_vertices[i * 4] = vertex.x;
		out_vertices[i * 4 + 1] = vertex.y;
		out_vertices[i * 4 + 2] = vertex.z;
		out_vertices[i * 4 + 3] = vertex.w;
	}


	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec4 normal = temp_normals[normalIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_normals[i * 4] = normal.x;
		out_normals[i * 4 + 1] = normal.y;
		out_normals[i * 4 + 2] = normal.z;
		out_normals[i * 4 + 3] = normal.w;
	}

	return true;

}

bool config::loadObj(const char * path, float *& out_vertices, float*& out_uvs, float *& out_normals, int* indeks)
{
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<glm::vec4> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Nie po¿na otworzyæ pliku %s!\n", path);
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
			//printf("vertex:\t%f\t%f\t%f\t%f\n", vertex.x,vertex.y,vertex.z,vertex.w);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
			//printf("uv:\t%f\t%f\n", uv.x, uv.y);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec4 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal.w = 1.0;
			temp_normals.push_back(normal);
			//printf("normal:\t%f\t%f\t%f\t%f\n", normal.x, normal.y, normal.z, normal.w);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3], uvIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("%s: niew³aœciwy format face w pliku. Sprobuj u¿yæ innej metody loadObj\n", path);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			//for (int k = 0; k < 3; k++) printf("f%d:\t[%d][%d][%d]\n", k, vertexIndex[k], uvIndex[k], normalIndex[k]);
			//printf("\n");

		}
		else
		{
			printf("%s: niew³aœciwy format w pliku. Znaleziono symbol inny ni¿ v, vt, vn, f\n", path);
			return false;
		}

	}

	fclose(file);


	*indeks = vertexIndices.size();
	out_vertices = new float[4 * (*indeks)];
	out_normals = new float[4 * (*indeks)];
	out_uvs = new float[2 * (*indeks)];


	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec4 vertex = temp_vertices[vertexIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_vertices[i * 4] = vertex.x;
		out_vertices[i * 4 + 1] = vertex.y;
		out_vertices[i * 4 + 2] = vertex.z;
		out_vertices[i * 4 + 3] = vertex.w;
		//printf("vertex:\t%f\t%f\t%f\t%f\n", vertex.x, vertex.y, vertex.z, vertex.w);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec4 normal = temp_normals[normalIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_normals[i * 4] = normal.x;
		out_normals[i * 4 + 1] = normal.y;
		out_normals[i * 4 + 2] = normal.z;
		out_normals[i * 4 + 3] = normal.w;
		//printf("normal:\t%f\t%f\t%f\t%f\n", normal.x, normal.y, normal.z, normal.w);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1]; //-1,  bo w .obj wierzcho³ki s¹ indeksowane od 1
		out_uvs[i * 2] = uv.x;
		out_uvs[i * 2 + 1] = uv.y;
		//printf("uv:\t%f\t%f\n", uv.x, uv.y);
	}

	return true;

}

GLuint config::loadTexture(const char* path)
{
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, path);

	//Import do pamiêci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
									   //Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}