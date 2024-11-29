#include <iostream>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void arrowMovement(sf::Transformable& entity) {
    using sf::Keyboard;
    if(Keyboard::isKeyPressed(Keyboard::Up)) {
        entity.move(0, -1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Down)) {
        entity.move(0, 1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Left)) {
        entity.move(-1, 0);
    }
    if(Keyboard::isKeyPressed(Keyboard::Right)) {
        entity.move(1, 0);
    }
}

static sf::Font starWarsFont;
static sf::Text starWarsText;
static float starWarsTextSpeed = 1.0f;
static void InitIntro()
{
    if (!starWarsFont.loadFromFile(ASSETS "/fonts/Starjedi.ttf"))
    {
        return;
    }

    starWarsText.setFont(starWarsFont);
    starWarsText.setString("Banana\nBanana\nBanana\nBanana");
    starWarsText.setCharacterSize(30); // Initial font size
    starWarsText.setFillColor(sf::Color::Yellow);

    // Center the text horizontally
    sf::FloatRect textBounds = starWarsText.getLocalBounds();
    starWarsText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    starWarsText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT);
}

static void UpdateIntro(float dt)
{
    auto pos = starWarsText.getPosition();
    starWarsText.setPosition(pos + sf::Vector2f(0, -1)*starWarsTextSpeed);
}

int main(int argc, char** argv){
    // Create a window with a framerate limit. It's possible to get a fullscreen mode through sf::VideoMode::getFullscreenModes().
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hackathon game");
    window.setFramerateLimit(60);

    // Variables for animation
    float scrollSpeed = 50.0f; // Pixels per second
    float perspectiveFactor = 1.0f; // Perspective scaling
    float skewAngle = 10.0f; // Angle to skew text

    sf::Clock clock;

    InitIntro();
    // Main loop, run as long as the window is open. The framerate limit makes sure it doesn't run too fast.
    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        // Either check keyboard (similar for mouse) status directly like this, or use events: https://www.sfml-dev.org/documentation/2.6.2/classsf_1_1Event.php
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            // Escape was pressed, so close the window.
            window.close();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        UpdateIntro(elapsed.asSeconds());

        // Clear the window, draw new things, then display the window. Everything you draw to the window should be between clear() and display().
        window.clear();
        window.draw(starWarsText);
        window.display();
    }
    return 0;
}
