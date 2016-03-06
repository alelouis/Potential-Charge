#include "Header.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Potential Charges", sf::Style::Default, settings);
    sf::CircleShape shape(100.f);
    sf::Color black(0,0,0,255);
    sf::Texture bgTex;
    sf::Sprite grav;
    sf::Vertex line[] = {};
    sf::Uint8 *pixels = new sf::Uint8[1280*720*4];
    float force;
    double fx = 0;
    double fy = 0;
    std::deque<Object*> masses;
    masses.push_front(new Object(400,300,1,true));
    int nbObjects = 1;
    window.setVerticalSyncEnabled(true);
    bgTex.create(1280, 720);
    grav.setTexture(bgTex);
    float red, green, blue;
    bool mode = true;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved)
            {
                if (mode) {
                    masses[0]->setX(event.mouseMove.x);
                    masses[0]->setY(event.mouseMove.y);
                }else{
                    
                    fx = 0;
                    fy = 0;
                    for(int j=0;j<masses.size();j++){
                        double dx = masses[j]->getX()-event.mouseMove.x;
                        double dy = masses[j]->getY()-event.mouseMove.y;
                        double angle = atan2(dy, dx);
                        fx += masses[j]->calcGravityForceAt(event.mouseMove.x,event.mouseMove.y)*10000000*cos(angle);
                        fy += masses[j]->calcGravityForceAt(event.mouseMove.x,event.mouseMove.y)*10000000*sin(angle);
                     }
                    line[0] = sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                    line[1] = sf::Vertex(sf::Vector2f(event.mouseMove.x+fx,event.mouseMove.y+fy));
                    window.draw(line, 2, sf::Lines);
                     
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    masses.push_front(new Object(event.mouseButton.x+1,event.mouseButton.y+1,1,masses[0]->getSigne()));
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    masses[0]->setSigne(!masses[0]->getSigne());
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    mode = !mode;
                }
            }
        }
        
        for(int x = 0; x < 1280; x++)
        {
            for(int y = 0; y < 720; y++)
            {
                //std::cout << mass.toColor((mass.calcGravityForceAt(x, y) + mass2.calcGravityForceAt(x, y))) << std::endl;
                for(int j=0;j<masses.size();j++){
                    force += masses[j]->calcGravityForceAt(x, y);
                }
                masses[0]->getHeatMapColor(force*5000, &red, &green, &blue);
                pixels[(1280 * y + x)*4] = red*255; // R
                pixels[(1280 * y + x)*4 + 1] = green*255; // G
                pixels[(1280 * y + x)*4+ 2] = blue*255; // B
                pixels[(1280 * y + x)*4 + 3] = 255; // A
                force = 0;
            }
        }
        
        bgTex.update(pixels);
        window.draw(grav);
        
        for(int x = 0; x <= 1280; x=x+40)
        {
            for(int y = 0; y <= 720; y=y+40)
            {
                fx = 0;
                fy = 0;
                for(int j=0;j<masses.size();j++){
                    double dx = masses[j]->getX()-x;
                    double dy = masses[j]->getY()-y;
                    double angle = atan2(dy, dx);
                    fx += masses[j]->calcGravityForceAt(x,y)*1000000*cos(angle);
                    fy += masses[j]->calcGravityForceAt(x,y)*1000000*sin(angle);
                }
                double norm = sqrt(fx*fx + fy*fy);
                if (norm>50) {
                    fx/=0;
                    fy/=0;
                }
                //fx /= 0.05*norm;
                //fy /= 0.05*norm;
                sf::Color lineColor(255,255,255,100+3*norm);
                line[0] = sf::Vertex(sf::Vector2f(x, y), lineColor);
                line[1] = sf::Vertex(sf::Vector2f(x+fx,y+fy), lineColor);
                window.draw(line, 2, sf::Lines);
            }
        }
        window.display();
    }
    
    return 0;
}