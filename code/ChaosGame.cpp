// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;


int main() {
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

     sf::Font font;
    if(!font.loadFromFile("Roboto-Light.ttf")) {
        cout << "Error loading font" << endl;
    }

    sf::Text text("Click anywhere on the screen to create three vertices of any kind of triangle, then click on another point to begin the pattern",font,20);
    text.setFillColor(sf::Color::White);

	while (window.isOpen()) {

        sf::Event event;
		while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
				// Quit the game when the window is closed
				window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << "the left button was pressed" << std::endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    if(vertices.size() < 3) {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

                    }
                    else if(points.size() == 0) {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //Firstpoint
                    }
                    //Ignore all other clicks
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {   
            //Terminate
			window.close();
		}

        if(points.size() > 0) {   
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            Vector2f currPoint;
            for (int i = 0; i < 1000; i++) {
                int currVertex;
                currVertex = rand() % 3;
                currPoint.x = ( points.at(i).x + vertices.at(currVertex).x ) / 2.0f;
                currPoint.y = ( points.at(i).y + vertices.at(currVertex).y ) / 2.0f;
                points.push_back(currPoint);
            }
        }
        
        window.clear();
        window.draw(text);

        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(3,3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        //float aCounter,wCounter,sCounter,dCounter = 0.0;
        for(unsigned int j = 10; j < points.size(); j++) {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(points[j].x, points[j].y));
            int color = j % 5;
            if (color == 0) { rect.setFillColor(Color::Red); }
            else if (color == 1) { rect.setFillColor(Color::Blue); }
            else if (color == 2) { rect.setFillColor(Color::Green); }
            else if (color == 3) { rect.setFillColor(Color::Yellow);}
            else if (color == 4) { rect.setFillColor(Color::White); }
            
            /*if(Keyboard::isKeyPressed(Keyboard::A)) { //Shift fractal to the left 
                aCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x - aCounter, points[j].y));
            }
            if(Keyboard::isKeyPressed(Keyboard::W)) { //shit fractal upwards 
                wCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x, points[j].y - wCounter));
            }
            if(Keyboard::isKeyPressed(Keyboard::S)) { //Shift fractal downwards 
                sCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x,points[j].y + sCounter));
            }
            if(Keyboard::isKeyPressed(Keyboard::D)) { //Shift fractal to the right
                dCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x + dCounter, points[j].y));
            }
            */
            window.draw(rect);
        }

        window.display();
    }
}

/*

int main() {
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

	while (window.isOpen()) {
    
        sf::Font font;
        if(!font.loadFromFile("Roboto-Light.ttf")) {
            cout << "Error loading font" << endl;
        }

        sf::Text text("Click anywhere to create the top left corner of a square. Click again to create the bottom right corner. Click once more to start.",font,20);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        window.display();

        sf::Event event;
		while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << "the left button was pressed" << std::endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    if(vertices.size() < 2) {   //Top left, bottom right
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0) {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //Firstpoint
                    }
                    //Ignore all other clicks
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {   
            //Terminate
			window.close();
		}

        //Creating rest of square points:
        Vector2f p2(vertices[1].x,vertices[0].y);            //top-right
        Vector2f p4(vertices[0].x,vertices[1].y);            //bottom-left
        
        vertices.push_back(p2);
        vertices.push_back(p4);                              //Vertices Order: p1, p3, p2, p4

        Vector2f p5( (vertices[0].x + vertices[2].x) / 2.0f, vertices[0].y);       //mid of p1 and p2
        Vector2f p6( vertices[2].x, (vertices[2].y + vertices[1].y) / 2.0f );      //mid of p2 and p3 (y-axis is (+) as it goes down)
        
        vertices.push_back(p5);
        vertices.push_back(p6);                               //Vertices Order: p1, p3, p2, p4, p5, p6

        Vector2f p7(vertices[4].x, vertices[1].y);
        Vector2f p8(vertices[0].x, vertices[5].y);

        vertices.push_back(p7);
        vertices.push_back(p8);

        if(points.size() > 0) {   
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            Vector2f currPoint;
            for (int i = 0; i < 5000; i++) {
                int currVertex;
                currVertex = rand() % 8;
                currPoint.x = points.at(i).x + (2.0/3.0f * (vertices.at(currVertex).x - points.at(i).x) );
                currPoint.y = points.at(i).y + (2.0/3.0f * (vertices.at(currVertex).y - points.at(i).y) );
                points.push_back(currPoint);
            }
        }
        
        window.clear();
        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(3,3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
            window.display();
        }

        float aCounter,wCounter,sCounter,dCounter = 0.0;
        for(unsigned int j = 10; j < points.size(); j++) {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(points[j].x, points[j].y));
            int color = j % 5;
            if (color == 0) { rect.setFillColor(Color::Red); }
            else if (color == 1) { rect.setFillColor(Color::Blue); }
            else if (color == 2) { rect.setFillColor(Color::Green); }
            else if (color == 3) { rect.setFillColor(Color::Yellow);}
            else if (color == 4) { rect.setFillColor(Color::White); }
            
            if(Keyboard::isKeyPressed(Keyboard::A)) { //Shift fractal to the left 
                aCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x - aCounter, points[j].y));
            }
            if(Keyboard::isKeyPressed(Keyboard::W)) { //shit fractal upwards 
                wCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x, points[j].y - wCounter));
            }
            if(Keyboard::isKeyPressed(Keyboard::S)) { //Shift fractal downwards 
                sCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x,points[j].y + sCounter));
            }
            if(Keyboard::isKeyPressed(Keyboard::D)) { //Shift fractal to the right
                dCounter += 0.1f;
                rect.setPosition(Vector2f(points[j].x + dCounter, points[j].y));
            }
                window.draw(rect);
                window.display();
            }

        if(Keyboard::isKeyPressed(Keyboard::R)) //Meant to rotate
        {
            for(unsigned int k = 0; k < points.size(); k++)
            {
                RectangleShape rect1(Vector2f(2,2));
                rect1.setPosition(Vector2f(points[k].x, points[k].y));
                rect1.rotate(10.f);
                rect1.setFillColor(Color::White);
                window.draw(rect1);
                window.display();
            }
        }
        
    }
}
*/