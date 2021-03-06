/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

const float PI = 3.141592653589793f;

const int PACMAN_SPEED = 20;
const int GHOST_SPEED = 25;
const int COIN_SPEED = 5000;
const int TEXT_SPEED = 13000;

const float PACMAN_SHINE = 500;
const float GHOST_SHINE = 500;
const float COIN_SHINE = 10;
const float FLOOR_SHINE = 300;
const float WALL_SHINE = 400;

const float ALPHA = 0.3f; //udzia� �wiat�a g��wnego w o�wietleniu sceny
const float CAMERA = 5.0f; //odleg�o�� kamery od pacmana w osi y i z

#endif
