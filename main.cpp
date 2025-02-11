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
#include <string>

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1350

static std::string actualText = R"(
A long time from now, in the year 2500...





volvo wars
Episode ex
The Autonomous Dilemma





The year is 2500. Decades after parting

ways with their Geely overlords, 

volvo remains steadfast in its quest to master

autonomous driving. in a world dominated

by sentient vehicles and hyper-intelligent

systems, after decades of tinkering and countless

prototype crashes, the iconic automaker faces

a daunting challenge - a roadblock, literally.



Now, volvo's engineers are out of coffee,

out of time, and dangerously close to asking

Tesla for help. Desperate to save their reputation

(and their sanity), they've called on you,

to pretend you're the autonomous system

they couldn't quite finish. volvo's biggest

stakeholder meeting looms on the horizon - 

a gathering of alien investors from the Andromeda

Galaxy, who are very particular about their roi.


Your mission: fake it 'till you make it.

Steer volvo vehicle's through chaotic simulations,

avoid embarrassing explosions, and convince that volvo

is the future of driving - even if it's mostly held

with duct tape and hope.



The simulation starts now... Good luck!
)";

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
static int state = 1;

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
    starWarsText.setString(actualText);
    starWarsText.setCharacterSize(45); // Initial font size
    starWarsText.setFillColor(sf::Color::Yellow);

    // Center the text horizontally
    sf::FloatRect textBounds = starWarsText.getLocalBounds();
    starWarsText.setOrigin(textBounds.width / 2, 0);
    starWarsText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/1.5);
}

static void UpdateIntro(float dt)
{
    auto pos = starWarsText.getPosition();
    starWarsText.setPosition(pos + sf::Vector2f(0, -1)*starWarsTextSpeed);
}

// Buffer some assets; a texture for sprites, and a soundbuffer for sounds
// Create a sprite using the texture, and put it in the middle of the window to start.

// print green position
// sf::Sprite red(redTex);
sf::Sprite red;
sf::Sprite darkGreen;
sf::Sprite green;

// sf::Texture greenTex;
// sf::Texture redTex;
// sf::Texture darkGreenTex;
// sf::SoundBuffer boingSound;

// sf::Sprite darkGreen(darkGreenTex);

// sf::Sprite green(greenTex);
// green.setPosition(0, 0);

// Create a sound effect using the soundbuffer.
// sf::Sound boing(boingSound);

static void Game()
{
    // Game logic here
    // Move the sprite around.
    arrowMovement(green);
    red.move(0, 0.1);
    darkGreen.move(0, 0.1);
    if (red.getPosition().y > 1024) {
        red.setPosition(0, -1026);
    }
    if (darkGreen.getPosition().y > 1024) {
        darkGreen.setPosition(0, -1026);
    }
}

int main(int argc, char** argv){
    sf::Texture greenTex;
    sf::Texture redTex;
    sf::Texture darkGreenTex;
    // sf::SoundBuffer boingSound;
    // Create a window with a framerate limit. It's possible to get a fullscreen mode through sf::VideoMode::getFullscreenModes().
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hackathon game");
    window.setFramerateLimit(60);
    greenTex.loadFromFile(ASSETS "/textures/green.png");
    redTex.loadFromFile(ASSETS "/textures/red.png");
    darkGreenTex.loadFromFile(ASSETS "/textures/darkGreen.png");
    // boingSound.loadFromFile(ASSETS "/audio/boing.ogg");
    red.setTexture(redTex);
    darkGreen.setTexture(darkGreenTex);
    green.setTexture(greenTex);


    green.setPosition(window.getView().getCenter().x, 250);
    darkGreen.setPosition(0, -1026);
    red.setPosition(0, 0);



    sf::Clock clock;

    InitIntro();

    // Main loop, run as long as the window is open. The framerate limit makes sure it doesn't run too fast.
    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        // std::cout<<"hej"<<std::endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // std::cout<<green.getPosition().x<<std::endl;
        window.clear();
        if (state == 0) {
            UpdateIntro(elapsed.asSeconds());
            window.draw(starWarsText);
        }
        else if (state == 1) {
            std::cout<<"hej"<<std::endl;
            Game();
            window.draw(red);
            window.draw(darkGreen);
            window.draw(green);
        }

        // Clear the window, draw new things, then display the window. Everything you draw to the window should be between clear() and display().

        window.display();
    }
    return 0;
}
