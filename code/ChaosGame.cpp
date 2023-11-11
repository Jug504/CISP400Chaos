// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/

        sf::Font font;
        if(!font.loadFromFile("/home/ubuntu/Desktop/cisp400/CISP400_SFML/Chapter18/fonts/Roboto-Light.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }

        sf::Text text;
        text.setFont(font);
        text.setString("Click anywhere on the screen to create three vertices of any kind of triangle, then click on another point to begin the pattern");
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        window.display();

        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //Firstpoint
                    }
                    else //Ignore all other clicks
                    {
                        break;
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{   
            //Terminate
			window.close();
		}

        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {   
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            Vector2f currPoint;
            for (int i = 0; i < 5000; i++) {
                int currVertex;
                currVertex = rand() % 3;
                currPoint.x = ( points.at(i).x + vertices.at(currVertex).x ) / 2.0f;
                currPoint.y = ( points.at(i).y + vertices.at(currVertex).y ) / 2.0f;
                points.push_back(currPoint);
            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        
        
        window.clear();
        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(3,3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }
        window.display();
        for(unsigned int j = 0; j < points.size(); j++)
        {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(points[j].x, points[j].y));
            int color = rand() % 5;
            if (color == 0) { rect.setFillColor(Color::Red); }
            else if (color == 1) { rect.setFillColor(Color::Blue); }
            else if (color == 2) { rect.setFillColor(Color::Green); }
            else if (color == 3) { rect.setFillColor(Color::Yellow);}
            else if (color == 4) { rect.setFillColor(Color::White); }
            window.draw(rect);
            window.display();
        }
        for(unsigned int k = 0; k < points.size(); k++)
        {
            RectangleShape rect1(Vector2f(2,2));
            rect1.setPosition(Vector2f(points[k].x, points[k].y));
            rect1.move(Vector2f(0.f, 220.f));
            rect1.setFillColor(Color::White);
            window.draw(rect1);
            window.display();
        }

        
    }
}