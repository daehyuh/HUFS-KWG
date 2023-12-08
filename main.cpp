#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
using namespace sf;

// 전역변수
int maxBoo = 4;
int studyLevel = 0;
int doubleLevel = 0;
int fastLevel = 0;

int status = 0;

sf::Font font;

sf::Texture texture;
sf::Texture testTexture;


sf::Texture texture2;
sf::Texture testTexture2;

sf::Texture texture3;
sf::Texture testTexture3;

sf::Texture texture4;
sf::Texture testTexture4;

class Boo{
    public:
        int uid;
        int level;
        int money;
        int power;
        int posX;
        int posY;
        
        Sprite sprite;

        Text text;
        

        Boo(int uid, int level, int power, int posX, int posY, int money, Font &font){
            this->uid = uid;
            this->level = level;
            this->power = power;
            this->posX = posX;
            this->posY = posY;
            this->money = money;
            cout<<this->uid << this->level <<endl;

            if (this->level <= 4) {
                this->sprite.setTexture(texture);
                text.setString("undergraduate"+to_string(this->level));
            } else if (this->level <= 6){
                this->sprite.setTexture(texture2);
                text.setString("master"+to_string(this->level-4));
            } else if (this->level <= 8){
                this->sprite.setTexture(texture3);
                text.setString("doctor"+to_string(this->level-6));
            } else {
                this->sprite.setTexture(texture4);
                text.setString("professor"+to_string(this->level-8));
            }
            
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(Color::White);
            text.setOutlineThickness(2);
            text.setPosition(this->posX+25, this->posY-25);
            this->sprite.setPosition(this->posX, this->posY);
            this->sprite.setScale(0.5, 0.5);

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
            this->text.setPosition(this->posX+25, this->posY-25);
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

        void checkPosition(){
            if (this->sprite.getPosition().x < 0) {
                this->sprite.setPosition(0, this->sprite.getPosition().y);
            }
            if (this->sprite.getPosition().x > 900) {
                this->sprite.setPosition(900, this->sprite.getPosition().y);
            }
            //y축
            if (this->sprite.getPosition().y < 80) {
                this->sprite.setPosition(this->sprite.getPosition().x, 80);
            }
            if (this->sprite.getPosition().y > 550) {
                this->sprite.setPosition(this->sprite.getPosition().x, 550);
            }
            this->text.setPosition(this->sprite.getPosition().x+25, this->sprite.getPosition().y-25);
        }    
        
};


int main(){
if (!font.loadFromFile("./arial.ttf")) { 
return 42; // Robust error handling!
}

//게임창 크기
int nX = 1000;
int nY = 800;

// uuid
int uid = 0;
//랜덤함수
srand(time(NULL));
// 돈, 시간
long long money = 0;
int time_passed = 0;
time_t time_start, time_end;
time(&time_start);

//STML 일정시간만 보여지는 알림 메세지
sf::Clock clock;
sf::Time elapsed = clock.getElapsedTime();
sf::Time timeToDisplay = sf::seconds(3.0f);

//타이틀
RenderWindow window(VideoMode(nX, nY), "Boo Grow Game", sf::Style::Titlebar | sf::Style::Close);
window.setFramerateLimit(240);


//텍스쳐 관리
//학부생
texture.loadFromFile("./image/boo.png");
texture.setSmooth(true);
//대학원생
texture2.loadFromFile("./image/boo2.png");
texture2.setSmooth(true);
//박사생
texture3.loadFromFile("./image/boo3.png");
texture3.setSmooth(true);
//교수
texture4.loadFromFile("./image/boo4.png");
texture4.setSmooth(true);

//상단바
sf::RectangleShape topbar(sf::Vector2f(1000.0f, 100.0f));
    topbar.setFillColor(sf::Color(236, 150, 68));
    topbar.setPosition(0.0f, 0.0f);
//하단바
sf::RectangleShape bottombar(sf::Vector2f(1000.0f, 100.0f));
    bottombar.setFillColor(sf::Color(236, 150, 68));
    bottombar.setPosition(0.0f, 700.0f);
// 배경
sf::Texture bg;
bg.loadFromFile("./image/bg2.png");
sf::Sprite background(bg);
background.setScale(0.3, 0.3);
background.setPosition(0, 80);

sf::Texture bg2;
bg2.loadFromFile("./image/bg2.png");
sf::Sprite background2(bg2);
background2.setScale(3, 3);
background2.setPosition(0, 80);


// 입학하기 버튼
 sf::RectangleShape button(sf::Vector2f(200.0f, 50.0f));
    button.setFillColor(sf::Color::Green);
    button.setPosition(0.0f, 700.0f);
// 입학하기 텍스트
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Fresh man +1");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(Color::White);
    buttonText.setOutlineThickness(2);
    buttonText.setPosition(25, 710);
// 증원하기 버튼
    sf::RectangleShape button2(sf::Vector2f(200.0f, 50.0f));
        button2.setFillColor(sf::Color::Red);
        button2.setPosition(200.0f, 700.0f);
// 증원하기 텍스트
    sf::Text button2Text;
    button2Text.setFont(font);
    button2Text.setString("maxBoo Lv."+to_string(maxBoo));
    button2Text.setCharacterSize(20);
    button2Text.setFillColor(Color::White);
    button2Text.setOutlineThickness(2);
    button2Text.setPosition(225, 710);
// 공부하기 버튼
    sf::RectangleShape button3(sf::Vector2f(200.0f, 50.0f));
        button3.setFillColor(sf::Color::Blue);
        button3.setPosition(400.0f, 700.0f);
// 공부하기 텍스트
    sf::Text button3Text;
    button3Text.setFont(font);
    button3Text.setString("studyLevel Lv."+to_string(studyLevel));
    button3Text.setCharacterSize(20);
    button3Text.setFillColor(Color::White);
    button3Text.setOutlineThickness(2);
    button3Text.setPosition(425, 710);

// 이중전공 버튼
    sf::RectangleShape button4(sf::Vector2f(200.0f, 50.0f));
        button4.setFillColor(sf::Color::Yellow);
        button4.setPosition(0.0f, 750.0f);
//이중전공 텍스트
    sf::Text button4Text;
    button4Text.setFont(font);
    button4Text.setString("doubleLevel Lv."+to_string(doubleLevel));
    button4Text.setCharacterSize(20);
    button4Text.setFillColor(Color::White);
    button4Text.setOutlineThickness(2);
    button4Text.setPosition(25, 760);
// 조기졸업 버튼
    sf::RectangleShape button5(sf::Vector2f(200.0f, 50.0f));
        button5.setFillColor(sf::Color::Magenta);
        button5.setPosition(200.0f, 750.0f);
// 조기졸업 텍스트
    sf::Text button5Text;
    button5Text.setFont(font);
    button5Text.setString("fastLevel Lv."+to_string(fastLevel));
    button5Text.setCharacterSize(20);
    button5Text.setFillColor(Color::White);
    button5Text.setOutlineThickness(2);
    button5Text.setPosition(225, 760);
// 시험 버튼
    sf::RectangleShape button6(sf::Vector2f(200.0f, 50.0f));
        button6.setFillColor(sf::Color::Cyan);
        button6.setPosition(400.0f, 750.0f);
// 시험 텍스트
    sf::Text button6Text;
    button6Text.setFont(font);
    button6Text.setString("go to test");
    button6Text.setCharacterSize(20);
    button6Text.setFillColor(Color::White);
    button6Text.setOutlineThickness(2);
    button6Text.setPosition(425, 760);

// 시험 버튼들 1
    sf::RectangleShape button7(sf::Vector2f(200.0f, 50.0f));
        button7.setFillColor(sf::Color::Cyan);
        button7.setPosition(50.0f, 200.0f);
// 시험 버튼들 2
    sf::RectangleShape button8(sf::Vector2f(200.0f, 50.0f));
        button8.setFillColor(sf::Color::Cyan);
        button8.setPosition(300.0f, 200.0f);
// 시험 버튼들 3
    sf::RectangleShape button9(sf::Vector2f(200.0f, 50.0f));
        button9.setFillColor(sf::Color::Cyan);
        button9.setPosition(50.0f, 400.0f);
// 시험 버튼들 4
    sf::RectangleShape button10(sf::Vector2f(200.0f, 50.0f));
        button10.setFillColor(sf::Color::Cyan);
        button10.setPosition(300.0f, 400.0f);

Text text;
text.setFont(font);
text.setString(to_string(money) + " won" + " " + to_string(time_passed) + " sec");
text.setCharacterSize(30);
text.setFillColor(Color::White);
//text 테두리 
text.setOutlineThickness(3);
text.setPosition(0, 0);

// Boo 객체를 생성한다.
vector<Boo> boos;
boos.push_back(Boo(++uid, 1, 25, 100, 100, 2000, font));
boos.push_back(Boo(++uid, 1, 25, 500, 500, 2000, font));

int t = 0;

// 게임루프
while (window.isOpen()){
// 이벤트 검사 및 처리
Event e;
while (window.pollEvent(e)) {
if (e.type == Event::Closed)
window.close();
}

if (status == 0){
// 이동 및 합치기 처리
if (Mouse::isButtonPressed(Mouse::Left)) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); 
    int x = worldPos.x;
    int y = worldPos.y;

    for(int i = 0; i < boos.size(); i++ ){
    if (boos[i].isInside(x, y)) {
        while (Mouse::isButtonPressed(Mouse::Left)) {
        cout << "클릭중" << i<< endl;
        //위치
        //실시간 이동위치
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); 
        int x2 = worldPos.x;
        int y2 = worldPos.y;
        boos[i].move(x2, y2);
        boos[i].checkPosition();
        
                // 합치기 출력 start
                window.clear();
                window.draw(topbar);
                window.draw(background);
                window.draw(bottombar);
                for (Boo boo2 : boos) {
                    if (boo2.uid != boos[i].uid) {
                        window.draw(boo2.sprite);
                        window.draw(boo2.text);
                    }
                }
                window.draw(boos[i].sprite);
                window.draw(boos[i].text);
                window.draw(text);
            
                window.draw(button6);
                window.draw(button6Text);
                window.draw(button);
                window.draw(buttonText);

                window.display();
                // 합치기 출력 end
        }
            for (Boo boo2 : boos) {
                if (boos[i].isCollide(boo2) && boos[i].uid != boo2.uid && boos[i].level == boo2.level) {
                    
                    int level = 0;

                    //조기졸업 확률코드 추가
                    int randNum = rand() % 100;
                    if (boo2.level == 3 &&randNum < 10 * fastLevel) {
                        level = 5;
                    } else {
                        level = boo2.level + 1;
                    }

                    Boo tempBoo(++uid, level, boos[i].power*3, boos[i].posX, boos[i].posY, boos[i].money*2, font);

                    
                    //boo, boo2 삭제
                    boos.erase(std::remove_if(boos.begin(), boos.end(), [&](Boo boo3) { return boo3.uid == boos[i].uid || boo3.uid == boo2.uid; }), boos.end());
                    boos.push_back(tempBoo);

                    
                    goto end;
                }
            }
     }
    }
}
// status end
}

if (e.type == sf::Event::MouseButtonPressed) {
    if (e.mouseButton.button == sf::Mouse::Left && money >= 100) {
        while (Mouse::isButtonPressed(Mouse::Left)) {
            // 땔때까지 대기
        }
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
        if (button.getGlobalBounds().contains(mousePos)) {
            if (boos.size() >= maxBoo) {
                cout << "더이상 추가할 수 없습니다" << endl;
                goto end;
            }

            //화면 밖으로 빠져나오지 않게 범위안에 랜덤 생성
            int randx = rand() % 1000;
            int randy = rand() % 500;
            if (randx > 1000) {
                randx = 900;
            } else if (randx < 100) {
                randx = 100;
            }
            if (randy > 500) {
                randy = 500;
            } else if (randy < 100) {
                randy = 100;
            }
            
            boos.push_back(Boo(++uid, 1, 25, randx, randy, 2000, font));
            
            window.clear();
            window.draw(topbar);
            window.draw(background);
            window.draw(bottombar);
            for (Boo boo2 : boos) {
                window.draw(boo2.sprite);
                window.draw(boo2.text);
            }
            window.display();

            std::cout << "Button Clicked!" << std::endl;
            money -= 100;
        }
        
    else if (button2.getGlobalBounds().contains(mousePos) && money >= 10000) {
        maxBoo += 1;
        money -= 10000;
        button2Text.setString("maxBoo Lv."+to_string(maxBoo));
    } else if (button3.getGlobalBounds().contains(mousePos)) {
        //:todo 강화 가격 증가
        studyLevel += 1;
        button3Text.setString("studyLevel Lv."+to_string(studyLevel));
    } else if (button4.getGlobalBounds().contains(mousePos)) {
        //:todo 이중 가격 증가
        doubleLevel += 1;
        button4Text.setString("doubleLevel Lv."+to_string(doubleLevel));
    } else if (button5.getGlobalBounds().contains(mousePos)) {
        //:todo 조기 가격 증가
        fastLevel += 1;
        button5Text.setString("fastLevel Lv."+to_string(fastLevel));
    } else if (button6.getGlobalBounds().contains(mousePos)) {
        if (status == 0) {
            status = 1;
            button6Text.setString("back");
        } else {
            (status = 0);
            button6Text.setString("goto test");
        }
    } else if (button7.getGlobalBounds().contains(mousePos)) {
        
    } else if (button8.getGlobalBounds().contains(mousePos)) {

    } else if (button9.getGlobalBounds().contains(mousePos)) {

    } else if (button10.getGlobalBounds().contains(mousePos)) {
    } 
    else {
        std::cout << "빈곳을 클릭함" << std::endl;
    }
    }
}

end:;

// must be running
time(&time_end);
for (Boo boo : boos) {
    if (time_passed != time_end - time_start){
        money += (boo.money + (50 * studyLevel)) * (1 + (0.025 * doubleLevel));
    }
}
time_passed = time_end - time_start;
text.setString(to_string(money) + " won" + " " + to_string(time_passed) + " sec " + to_string(boos.size()) + "/" + to_string(maxBoo) + "person");
//

if (status == 0){
window.clear();
window.draw(topbar);
window.draw(background);
window.draw(bottombar);
for (Boo boo : boos) {
    boo.checkPosition();
    window.draw(boo.sprite);
    window.draw(boo.text);
}

window.draw(text);
window.draw(button);
window.draw(buttonText);
window.draw(button6);
window.draw(button6Text);
// 화면을 표시한다. 
window.display();

//status 0 end
} else if (status == 1) {
    window.clear();
    window.draw(topbar);
    window.draw(background);
    window.draw(bottombar);
    window.draw(button6);

    window.draw(text);
    
    window.draw(button2);
    window.draw(button3);
    window.draw(button4);
    window.draw(button5);
    window.draw(button6);
    window.draw(button2Text);
    window.draw(button3Text);
    window.draw(button4Text);
    window.draw(button5Text);
    window.draw(button6Text);

    window.display();
}

}
return 0;
}
//g++ -std=c++11 -fdiagnostics-color=always -g main.cpp  -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics