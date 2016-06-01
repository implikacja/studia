#include "config.h"



config::config()
{

	mode3d = false;

	glfwSetErrorCallback(config::error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL. 

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


	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniuj¹cy 
	cube c;


																		   //*****Przygotowanie do rysowania pojedynczego obiektu*******
																		//Zbuduj VBO z danymi obiektu do narysowania
	//Trojkat na razie tak oszukujê
	/*float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f,  0.5f, 0.0f, 1.0f,
	};*/

	bufVertices[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobiæ wszystkie obiekty :(
	bufVertices2d[0] = makeBuffer(c.vertices, c.vertexCount, sizeof(float) * 4); //Tu musimy zrobiæ wszystkie obiekty :(

																		//Zbuduj VAO wi¹¿¹cy atrybuty z konkretnymi VBO
	glGenVertexArrays(5, vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices[0], 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors[0], 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals[0], 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze

	glBindVertexArray(0); //Dezaktywuj VAO
	glGenVertexArrays(7, vao2d); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao2d[0]); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices2d[0], 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors2d[0], 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze

	glBindVertexArray(0);

						  //******Koniec przygotowania obiektu************



}


config::~config()
{
	delete shaderProgram; //Usuniêcie programu cieniuj¹cego

	glDeleteVertexArrays(5, vao); //Usuniêcie vao
	glDeleteBuffers(5, bufVertices); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(5, bufColors); //Usuniêcie VBO z kolorami
	glDeleteBuffers(5, bufNormals); //Usuniêcie VBO z wektorami normalnymi
	glDeleteVertexArrays(7, vao2d); //Usuniêcie vao
	glDeleteBuffers(7, bufVertices2d); //Usuniêcie VBO z wierzcho³kami
	glDeleteBuffers(7, bufColors2d); //Usuniêcie VBO z kolorami

	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);

}


//Tworzy bufor VBO z tablicy
GLuint config::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który bêdzie zawiera³ tablicê danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicê do VBO

	return handle;
}

//Przypisuje bufor VBO do atrybutu 
void config::assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}

//Procedura obs³ugi b³êdów
void config::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obs³ugi klawiatury
void config::key_callback(GLFWwindow* window, int key,int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {

	}


	if (action == GLFW_RELEASE) {

	}
}

void config::mainloop(world w)
{
	//G³ówna pêtla
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		if (mode3d)
		{
			w.drawScene(window, vao[0], shaderProgram); //Wykonaj procedurê rysuj¹c¹
		}
		else
		{
			w.drawScene2d(window, vao2d[0], shaderProgram); //Wykonaj procedurê rysuj¹c¹
		}


		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}
}