#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


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

int main(int argc, char** argv){
    // Create a window with a framerate limit. It's possible to get a fullscreen mode through sf::VideoMode::getFullscreenModes().
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hackathon game");
    window.setFramerateLimit(60);

    // Buffer some assets; a texture for sprites, and a soundbuffer for sounds
    sf::Texture greenTex;
    greenTex.loadFromFile(ASSETS "/textures/green.png");
    sf::SoundBuffer boingSound;
    boingSound.loadFromFile(ASSETS "/audio/boing.ogg");

    // Create a sprite using the texture, and put it in the middle of the window to start.
    sf::Sprite green(greenTex);
    green.setPosition(window.getView().getCenter());
    
    // Create a sound effect using the soundbuffer.
    sf::Sound boing(boingSound);
    
    
    // Main loop, run as long as the window is open. The framerate limit makes sure it doesn't run too fast.
    while(window.isOpen()) {
        // Either check keyboard (similar for mouse) status directly like this, or use events: https://www.sfml-dev.org/documentation/2.6.2/classsf_1_1Event.php 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            // Escape was pressed, so close the window.
            window.close();
        }
        // Move the sprite around.
        arrowMovement(green);

        // Play the sound effect when pressing space (unless it's already playing).
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && boing.getStatus() != sf::Sound::Playing) {
            boing.play();
        }
        // Clear the window, draw new things, then display the window. Everything you draw to the window should be between clear() and display().
        window.clear();
        window.draw(green);
        window.display();
    }
    return 0;
}
