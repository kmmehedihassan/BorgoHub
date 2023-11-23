#include "PingPong.h"

void PingPong::handlePlayerCollision(bool isPlayerLeft)
{
    std::pair<int, int> pb = ball.getTopLeftPos();
    if (isPlayerLeft) {
        std::pair<int, int> pl = playerL.getTopLeftPos();
        switch (pb.second - pl.second) {
        case -2:
        case -1:
        case 0:
            ball.setAngle(Ball::Angle::_60d);
            break;
        case 1:
            ball.setAngle(Ball::Angle::_45d);
            break;
        case 2:
            ball.setAngle(Ball::Angle::_30d);
            break;
        case 3:
            ball.setAngle(Ball::Angle::_0d);
            break;
        case 4:
            ball.setAngle(Ball::Angle::_330d);
            break;
        case 5:
            ball.setAngle(Ball::Angle::_315d);
            break;
        case 6:
        case 7:
        case 8:
            ball.setAngle(Ball::Angle::_300d);
            break;
        }
    }
    else {
        std::pair<int, int> pr = playerR.getTopLeftPos();
        switch (pb.second - pr.second) {
        case -2:
        case -1:
        case 0:
            ball.setAngle(Ball::Angle::_120d);
            break;
        case 1:
            ball.setAngle(Ball::Angle::_135d);
            break;
        case 2:
            ball.setAngle(Ball::Angle::_150d);
            break;
        case 3:
            ball.setAngle(Ball::Angle::_180d);
            break;
        case 4:
            ball.setAngle(Ball::Angle::_210d);
            break;
        case 5:
            ball.setAngle(Ball::Angle::_225d);
            break;
        case 6:
        case 7:
        case 8:
            ball.setAngle(Ball::Angle::_240d);
            break;
        }
    }
}

void PingPong::handleWallCollision(bool isTopWall)
{
    std::pair<int, int> pb = ball.getTopLeftPos();
    if (isTopWall) {
        switch (ball.getAngle()) {
        case Ball::Angle::_60d:
            ball.setAngle(Ball::Angle::_300d);
            break;
        case Ball::Angle::_45d:
            ball.setAngle(Ball::Angle::_315d);
            break;
        case Ball::Angle::_30d:
            ball.setAngle(Ball::Angle::_330d);
            break;
        case Ball::Angle::_120d:
            ball.setAngle(Ball::Angle::_240d);
            break;
        case Ball::Angle::_135d:
            ball.setAngle(Ball::Angle::_225d);
            break;
        case Ball::Angle::_150d:
            ball.setAngle(Ball::Angle::_210d);
            break;
        }
    }
    else {
        switch (ball.getAngle()) {
        case Ball::Angle::_300d:
            ball.setAngle(Ball::Angle::_60d);
            break;
        case Ball::Angle::_315d:
            ball.setAngle(Ball::Angle::_45d);
            break;
        case Ball::Angle::_330d:
            ball.setAngle(Ball::Angle::_30d);
            break;
        case Ball::Angle::_240d:
            ball.setAngle(Ball::Angle::_120d);
            break;
        case Ball::Angle::_225d:
            ball.setAngle(Ball::Angle::_135d);
            break;
        case Ball::Angle::_210d:
            ball.setAngle(Ball::Angle::_150d);
            break;
        }
    }
}

PingPong::PingPong(World& world, ScoreBoard& scoreboard) : Engine(world, scoreboard), delay(0.03f), timer(0.0f),
    playerL(1, this), playerR(0, this), ball(1, this), isIdle(0)
{
    bgcolor = sf::Color::Black;
    width = world.getWidth();
    height = world.getHeight();
}

int PingPong::getWidth()
{
    return width;
}

int PingPong::getHeight()
{
    return height;
}

void PingPong::start()
{
    sf::Clock clock;
    float dt;
    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
        clear();
        input();
        update(dt);
        render();
    }
}

void PingPong::clear()
{
    world.clearObject(ball.getBallPosition());
    world.clearObject(playerL.getPlayerPosition());
    world.clearObject(playerR.getPlayerPosition());
    scoreboard.clearBoard();
}

void PingPong::input()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed) {
            isIdle = 0;
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::Up:
                playerR.moveUp();
                break;
            case sf::Keyboard::Down:
                playerR.moveDown();
                break;
            case sf::Keyboard::W:
                playerL.moveUp();
                break;
            case sf::Keyboard::S:
                playerL.moveDown();
                break;
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
        }
        catch (Ball::Collision col) {
            switch (col.collisionType) {
            case Ball::Collision::CollisionType::LeftPlayer:
                handlePlayerCollision(1);
                break;
            case Ball::Collision::CollisionType::RightPlayer:
                handlePlayerCollision(0);
                break;
            case Ball::Collision::CollisionType::TopWall:
                handleWallCollision(1);
                break;
            case Ball::Collision::CollisionType::BottomWall:
                handleWallCollision(0);
                break;
            }
        }
        catch (Ball::GameOver game) {
            if (game.gameWinner == Ball::GameOver::GameWinner::LeftPlayer) {
                ball = Ball(1, this);
                playerL.incrementScore();
            }
            else {
                ball = Ball(0, this);
                playerR.incrementScore();
            }
            isIdle = 1;
            playerL.resetPosition(1);
            playerR.resetPosition(0);
        }

        timer = 0;
    }
    world.addObject(playerL.getPlayerColor());
    world.addObject(playerR.getPlayerColor());
    world.addObject(ball.getBallColor());
    world.update();
    scoreboard.addScore(std::pair<std::string, int>("P1", playerL.getScore()));
    scoreboard.addScore(std::pair<std::string, int>("P2", playerR.getScore()));
    scoreboard.update();
}

void PingPong::render()
{
    window.clear();
    window.draw(world);
    window.draw(scoreboard);
    window.display();
}


PingPongPlayer::PingPongPlayer(bool isPlayerLeft, PingPong* engine) : score(0)
{
    this->engine = engine;
    color = sf::Color::Cyan;
    if (isPlayerLeft) {
        for (int i = 0; i < 2; i++) {
            for (int j = 12; j < 20; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
    }
    else {
        for (int i = 54; i < 56; i++) {
            for (int j = 12; j < 20; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
    }
}

int PingPongPlayer::getScore() const
{
    return score;
}

std::set<std::pair<int, int>> PingPongPlayer::getPlayerPosition() const
{
    return position;
}

std::map<std::pair<int, int>, sf::Color> PingPongPlayer::getPlayerColor() const
{
    std::map<std::pair<int, int>, sf::Color> ret;
    for (auto p : position) {
        ret[p] = color;
    }
    return ret;
}

std::pair<int, int> PingPongPlayer::getTopLeftPos() const
{
    std::pair<int, int> ret(INT_MAX, INT_MAX);
    for (auto p : position) {
        ret = std::min(ret, p);
    }
    return ret;
}

void PingPongPlayer::moveUp()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        std::pair<int, int> np(p.first, p.second - 1);
        if (np.second < 0) return;
        newPos.insert(np);
    }
    position = newPos;
}

void PingPongPlayer::moveDown()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        p.second++;
        if (p.second >= engine->getHeight()) return;
        newPos.insert(p);
    }
    position = newPos;
}

void PingPongPlayer::resetPosition(bool isPlayerLeft)
{
    position.clear();
    if (isPlayerLeft) {
        for (int i = 0; i < 2; i++) {
            for (int j = 12; j < 20; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
    }
    else {
        for (int i = 54; i < 56; i++) {
            for (int j = 12; j < 20; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
    }
}

void PingPongPlayer::incrementScore()
{
    score++;
}

void Ball::moveLeft()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        std::pair<int, int> np(p.first - 1, p.second);
        for (auto pl : engine->playerL.getPlayerPosition()) {
            if (pl == np && getTopLeftPos().first - engine->playerL.getTopLeftPos().first == 2) {
                throw Collision(Collision::CollisionType::LeftPlayer);
            }
        }
        if (np.first <= 0) throw GameOver(GameOver::GameWinner::RightPlayer);
        newPos.insert(np);
    }
    position = newPos;
}

void Ball::moveRight()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        std::pair<int, int> np(p.first + 1, p.second);
        for (auto pr : engine->playerR.getPlayerPosition()) {
            if (pr == np && engine->playerR.getTopLeftPos().first - getTopLeftPos().first == 2) {
                throw Collision(Collision::CollisionType::RightPlayer);
            }
        }
        if (np.first >= engine->getWidth() - 1) throw GameOver(GameOver::GameWinner::LeftPlayer);
        newPos.insert(np);
    }
    position = newPos;
}

void Ball::moveUp()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        std::pair<int, int> np(p.first, p.second - 1);
        if (np.second < 0) throw Collision(Collision::CollisionType::TopWall);
        newPos.insert(np);
    }
    position = newPos;
}

void Ball::moveDown()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : position) {
        std::pair<int, int> np(p.first, p.second + 1);
        if (np.second >= engine->getHeight()) throw Collision(Collision::CollisionType::BottomWall);
        newPos.insert(np);
    }
    position = newPos;
}

void Ball::setDirection(Angle a)
{
    while (!direction.empty()) direction.pop();
    switch (a) {
    case _0d:
        direction.push(TransformDirection::Right);
        break;
    case _30d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Top);
        break;
    case _45d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Top);
        break;
    case _60d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Top);
        direction.push(TransformDirection::Top);
        break;
    case _120d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Top);
        direction.push(TransformDirection::Top);
        break;
    case _135d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Top);
        break;
    case _150d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Top);
        break;
    case _180d:
        direction.push(TransformDirection::Left);
        break;
    case _210d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Bottom);
        break;
    case _225d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Bottom);
        break;
    case _240d:
        direction.push(TransformDirection::Left);
        direction.push(TransformDirection::Bottom);
        direction.push(TransformDirection::Bottom);
        break;
    case _300d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Bottom);
        direction.push(TransformDirection::Bottom);
        break;
    case _315d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Bottom);
        break;
    case _330d:
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Right);
        direction.push(TransformDirection::Bottom);
        break;
    }
}

Ball::Ball(bool isPlayerLeft, PingPong* engine)
{
    this->engine = engine;
    color = sf::Color::Yellow;
    if (isPlayerLeft) {
        for (int i = 2; i < 4; i++) {
            for (int j = 14; j < 16; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
        setAngle(Angle::_45d);

    }
    else {
        for (int i = 52; i < 54; i++) {
            for (int j = 14; j < 16; j++) {
                position.insert(std::pair<int, int>(i, j));
            }
        }
        setAngle(Angle::_135d);
    }
}

Ball::Angle Ball::getAngle()
{
    return angle;
}

void Ball::setAngle(Angle a)
{
    this->angle = a;
    setDirection(a);
}

std::set<std::pair<int, int>> Ball::getBallPosition() const
{
    return position;
}

std::map<std::pair<int, int>, sf::Color> Ball::getBallColor() const
{
    std::map<std::pair<int, int>, sf::Color> ret;
    for (auto p : position) {
        ret[p] = color;
    }
    return ret;
}

std::pair<int, int> Ball::getTopLeftPos() const
{
    std::pair<int, int> ret(INT_MAX, INT_MAX);
    for (auto p : position) {
        ret = std::min(ret, p);
    }
    return ret;
}

void Ball::move()
{
    TransformDirection dir = direction.front();
    switch (dir) {
    case TransformDirection::Left:
        moveLeft();
        break;
    case TransformDirection::Right:
        moveRight();
        break;
    case TransformDirection::Top:
        moveUp();
        break;
    case TransformDirection::Bottom:
        moveDown();
        break;
    }
    direction.pop();
    direction.push(dir);
}

Ball::GameOver::GameOver(GameWinner winner) : gameWinner(winner)
{
}

Ball::Collision::Collision(CollisionType type) : collisionType(type)
{
}
