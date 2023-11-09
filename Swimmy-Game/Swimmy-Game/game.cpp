#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include "player.h"

using namespace sf;

const int WIDTH = 1000;
const int HEIGHT = 700;

enum GameState {  // 게임 상태를 나타내는 열거형
    StartScreen,  // 게임 시작 화면
    InfoScreen,   // 게임 설명 화면
    GameScreen    // 게임 진행 화면
};

int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Swimmy");
    GameState gameState = StartScreen;

    // 게임시작화면 이미지 삽입
    Texture startScreenTexture;
    if (!startScreenTexture.loadFromFile("startScreenImage.png")) {
        return 1;
    }
    Sprite startScreenSprite(startScreenTexture);

    // 게임진행화면 이미지 삽입
    Texture gameScreenTexture;
    if (!gameScreenTexture.loadFromFile("gameScreenImage.png")) {
        return 1;
    }
    Sprite gameScreenSprite(gameScreenTexture);

    // 게임설명화면 이미지 삽입
    Texture infoScreenTexture;
    if (!infoScreenTexture.loadFromFile("infoScreenImage.png")) {
        return 1;
    }
    Sprite infoScreenSprite(infoScreenTexture);

    // Player 이미지 삽입
    Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png")) {
        return 1;
    }
    Player player(playerTexture, 30, 30); // Player 객체 생성
    player.sprite.setScale(0.4f, 0.4f);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) { // 창을 닫으면 종료
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                // 게임시작화면에서 스페이스바를 누름 -> 게임진행화면으로 이동
                if (event.key.code == Keyboard::Space && gameState == StartScreen) {
                    gameState = GameScreen;
                }
                // 게임시작화면에서 A키를 누름 -> 게임설명화면으로 이동
                else if (event.key.code == Keyboard::A && gameState == StartScreen) {
                    gameState = InfoScreen;
                }
                // 게임설명화면에서 스페이스바를 누름 -> 게임진행화면으로 이동
                else if (event.key.code == Keyboard::Space && gameState == InfoScreen) {
                    gameState = GameScreen;
                }
            }
        }

        if (gameState == GameScreen) {
            player.update(Vector2u(WIDTH, HEIGHT));
        }

        window.clear();

        if (gameState == StartScreen) {
            window.draw(startScreenSprite);
        }
        else if (gameState == GameScreen) {
            window.draw(gameScreenSprite);
            window.draw(player.sprite);
        }
        else if (gameState == InfoScreen) {
            window.draw(infoScreenSprite);
        }

        window.display();
    }

    return 0;
}