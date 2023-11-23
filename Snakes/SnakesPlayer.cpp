#include "SnakesPlayer.h"

bool SnakesPlayer::isDigested(Food& food)
{
    for (auto b : body) {
        if (b.getPosition() == food.getPosition()) return false;
    }
    return true;
}

SnakesPlayer::SnakesPlayer() : score(0)
{
    std::pair<int, int> p1(5, 6), p2(6, 6), p3(7, 6);
    body.push_back(SnakeBody(p3, Right));
    body.push_back(SnakeBody(p2, Right));
    body.push_back(SnakeBody(p1, Right));
}

std::pair<int, int> SnakesPlayer::getHeadPosition()
{
    return body[0].getPosition();
}

std::map<std::pair<int, int>, sf::Color> SnakesPlayer::getPlayerColors() const
{
    std::map<std::pair<int, int>, sf::Color> ret;
    for (auto b : body) {
        ret[b.getPosition()] = b.getColor();
    }
    return ret;
}

std::set<std::pair<int, int>> SnakesPlayer::getPlayerPosition() const
{
    std::set<std::pair<int, int>> ret;
    for (auto b : body) {
        ret.insert(b.getPosition());
    }
    return ret;
}

int SnakesPlayer::getScore()
{
    return score;
}

void SnakesPlayer::setDirection(TransformDirection dir)
{
    if ((dir | body[0].getDirection()) == 3 || (dir | body[0].getDirection()) == 12) return; /// invalid direction input : ignore
    body[0].setDirection(dir);
}

void SnakesPlayer::eatFood(Food& food)
{
    foodsEaten.push(food);
    score += food.getPoints();
}

void SnakesPlayer::moveForward()
{
    TransformDirection prev = body[0].getDirection();
    for (int i = 0; i < body.size(); i++) {
        std::pair<int, int> newPos = body[i].getPosition();
        switch (body[i].getDirection()) {
        case TransformDirection::Left:
            newPos.first -= 1;
            break;
        case TransformDirection::Right:
            newPos.first += 1;
            break;
        case TransformDirection::Top:
            newPos.second -= 1;
            break;
        case TransformDirection::Bottom:
            newPos.second += 1;
            break;
        }
        if (newPos.first < 0 || newPos.first >= 20 || newPos.second < 0 || newPos.second >= 12) throw GameOver();
        if (i == 0 && newPos != body.back().getPosition()) {
            for (auto b : body) {
                if (newPos == b.getPosition()) throw GameOver();
            }
        }
        body[i].setPosition(newPos);

        TransformDirection temp = body[i].getDirection();
        body[i].setDirection(prev);
        prev = temp;
    }
    if (!foodsEaten.empty() && isDigested(foodsEaten.front())) {
        SnakeBody bodyPart(foodsEaten.front().getPosition(), prev);
        foodsEaten.pop();
        body.push_back(bodyPart);
    }
}
