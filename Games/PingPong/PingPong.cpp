// File: games/PingPong/PingPong.cpp
#include "PingPong.h"
#include <algorithm>     // std::min

namespace borgo {

/*-----------------------------------------------------------*
 |  PingPong – private helpers                               |
 *-----------------------------------------------------------*/
void PingPong::handlePlayerCollision(bool isPlayerLeft)
{
    auto pb = ball.getTopLeftPos();
    if (isPlayerLeft) {
        auto pl = playerL.getTopLeftPos();
        switch (pb.second - pl.second) {
        case -2: case -1: case 0:  ball.setAngle(Ball::Angle::_60d);  break;
        case  1:                   ball.setAngle(Ball::Angle::_45d);  break;
        case  2:                   ball.setAngle(Ball::Angle::_30d);  break;
        case  3:                   ball.setAngle(Ball::Angle::_0d);   break;
        case  4:                   ball.setAngle(Ball::Angle::_330d); break;
        case  5:                   ball.setAngle(Ball::Angle::_315d); break;
        default:                   ball.setAngle(Ball::Angle::_300d); break;
        }
    } else {
        auto pr = playerR.getTopLeftPos();
        switch (pb.second - pr.second) {
        case -2: case -1: case 0:  ball.setAngle(Ball::Angle::_120d); break;
        case  1:                   ball.setAngle(Ball::Angle::_135d); break;
        case  2:                   ball.setAngle(Ball::Angle::_150d); break;
        case  3:                   ball.setAngle(Ball::Angle::_180d); break;
        case  4:                   ball.setAngle(Ball::Angle::_210d); break;
        case  5:                   ball.setAngle(Ball::Angle::_225d); break;
        default:                   ball.setAngle(Ball::Angle::_240d); break;
        }
    }
}



void PingPong::handleWallCollision(bool isTopWall)
{
    auto swap = [this](Ball::Angle a) { ball.setAngle(a); };

    if (isTopWall) {
        switch (ball.getAngle()) {
        case Ball::Angle::_60d:  swap(Ball::Angle::_300d); break;
        case Ball::Angle::_45d:  swap(Ball::Angle::_315d); break;
        case Ball::Angle::_30d:  swap(Ball::Angle::_330d); break;
        case Ball::Angle::_120d: swap(Ball::Angle::_240d); break;
        case Ball::Angle::_135d: swap(Ball::Angle::_225d); break;
        case Ball::Angle::_150d: swap(Ball::Angle::_210d); break;
        default: break;
        }
    } else {
        switch (ball.getAngle()) {
        case Ball::Angle::_300d: swap(Ball::Angle::_60d);  break;
        case Ball::Angle::_315d: swap(Ball::Angle::_45d);  break;
        case Ball::Angle::_330d: swap(Ball::Angle::_30d);  break;
        case Ball::Angle::_240d: swap(Ball::Angle::_120d); break;
        case Ball::Angle::_225d: swap(Ball::Angle::_135d); break;
        case Ball::Angle::_210d: swap(Ball::Angle::_150d); break;
        default: break;
        }
    }
}

/*-----------------------------------------------------------*
 |  PingPong – ctor / trivial getters                        |
 *-----------------------------------------------------------*/
PingPong::PingPong(World& w, ScoreBoard& s)
: Engine(w,s)
, delay (0.03f)
, timer (0.f)
, isIdle(true)
, bgcolor(sf::Color::Black)
, playerL(true ,this)
, playerR(false,this)
, ball   (true ,this)
{
    width  = w.getWidth();
    height = w.getHeight();
}

int PingPong::getWidth()  const { return width;  }
int PingPong::getHeight() const { return height; }

/*-----------------------------------------------------------*
 |  Game loop                                                 |
 *-----------------------------------------------------------*/
void PingPong::start()
{
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        clear();
        input();
        update(dt);
        render();
    }
}

void PingPong::clear()
{
    world.clearObject(ball   .getBallPosition());
    world.clearObject(playerL.getPlayerPosition());
    world.clearObject(playerR.getPlayerPosition());
    scoreboard.clearBoard();
}

void PingPong::input()
{
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) { window.close(); return; }
        if (e.type == sf::Event::KeyPressed) {
            isIdle = false;
            switch (e.key.code) {
            case sf::Keyboard::Escape: window.close();           break;
            case sf::Keyboard::Up:     playerR.moveUp();         break;
            case sf::Keyboard::Down:   playerR.moveDown();       break;
            case sf::Keyboard::W:      playerL.moveUp();         break;
            case sf::Keyboard::S:      playerL.moveDown();       break;
            default: break;
            }
        }
    }
}

void PingPong::update(float& dt)
{
    timer += dt;

    if (!isIdle && timer > delay) {
        try {
            ball.move();
        } catch (const Ball::Collision& c) {
            switch (c.collisionType) {
            case Ball::Collision::CollisionType::LeftPlayer:  handlePlayerCollision(true);  break;
            case Ball::Collision::CollisionType::RightPlayer: handlePlayerCollision(false); break;
            case Ball::Collision::CollisionType::TopWall:     handleWallCollision(true);    break;
            case Ball::Collision::CollisionType::BottomWall:  handleWallCollision(false);   break;
            }
        } catch (const Ball::GameOver& g) {
            if (g.gameWinner == Ball::GameOver::GameWinner::LeftPlayer) {
                ball = Ball(true ,this);
                playerL.incrementScore();
            } else {
                ball = Ball(false,this);
                playerR.incrementScore();
            }
            isIdle = true;
            playerL.resetPosition(true);
            playerR.resetPosition(false);
        }
        timer = 0.f;
    }

    /* push new frame to world/scoreboard */
    world.addObject(playerL.getPlayerColor());
    world.addObject(playerR.getPlayerColor());
    world.addObject(ball   .getBallColor());
    world.update();

    scoreboard.addScore({"P1", playerL.getScore()});
    scoreboard.addScore({"P2", playerR.getScore()});
    scoreboard.update();
}

void PingPong::render()
{
    window.clear(bgcolor);
    window.draw(world);
    window.draw(scoreboard);
    window.display();
}

/*-----------------------------------------------------------*
 |  PingPongPlayer implementation                            |
 *-----------------------------------------------------------*/
PingPongPlayer::PingPongPlayer(bool left, PingPong* e)
: engine(e)
{
    int x0 = left ? 0 : e->getWidth()-2;
    for (int x = x0; x < x0+2; ++x)
        for (int y = 12; y < 20; ++y)
            position.insert({x,y});
}

void PingPongPlayer::incrementScore()          { ++score; }
int  PingPongPlayer::getScore()           const { return score; }
auto PingPongPlayer::getPlayerPosition()  const -> std::set<std::pair<int,int>> { return position; }

auto PingPongPlayer::getPlayerColor() const
-> std::map<std::pair<int,int>,sf::Color>
{
    std::map<std::pair<int,int>,sf::Color> out;
    for (auto p : position) out[p] = color;
    return out;
}

std::pair<int,int> PingPongPlayer::getTopLeftPos() const
{
    return *std::min_element(position.begin(), position.end());
}

void PingPongPlayer::moveUp()
{
    for (auto& p : position)
        if (p.second == 0) return;       // hit top
    std::set<std::pair<int, int>> newPos;
for (auto p : position) { --p.second; newPos.insert(p); }
position = newPos;

}

void PingPongPlayer::moveDown()
{
    for (auto& p : position)
        if (p.second == engine->getHeight()-1) return; // hit bottom
    std::set<std::pair<int, int>> newPos;
for (auto p : position) {
    ++p.second;        // or --p.second, whatever your logic needs
    newPos.insert(p);
}
position = newPos;
}

void PingPongPlayer::resetPosition(bool left) { *this = PingPongPlayer(left,engine); }

/*-----------------------------------------------------------*
 |  Ball implementation                                      |
 *-----------------------------------------------------------*/
Ball::Ball(bool fromLeft, PingPong* e)
: engine(e)
{
    int x0 = fromLeft ? 2 : e->getWidth()-4;
    for (int x = x0; x < x0+2; ++x)
        for (int y = 14; y < 16; ++y)
            position.insert({x,y});
    setAngle(fromLeft ? Angle::_45d : Angle::_135d);
}

Ball::Angle Ball::getAngle() const { return angle; }

void Ball::setAngle(Angle a)
{
    angle = a;
    setDirection(a);
}

auto Ball::getBallPosition() const -> std::set<std::pair<int,int>> { return position; }

auto Ball::getBallColor() const
-> std::map<std::pair<int,int>,sf::Color>
{
    std::map<std::pair<int,int>,sf::Color> out;
    for (auto p : position) out[p] = color;
    return out;
}

std::pair<int,int> Ball::getTopLeftPos() const
{
    return *std::min_element(position.begin(), position.end());
}

/*--------- movement helpers ----------*/
void Ball::moveLeft ()
{
    std::set<std::pair<int,int>> next;
    for (auto p : position) {
        auto np = std::make_pair(p.first-1, p.second);
        if (np.first < 0) throw GameOver(GameOver::GameWinner::RightPlayer);
        if (engine->playerL.getPlayerPosition().count(np) &&
            getTopLeftPos().first - engine->playerL.getTopLeftPos().first == 2)
            throw Collision(Collision::CollisionType::LeftPlayer);
        next.insert(np);
    }
    position.swap(next);
}

void Ball::moveRight()
{
    std::set<std::pair<int,int>> next;
    for (auto p : position) {
        auto np = std::make_pair(p.first+1, p.second);
        if (np.first >= engine->getWidth())
            throw GameOver(GameOver::GameWinner::LeftPlayer);
        if (engine->playerR.getPlayerPosition().count(np) &&
            engine->playerR.getTopLeftPos().first - getTopLeftPos().first == 2)
            throw Collision(Collision::CollisionType::RightPlayer);
        next.insert(np);
    }
    position.swap(next);
}

void Ball::moveUp  ()
{
    for (auto& p : position)
        if (p.second == 0) throw Collision(Collision::CollisionType::TopWall);
    std::set<std::pair<int, int>> newPos;
for (auto p : position) { --p.second; newPos.insert(p); }
position = newPos;

}

void Ball::moveDown()
{
    for (auto& p : position)
        if (p.second == engine->getHeight()-1) throw Collision(Collision::CollisionType::BottomWall);
    std::set<std::pair<int, int>> newPos;
for (auto p : position) {
    ++p.second;        // or --p.second, whatever your logic needs
    newPos.insert(p);
}
position = newPos;
}

void Ball::setDirection(Angle a)
{
    while (!direction.empty()) direction.pop();

    auto push = [this](TransformDirection d,int n=1){ while(n--) direction.push(d); };

    switch (a) {
    case Angle::_0d:   push(Right);                              break;
    case Angle::_30d:  push(Right,2); push(Top);                 break;
    case Angle::_45d:  push(Right);   push(Top);                 break;
    case Angle::_60d:  push(Right);   push(Top,2);               break;
    case Angle::_120d: push(Left);    push(Top,2);               break;
    case Angle::_135d: push(Left);    push(Top);                 break;
    case Angle::_150d: push(Left,2);  push(Top);                 break;
    case Angle::_180d: push(Left);                               break;
    case Angle::_210d: push(Left,2);  push(Bottom);              break;
    case Angle::_225d: push(Left);    push(Bottom);              break;
    case Angle::_240d: push(Left);    push(Bottom,2);            break;
    case Angle::_300d: push(Right);   push(Bottom,2);            break;
    case Angle::_315d: push(Right);   push(Bottom);              break;
    case Angle::_330d: push(Right,2); push(Bottom);              break;
    }
}

void Ball::move()
{
    TransformDirection d = direction.front();
    switch (d) {
    case Left:   moveLeft();  break;
    case Right:  moveRight(); break;
    case Top:    moveUp();    break;
    case Bottom: moveDown();  break;
    }
    direction.pop();
    direction.push(d);  // circular queue
}

} // namespace borgo
