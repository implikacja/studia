/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

const float PI = 3.141592653589793f;

const int PACMAN_SPEED = 20;
const int GHOST_SPEED = 25;
const int COIN_SPEED = 5000;

const float PACMAN_SHINE = 500;
const float GHOST_SHINE = 500;
const float COIN_SHINE = 10;
const float FLOOR_SHINE = 300;
const float WALL_SHINE = 400;

const float ALPHA = 0.3f; //udzia³ œwiat³a g³ównego w oœwietleniu sceny
const float CAMERA = 5.0f; //odleg³oœæ kamery od pacmana w osi y i z

#endif
