#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glu.h>  
// #include "masterCar.h"
#include "masterCar.cpp"
#include "road.cpp"
using namespace std;
using namespace sf;
void drawWheel(float radius, float width) {
    GLUquadric* quad = gluNewQuadric();
    // cylinder along Z axis; rotate so cylinder axis aligns with X
    glPushMatrix();
        glRotatef(0, 0, 1, 0);
        // draw cylinder (outer)
        gluQuadricNormals(quad, GLU_SMOOTH);
        gluCylinder(quad, radius, radius, width, 24, 1);
        // draw disks on sides
        glPushMatrix();
            // cap at start
            gluDisk(quad, 0.0, radius, 24, 1);
        glPopMatrix();
        glTranslatef(0.0f, 0.0f, width);
        glPushMatrix();
            // cap at end
            gluDisk(quad, 0.0, radius, 24, 1);
        glPopMatrix();
    glPopMatrix();
    gluDeleteQuadric(quad);
}
void drawCube(float w, float h, float d) {
    float hw = w * 0.5f, hh = h * 0.5f, hd = d * 0.5f;
    glBegin(GL_QUADS);
    // top (y = +hh)
    glNormal3f(0,1,0);
    glVertex3f(-hw, hh, -hd);
    glVertex3f(hw, hh, -hd);
    glVertex3f(hw, hh, hd);
    glVertex3f(-hw, hh, hd);
    // bottom (y = -hh)
    glNormal3f(0,-1,0);
    glVertex3f(-hw, -hh, -hd);
    glVertex3f(-hw, -hh, hd);
    glVertex3f(hw, -hh, hd);
    glVertex3f(hw, -hh, -hd);
    // front (z = +hd)
    glNormal3f(0,0,1);
    glVertex3f(-hw, -hh, hd);
    glVertex3f(-hw, hh, hd);
    glVertex3f(hw, hh, hd);
    glVertex3f(hw, -hh, hd);
    // back (z = -hd)
    glNormal3f(0,0,-1);
    glVertex3f(-hw, -hh, -hd);
    glVertex3f(hw, -hh, -hd);
    glVertex3f(hw, hh, -hd);
    glVertex3f(-hw, hh, -hd);
    // left (x = -hw)
    glNormal3f(-1,0,0);
    glVertex3f(-hw, -hh, -hd);
    glVertex3f(-hw, hh, -hd);
    glVertex3f(-hw, hh, hd);
    glVertex3f(-hw, -hh, hd);
    // right (x = +hw)
    glNormal3f(1,0,0);
    glVertex3f(hw, -hh, -hd);
    glVertex3f(hw, -hh, hd);
    glVertex3f(hw, hh, hd);
    glVertex3f(hw, hh, -hd);
    glEnd();
}
void setupGL(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // simple light
    GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // perspective: fov 45, aspect, near 0.1, far 100
    gluPerspective(45.0, (double)width / (double)height, 0.1, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(){
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Infinite Road 2D Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // --- Colors ---
    sf::Color backgroundColor(100, 150, 255); // Sky blue

    // Create instances of the Car and Road classes
    MasterCar myCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    Road myRoad(sf::Vector2f(window.getSize().x, window.getSize().y));

    // --- Game Clock for Time-Based Movement ---
    sf::Clock clock;

    // --- Main Game Loop ---
    while (window.isOpen())
    {
        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // --- Event Handling ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Update ---
        myCar.update(deltaTime, window);
        myRoad.update(deltaTime, sf::Vector2f(window.getSize().x, window.getSize().y));

        // --- Render ---
        window.clear(backgroundColor);
        myRoad.draw(window);
        myCar.draw(window);
        window.display();
    }

    return 1;
}
