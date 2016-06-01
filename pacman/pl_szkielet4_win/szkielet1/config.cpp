#include "config.h"



config::config()
{

	mode3d = false;

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

	bufVertices[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobi� wszystkie obiekty :(
	bufVertices2d[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobi� wszystkie obiekty :(

																		//Zbuduj VAO wi���cy atrybuty z konkretnymi VBO
	glGenVertexArrays(5, vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices[0], 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors[0], 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals[0], 4); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze

	glBindVertexArray(0); //Dezaktywuj VAO
	glGenVertexArrays(7, vao2d); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao2d[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices2d[0], 4); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors2d[0], 4); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze

	glBindVertexArray(0);

						  //******Koniec przygotowania obiektu************



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