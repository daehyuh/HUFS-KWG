#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
using namespace sf;

sf::Texture texture;

void loadTexture(){
    texture.loadFromFile("./image/image.png");
    texture.setSmooth(true);
}

class Boo{
    public:
        int uid;
        int level;
        int money;
        int power;
        int posX;
        int posY;
        
        Sprite sprite;

        Boo(int uid, int level, int power, int posX, int posY, int money){
            this->uid = uid;
            this->level = level;
            this->power = power;
            this->posX = posX;
            this->posY = posY;
            this->money = money;
            cout<<this->uid << this->level <<endl;
            this->sprite.setTexture(texture);
            this->sprite.setPosition(this->posX, this->posY);
        }
        
        // x y가 sprite 범위 안에 있는지 확인하는 함수
        bool isInside(int x, int y){
            cout << this->sprite.getGlobalBounds().contains(x, y) << endl;
            cout << x << " " << y << endl;
            if (this->sprite.getGlobalBounds().contains(x, y)) {
                return true;
            }
            else {
                return false;
            }
        }

        //해당좌표로 이동하는 함수
        void move(int x, int y){
            this->posX = x;
            this->posY = y;
            this->sprite.setPosition(this->posX, this->posY);
        }
        // 충돌하는지 확인
        bool isCollide(Boo boo){
            if (this->sprite.getGlobalBounds().intersects(boo.sprite.getGlobalBounds())) {
                return true;
            }
            else {
                return false;
            }
        }
};


int main(){
int nX = 1000;
int nY = 1000;
int uid = 0;
RenderWindow window(VideoMode(nX, nY), "Boo Grow Game");
window.setFramerateLimit(100);

texture.loadFromFile("./image/image.png");
texture.setSmooth(true);


// Boo 객체를 생성한다.
vector<Boo> boos;
boos.push_back(Boo(++uid, 1, 25, 100, 100, 2000));
boos.push_back(Boo(++uid, 1, 25, 500, 500, 2000));

// SFML 버튼을 추가한다.
 sf::RectangleShape button(sf::Vector2f(200.0f, 50.0f));
    button.setFillColor(sf::Color::Green);
    button.setPosition(0.0f, 850.0f);

//랜덤함수
srand(time(NULL));

int money = 0;
int time_passed = 0;
time_t time_start, time_end;
Font font;
Text text;

time(&time_start);

text.setFont(font);
text.setString(to_string(money) + " won" + " " + to_string(time_passed) + " sec");
text.setCharacterSize(20);
text.setFillColor(Color::Blue);
text.setPosition(0, 0);

int t = 0;
if (!font.loadFromFile("./arial.ttf")) { 
return 42; // Robust error handling!
}
// 여기서부터 게임 루프
while (window.isOpen()){
    window.clear();
// 이벤트 검사 및 처리
Event e;
while (window.pollEvent(e)) {
if (e.type == Event::Closed)
window.close();
}

if (Mouse::isButtonPressed(Mouse::Left)) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); 
    int x = worldPos.x;
    int y = worldPos.y;
    cout << x << " " << y << endl;
    //마우스 위치
    //boos 반복문


    for (auto boo : boos) {
        cout << "순서" << boo.uid << endl;
        if (boo.isInside(x, y)) {
            while (Mouse::isButtonPressed(Mouse::Left)) {
            //위치
            //실시간 이동위치
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); 
            int x = worldPos.x;
            int y = worldPos.y;
            
            // 객체 이동
            boo.move(x, y);
            
            // 나머지객체 그리기 start
            window.clear();
            for (Boo boo2 : boos) {
                if (boo2.uid != boo.uid) {
                    window.draw(boo2.sprite);
                }
            }
            window.draw(text);
            window.draw(button);
            window.draw(boo.sprite);
            window.display();
            // 나머지객체 그리기 end


            // 진급하기
            for (Boo boo2 : boos) {
                if (boo.isCollide(boo2) && boo.uid != boo2.uid && boo.level == boo2.level) {
                    //boo.uid boo2.uid 찾아서 pop
                    for (int i = 0; i < boos.size(); i++) {
                        if (boos[i].uid == boo.uid) {
                            boos.erase(boos.begin() + i);
                        }
                        if (boos[i].uid == boo2.uid) {
                            boos.erase(boos.begin() + i);
                        }
                    }
                    
                    window.clear();
                    // 삭제이후 보여주기
                    for (Boo boo2 : boos) {
                        window.draw(boo2.sprite);
                    }
                    window.display();
                    
                    boos.push_back(Boo(++uid, 2, 50, boo.posX, boo.posY, 2));
                    cout << "진급"  << endl;
                    goto end;
                }
            }
        }
        }
    }
}

if (e.type == sf::Event::MouseButtonPressed) {
    if (e.mouseButton.button == sf::Mouse::Left && money >= 100) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
        if (button.getGlobalBounds().contains(mousePos)) {
            int randx = rand()% 1000;
            int randy = rand()% 1000;
            if (randx > 500) {
                randx = 500;
            } else if (randx < 200) {
                randx = 200;
            }
            if (randy > 500) {
                randy = 500;
            } else if (randy < 200) {
                randy = 200;
            }
            boos.push_back(Boo(++uid, 1, 25, randx, randy, 2000));
            
            window.clear();
            for (Boo boo2 : boos) {
                window.draw(boo2.sprite);
            }
            window.display();

            std::cout << "Button Clicked!" << std::endl;
            money -= 100;
        } else {
        std::cout << "충분한 돈이 없습니다" << std::endl;
        }
    }
}

end:;
time(&time_end);

window.clear();
for (Boo boo : boos) {
    window.draw(boo.sprite);
    if (time_passed != time_end - time_start){
        money += boo.money;    
    }
}
time_passed = time_end - time_start;
text.setString(to_string(money) + " won" + " " + to_string(time_passed) + " sec");
window.draw(text);
window.draw(button);
// 화면을 표시한다. 
window.display();

}
return 0;
}
//g++ -std=c++11 -fdiagnostics-color=always -g main.cpp  -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics