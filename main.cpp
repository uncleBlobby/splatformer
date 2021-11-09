#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

struct entity {
    float positionX;
    float positionY;
};

entity Player;

struct walkFrame {
    int frameID;
    sf::Vector2f headPosition;
    sf::RectangleShape playerHead;
    sf::RectangleShape playerTorso;
    sf::RectangleShape playerLegBack;
    sf::RectangleShape playerLegFront;
};

walkFrame walkFrame0;
walkFrame walkFrame1;
walkFrame walkFrame2;
walkFrame walkFrame3;

walkFrame basic_Walk_Array[4] = {walkFrame0, walkFrame1, walkFrame2, walkFrame3};

walkFrame generateWalkFrame(int frameID, sf::RenderWindow &window, entity &Player);

void drawFrame(walkFrame* basic_Walk_Array, int frameID, sf::RenderWindow &window)
{
    window.draw(basic_Walk_Array[frameID].playerHead);
    window.draw(basic_Walk_Array[frameID].playerTorso);
    window.draw(basic_Walk_Array[frameID].playerLegBack);
    window.draw(basic_Walk_Array[frameID].playerLegFront);
}

void displayWalkAnimationRight(sf::RenderWindow &window, entity &Player)
{
    window.clear(sf::Color::Black);
    //Player.positionX += 18.f;
    generateWalkFrame(0, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += 18.f;
    generateWalkFrame(1, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += 18.f;
    generateWalkFrame(2, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += 18.f;
    generateWalkFrame(3, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));

}

void displayWalkAnimationLeft(sf::RenderWindow &window, entity &Player)
{
    window.clear(sf::Color::Black);
    //Player.positionX += -18.f;
    generateWalkFrame(0, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += -18.f;
    generateWalkFrame(1, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += -18.f;
    generateWalkFrame(2, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));
    window.clear(sf::Color::Black);
    Player.positionX += -18.f;
    generateWalkFrame(3, window, Player);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(175));

}

void displayStaticCharacterPosition(sf::RenderWindow &window, entity &Player)
{
    window.clear(sf::Color::Black);
    generateWalkFrame(0, window, Player);
    window.display(); 
}

void drawFloor(sf::RenderWindow &window){

    float floorHeight = 570.f;

    sf::RectangleShape floor(sf::Vector2f(1600.f, 5.f));
    floor.setPosition(0.f, floorHeight);
    floor.setFillColor(sf::Color::White);
    window.draw(floor);
}


entity& player = Player;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Splatformer V0.0.1");

    Player.positionX = 800.f;
    Player.positionY = 450.f;

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            cout << "moving left" << endl;
            cout << "Player.positionX = " << Player.positionX << endl;
            displayWalkAnimationRight(window, Player);
            Player.positionY += 5;
            //player.positionX += 18.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            cout << "moving left" << endl;
            cout << "Player.positionX = " << Player.positionX << endl;
            displayWalkAnimationLeft(window, Player);
            Player.positionY += 5;
            //player.positionX -= 18.f;
        }


    displayStaticCharacterPosition(window, Player);

    }

    
    
    return 0;
}


walkFrame generateWalkFrame(int frameID, sf::RenderWindow &window, entity &Player)
{   
    walkFrame newFrame;
    if(frameID == 0)
    {
        newFrame.frameID = 0;
        //draw frame 0 head - stock position
        sf::RectangleShape playerHead(sf::Vector2f(25.f, 25.f));
        playerHead.setPosition(Player.positionX, player.positionY);
        newFrame.playerHead = playerHead;
        //window.draw(playerHead);
        
        // set player position based on head position   
        Player.positionX = playerHead.getPosition().x;
        Player.positionY = playerHead.getPosition().y;

        //draw frame 0 torso - stock position
        sf::RectangleShape playerTorso(sf::Vector2f(13.f, 50.f));
        playerTorso.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        newFrame.playerTorso = playerTorso;
        //window.draw(playerTorso);
        
        //draw frame 0 back arm - stock position
        sf::RectangleShape playerArmBack(sf::Vector2f(13.f, 30.f));
        playerArmBack.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmBack.setFillColor(sf::Color::Red);
        //newFrame.playerArmback = playerArmBack;
        //window.draw(playerArmBack);

        //draw frame 0 front arm - stock position
        sf::RectangleShape playerArmFront(sf::Vector2f(13.f, 30.f));
        playerArmFront.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmFront.setFillColor(sf::Color::Blue);
        //newFrame.playerArmFront = playerArmFront;
        //window.draw(playerArmFront);

        //draw frame 0 back leg - stock position
        sf::RectangleShape playerLegBack(sf::Vector2f(13.f, 50.f));
        playerLegBack.setFillColor(sf::Color::Magenta);
        playerLegBack.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        //playerLegBack.rotate(45.f);
        newFrame.playerLegBack = playerLegBack;
        //window.draw(playerLegBack);

        //draw frame 0 front leg - stock position
        sf::RectangleShape playerLegFront(sf::Vector2f(13.f, 50.f));
        playerLegFront.setFillColor(sf::Color::Cyan);
        playerLegFront.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        newFrame.playerLegFront = playerLegFront;

        window.draw(playerArmBack);
        window.draw(playerLegBack);
        window.draw(playerTorso);
        window.draw(playerHead);
        window.draw(playerLegFront);
        window.draw(playerArmFront);        

    }
    if(frameID == 1)
    {
        newFrame.frameID = 0;
        //draw frame 0 head - stock position
        sf::RectangleShape playerHead(sf::Vector2f(25.f, 25.f));
        playerHead.setPosition(Player.positionX, player.positionY - 5);
        newFrame.playerHead = playerHead;
        //window.draw(playerHead);

        // set player position based on head position   
        Player.positionX = playerHead.getPosition().x;
        Player.positionY = playerHead.getPosition().y;
        
        //draw frame 0 torso - stock position
        sf::RectangleShape playerTorso(sf::Vector2f(13.f, 50.f));
        playerTorso.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y - 7.f);
        newFrame.playerTorso = playerTorso;
        //window.draw(playerTorso);

        //draw frame 0 back arm - stock position
        sf::RectangleShape playerArmBack(sf::Vector2f(13.f, 30.f));
        playerArmBack.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y + 7);
        playerArmBack.setFillColor(sf::Color::Red);
        playerArmBack.rotate(-45.f);
        //newFrame.playerArmback = playerArmBack;
        //window.draw(playerArmBack);
        
        //draw frame 0 front arm - stock position
        sf::RectangleShape playerArmFront(sf::Vector2f(13.f, 30.f));
        playerArmFront.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmFront.setFillColor(sf::Color::Blue);
        playerArmFront.rotate(45.f);
        //newFrame.playerArmFront = playerArmFront;
        //window.draw(playerArmFront);

        //draw frame 0 back leg - stock position
        sf::RectangleShape playerLegBack(sf::Vector2f(13.f, 50.f));
        playerLegBack.setFillColor(sf::Color::Magenta);
        playerLegBack.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        playerLegBack.rotate(45.f);
        newFrame.playerLegBack = playerLegBack;
        //window.draw(playerLegBack);

        //draw frame 0 front leg - stock position
        sf::RectangleShape playerLegFront(sf::Vector2f(13.f, 50.f));
        playerLegFront.setFillColor(sf::Color::Cyan);
        playerLegFront.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y + 7);
        playerLegFront.rotate(-45.f);
        newFrame.playerLegFront = playerLegFront;
        //window.draw(playerLegFront);

        window.draw(playerArmBack);
        window.draw(playerLegBack);
        window.draw(playerTorso);
        window.draw(playerHead);
        window.draw(playerLegFront);
        window.draw(playerArmFront);
    }
    if(frameID == 2)
    {
        newFrame.frameID = 0;
        //draw frame 0 head - stock position
        sf::RectangleShape playerHead(sf::Vector2f(25.f, 25.f));
        playerHead.setPosition(Player.positionX, player.positionY + 5 );
        newFrame.playerHead = playerHead;
        //window.draw(playerHead);

        // set player position based on head position   
        Player.positionX = playerHead.getPosition().x;
        Player.positionY = playerHead.getPosition().y;

        
        //draw frame 0 torso - stock position
        sf::RectangleShape playerTorso(sf::Vector2f(13.f, 50.f));
        playerTorso.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        newFrame.playerTorso = playerTorso;
        //window.draw(playerTorso);

        //draw frame 0 back arm - stock position
        sf::RectangleShape playerArmBack(sf::Vector2f(13.f, 30.f));
        playerArmBack.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmBack.setFillColor(sf::Color::Red);
        //newFrame.playerArmback = playerArmBack;
        //window.draw(playerArmBack);

        //draw frame 0 front arm - stock position
        sf::RectangleShape playerArmFront(sf::Vector2f(13.f, 30.f));
        playerArmFront.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmFront.setFillColor(sf::Color::Blue);
        //newFrame.playerArmFront = playerArmFront;
        //window.draw(playerArmFront);
        
        //draw frame 0 back leg - stock position
        sf::RectangleShape playerLegBack(sf::Vector2f(13.f, 50.f));
        playerLegBack.setFillColor(sf::Color::Magenta);
        playerLegBack.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        //playerLegBack.rotate(45.f);
        newFrame.playerLegBack = playerLegBack;
        //window.draw(playerLegBack);

        //draw frame 0 front leg - stock position
        sf::RectangleShape playerLegFront(sf::Vector2f(13.f, 50.f));
        playerLegFront.setFillColor(sf::Color::Cyan);
        playerLegFront.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        newFrame.playerLegFront = playerLegFront;
        //window.draw(playerLegFront);

        window.draw(playerArmBack);
        window.draw(playerLegBack);
        window.draw(playerTorso);
        window.draw(playerHead);
        window.draw(playerLegFront);
        window.draw(playerArmFront);
    }
    if(frameID == 3)
    {
        newFrame.frameID = 0;
        //draw frame 0 head - stock position
        sf::RectangleShape playerHead(sf::Vector2f(25.f, 25.f));
        playerHead.setPosition(Player.positionX, player.positionY - 5);
        newFrame.playerHead = playerHead;
        //window.draw(playerHead);

        // set player position based on head position   
        Player.positionX = playerHead.getPosition().x;
        Player.positionY = playerHead.getPosition().y;

        
        //draw frame 0 torso - stock position
        sf::RectangleShape playerTorso(sf::Vector2f(13.f, 50.f));
        playerTorso.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y - 7.f);
        newFrame.playerTorso = playerTorso;
        //window.draw(playerTorso);

        //draw frame 0 back arm - stock position
        sf::RectangleShape playerArmBack(sf::Vector2f(13.f, 30.f));
        playerArmBack.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y);
        playerArmBack.setFillColor(sf::Color::Red);
        playerArmBack.rotate(45.f);
        //newFrame.playerArmback = playerArmBack;
        //window.draw(playerArmBack);

        //draw frame 0 front arm - stock position
        sf::RectangleShape playerArmFront(sf::Vector2f(13.f, 30.f));
        playerArmFront.setPosition(playerHead.getPosition().x + (playerHead.getSize().x / 4), playerHead.getPosition().y + playerHead.getSize().y + 7);
        playerArmFront.setFillColor(sf::Color::Blue);
        playerArmFront.rotate(-45.f);
        //newFrame.playerArmFront = playerArmFront;
        //window.draw(playerArmFront);
        
        //draw frame 0 back leg - stock position
        sf::RectangleShape playerLegBack(sf::Vector2f(13.f, 50.f));
        playerLegBack.setFillColor(sf::Color::Magenta);
        playerLegBack.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y + 7);
        playerLegBack.rotate(-45.f);
        newFrame.playerLegBack = playerLegBack;
        //window.draw(playerLegBack);

        //draw frame 0 front leg - stock position
        sf::RectangleShape playerLegFront(sf::Vector2f(13.f, 50.f));
        playerLegFront.setFillColor(sf::Color::Cyan);
        playerLegFront.setPosition(playerTorso.getPosition().x, playerTorso.getPosition().y + playerTorso.getSize().y);
        playerLegFront.rotate(45.f);
        newFrame.playerLegFront = playerLegFront;
        //window.draw(playerLegFront);

        window.draw(playerArmBack);
        window.draw(playerLegBack);
        window.draw(playerTorso);
        window.draw(playerHead);
        window.draw(playerLegFront);
        window.draw(playerArmFront);
    }
    drawFloor(window);
    return newFrame;
}
