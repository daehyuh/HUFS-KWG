#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
using namespace sf;


class MyCircle{
    public:
        int uid;
        int level;
        int money;
        int power;
        double radius;
        double diameter;
        double posX;
        double posY;
        double velocity;
        CircleShape circle;
        
        MyCircle(int uid,int level, double radius, double posX, double posY, double velocity){
            this->level = level;
            this->uid = uid;
            this->radius = radius;
            this->diameter = radius * 2;
            this->posX = posX;
            this->posY = posY;
            this->velocity = velocity;
            this->circle = CircleShape(radius);
            this->circle.setPosition(posX, posY);
            
            if (this->level == 1){
                this->circle.setFillColor(Color::Red);
                this->money = 10;
                this->power = 1;
            } else if (this->level == 2) {
                this->circle.setFillColor(Color::Blue);
                this->money = 30;
                this->power = 2;
            } else if (this->level == 3) {
                this->circle.setFillColor(Color::Green);
                this->money = 75;
                this->power = 3;
            } else if (this->level == 4) {
                this->circle.setFillColor(Color::Yellow);
                this->money = 170;
                this->power = 4;
            } else if (this->level == 5) {
                this->circle.setFillColor(Color::Magenta);
                this->money = 280;
                this->power = 5;
            } else if (this->level == 6) {
                this->circle.setFillColor(Color::Cyan);
                this->money = 600;
                this->power = 6;
            } else if (this->level == 7) {
                this->circle.setFillColor(Color::White);
                this->money = 1250;
                this->power = 7;
            } else if (this->level == 8) {
                this->circle.setFillColor(Color::Black);
                this->money = 2500;
                this->power = 8;
            } else if (this->level == 9) {
                this->circle.setFillColor(Color::Red);
                this->money = 5500;
                this->power = 9;
            } else if (this->level == 10) {
                this->circle.setFillColor(Color::Blue);
                this->money = 10000;
                this->power = 10;
            } else if (this->level == 11) {
                this->circle.setFillColor(Color::Green);
                this->money = 25000;
                this->power = 11;
            } else if (this->level == 12) {
                this->circle.setFillColor(Color::Yellow);
                this->money = 50000;
                this->power = 12;
            } else if (this->level == 13) {
                this->circle.setFillColor(Color::Magenta);
                this->money = 100000;
                this->power = 13;
            } else if (this->level == 14) {
                this->circle.setFillColor(Color::Cyan);
                this->money = 140;
                this->power = 14;
            } else if (this->level == 15) {
                this->circle.setFillColor(Color::White);
                this->money = 150;
                this->power = 15;
            } else if (this->level == 16) {
                this->circle.setFillColor(Color::Black);
                this->money = 160;
                this->power = 16;
            } else if (this->level == 17) {
                this->circle.setFillColor(Color::Red);
                this->money = 170;
                this->power = 17;
            }
            
            
            this->circle.setPointCount(radius);
        }
        // 마우스 클릭이 circle 범위 안에 있는지 확인
        bool isInside(int x, int y){
            double distance = sqrt(pow(x - this->circle.getPosition().x-radius, 2) + pow(y - this->circle.getPosition().y-radius, 2));
            if (distance < this->radius) {
                return true;
            }
            return false;
        }
        //해당좌표로 이동하는 함수
        void move(int x, int y){
            this->circle.setPosition(x-this->radius, y-this->radius);
        }
        // 충돌하는지 확인
        bool isCollide(MyCircle circle2){
            double distance = sqrt(pow(this->circle.getPosition().x - circle2.circle.getPosition().x, 2) + pow(this->circle.getPosition().y - circle2.circle.getPosition().y, 2));
            if (distance <= this->radius + circle2.radius) {
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
RenderWindow window(VideoMode(nX, nY), "Moving Ball");
window.setFramerateLimit(100);

// Mycircle 객체를 생성한다.
vector<MyCircle> circles;
circles.push_back(MyCircle(uid,1, 25, 100, 100, 0));
circles.push_back(MyCircle(++uid,1, 25, 500, 500, 0));

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
while (window.isOpen())
{
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
    //마우스 위치
    for (MyCircle circle : circles) {
        if (circle.isInside(x, y)) {
        while (Mouse::isButtonPressed(Mouse::Left)) {
            //위치
            //실시간 이동위치
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); 
            int x = worldPos.x;
            int y = worldPos.y;
            
            // 객체 이동
            circle.move(x, y);
            // 나머지객체
            window.clear();
            for (MyCircle circle2 : circles) {
                // 클래스 비교
                if (circle2.uid != circle.uid) {
                    window.draw(circle2.circle);
                }
            }
            
            window.draw(text);
            window.draw(button);
            window.draw(circle.circle);
            window.display();
            
            // 진급하기
            for (MyCircle circle2 : circles) {
                if (circle.isCollide(circle2) && circle.uid != circle2.uid && circle.level == circle2.level) {
                    //circle.uid circle2.uid 찾아서 pop
                    window.clear();
                    // 삭제코드
                    for (int i = 0; i < circles.size(); i++) {
                        if (circles[i].uid == circle.uid) {
                            circles.erase(circles.begin() + i);
                        }
                    }
                    for (int i = 0; i < circles.size(); i++) {
                        if (circles[i].uid == circle2.uid) {
                            circles.erase(circles.begin() + i);
                        }
                    }
                    // 진급
                    circles.push_back(MyCircle(++uid, circle.level+1, circle.radius, circle.circle.getPosition().x, circle.circle.getPosition().y, 0));
                    // 삭제이후 보여주기
                    for (MyCircle circle2 : circles) {
                        window.draw(circle2.circle);
                    }
                    window.display();

                    cout << "진급"  << endl;
                    goto end;
                }
            }
        }
    }
    }
} else {
window.clear();
for (MyCircle circle : circles) {
window.draw(circle.circle);
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
                        circles.push_back(MyCircle(++uid, 1, 25, randx, randy, 0));
                        for (MyCircle circle2 : circles) {
                            window.draw(circle2.circle);
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
window.clear();

time(&time_end);

for (MyCircle circle : circles) {
    window.draw(circle.circle);
    if (time_passed != time_end - time_start){
        money += circle.money;    
    }
}


time_passed = time_end - time_start;
text.setString(to_string(money) + " won" + " " + to_string(time_passed) + " sec");
window.draw(text);
window.draw(button);
// 화면을 표시한다. 
window.display();
}
}
return 0;
}
//g++ -std=c++11 -fdiagnostics-color=always -g main.cpp  -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics