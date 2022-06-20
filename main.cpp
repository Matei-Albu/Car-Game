#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <thread>

using namespace std;
bool cont = true;
int h = 0;
int m = 0;
int s = 0;



void timers()
{
    //timer
    for(;;)
    {
        if (s == 60)
        {
            m++;
            s = 0;
        }
        if (m == 60)
        {
            h++;
            m = 0;
        }

        system("cls");
        cout<<h<<":"<<m<<":"<<s++;
        Sleep(1000);

        if (cont == false)
        {
            break;
        }
    }
}

void program()
{
    // game windo
    sf::RenderWindow app(sf::VideoMode(405,645), "SFML window");
    app.setFramerateLimit(60);

    //load font
    sf::Font myfont;
    myfont.loadFromFile("SuperMario256.ttf");

    //display timer on screen
    sf::Text timer;
    timer.setFont(myfont);
    timer.setPosition(295,275);
    timer.setFillColor(sf::Color(255,255,255));

    //time prompt when lose
    sf::Text yourTime;
    yourTime.setFont(myfont);
    yourTime.setPosition(70,110);
    yourTime.setFillColor(sf::Color(255,255,255));
    yourTime.setString("Your time was");

    // press spacebar message
    sf::Text space;
    space.setFont(myfont);
    space.setPosition(40,500);
    space.setFillColor(sf::Color(255,255,255));
    space.setString("Press spacebar to \n        start");

    //load car
    sf:: Texture car;
    car.loadFromFile("car.png");

    sf::Sprite mustang(car);
    mustang.setOrigin(50, 50);
    mustang.setPosition(210,500);
    mustang.setScale(.2,.2);


    //load white car
    sf::Texture botCar;
    botCar.loadFromFile("whitecar.png");

    //car array
    sf:: Sprite carArray[3];
    for (int i=0; i<3; i++)
    {

        carArray[i].setTexture(botCar);
        carArray[i].setOrigin(50, 50);
        carArray[i].setPosition(i*80 + 78, i*300 + rand()%300);
        carArray[i].setScale(0.45,0.45);

    }

    //background
    sf:: Texture lane;
    lane.loadFromFile("lanes.png");
    sf::Sprite carlane(lane);
    carlane.setPosition(0,-4);
    carlane.scale(1,2);


    //Game loop
    while (app.isOpen())
    {
        //Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            //Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //check key pressed to move car
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mustang.getPosition().y<550)
        {
            mustang.move(0,3);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mustang.getPosition().y>50)
        {
            mustang.move(0,-3);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mustang.getPosition().x<210)
        {
            mustang.move(3,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mustang.getPosition().x>65)
        {
            mustang.move(-3,0);
        }

        //update timer
        timer.setString(std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s));

        //random car array position
        for (int i = 0; i < 3; i++ )
        {

            carArray[i].move(0, -(rand()%2-5));

            if (carArray[i].getPosition().y> 700)
            {
                carArray[i].setPosition(i*73 + 77, rand()%150-400);
            }


            //check to see if cars colide
            if(carArray[i].getGlobalBounds().intersects(mustang.getGlobalBounds()))
            {
                cont = false;
            }
        }

        app.clear();

        //if cars don't hit, game continues
        if (cont != false)
        {
            app.draw(carlane);
            app.draw(mustang);
            app.draw(timer);
            for (int i = 0; i < 3; i++ )
            {
                app.draw(carArray[i]);
            }
        }

        //if cars hit, game stops
        else
        {
            timer.setPosition(165,150);
            app.draw(timer);
            app.draw(yourTime);
            app.draw(space);
            app.draw(mustang);
            mustang.setPosition(190,275);

            // check spacebar hit for replayability
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                //reset everything
                h = 0;
                m = 0;
                s = 0;
                cont = true;
                timer.setPosition(295,275);
                mustang.setPosition(210,500);

                for (int i=0; i<3; i++)
                {
                    carArray[i].setPosition(i*80 + 78, i*300 + rand()%300);
                }
            }
        }

        app.display();

    }
}


int main()
{

    srand(time(NULL));


    if (cont != false)
    {
        thread th1(timers);
        thread th2(program);

        th1.join();
        th2.join();

    }

}
