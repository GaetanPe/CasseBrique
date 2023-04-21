#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Casse-Brique");

    sf::RectangleShape racket(sf::Vector2f(100.f, 20.f));
    racket.setFillColor(sf::Color::Green);
    racket.setOrigin(racket.getSize() / 2.f);
    racket.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(racket.getPosition().x, racket.getPosition().y - racket.getSize().y / 2.f - ball.getRadius());

    const int row = 5;
    const int column = 10;
    sf::RectangleShape bricks[row][column];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            bricks[i][j].setSize(sf::Vector2f(70.f, 20.f));
            bricks[i][j].setFillColor(sf::Color::Yellow);
            bricks[i][j].setOrigin(bricks[i][j].getSize() / 2.f);
            bricks[i][j].setPosition(100.f + j * (bricks[i][j].getSize().x + 10.f), 50.f + i * (bricks[i][j].getSize().y + 10.f));
        }
    }

    bool gameOver = false;
    bool victory = false;
    int remainingBricks = row * column;
    sf::Vector2f ballVelocity(200.f, -200.f);
    const float ballSpeed = 400.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver && !victory) {
            ball.move(ballVelocity * window.getSize().x / 800.f * window.getSize().y / 600.f * clock.getElapsedTime());

            if (ball.getPosition().x - ball.getRadius() < 0.f) {
                ball.setPosition(ball.getRadius(), ball.getPosition().y);
                ballVelocity.x = -ballVelocity.x;
            }
            if (ball.getPosition().x + ball.getRadius() > window.getSize().x) {
                ball.setPosition(window.getSize().x - ball.getRadius(), ball.getPosition().y);
                ballVelocity.x = -ballVelocity.x;
            }
            if (ball.getPosition().y - ball.getRadius() < 0.f) {
                ball.setPosition(ball.getPosition().x, ball.getRadius());
                ballVelocity.y = -ballVelocity.y;
            }

            if (ball.getGlobalBounds().intersects(racket.getGlobalBounds())) {
                ball.setPosition(ball.getPosition().x, racket.getPosition().y - racket.getSize().y / 2.f - ball.getRadius());
                ballVelocity.y = -ballVelocity.y;
            }

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (bricks[i][j].getGlobalBounds().intersects(ball.getGlobalBounds()))
                    {
                        bricks[i][j].setFillColor(sf::Color::Transparent);
                        remainingBricks--;
                        if (remainingBricks == 0) {
                            victory = true;
                            break;
                        }
                        if (ball.getPosition().y < bricks[i][j].getPosition().x) {

                        }
                    }
                }
            }
        }
    }
	return 0;
}