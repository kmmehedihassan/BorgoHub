#include "Tetris.h"

Tetris::Tetris(World& world, ScoreBoard& scoreboard)
 : Engine(world, scoreboard), player("Sami"), tetromino(rand()%7, this), timer(0.0f), delay(0.6f)
{
    srand(time(NULL));
    std::pair<std::string, int> score("Score", player.getScore());
//    std::pair<std::string, int> time("Time", std::floor(player.getTime().asSeconds()));
//    scoreboard.addScore(score);
//    scoreboard.addScore(time);
    scoreboard.setBackgroundColor(sf::Color::White);
    scoreboard.setTextColor(sf::Color::Black);
}

Tetris::Tetris(float bSize, unsigned int width, unsigned int height, sf::Vector2f& pos)
 : Engine(bSize, width, height, pos), player("sami"), tetromino(rand()%7, this), timer(0.0f), delay(0.6f)
{
    srand(time(NULL));
}

void Tetris::start()
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

void Tetris::clear()
{
    world.clearObject(tetromino.getPosition());
}

void Tetris::input()
{
    sf::Event ev;
    try {
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();
            if(ev.type == sf::Event::KeyPressed){
                if(ev.key.code == sf::Keyboard::Up) tetromino.rotate();
                else if(ev.key.code == sf::Keyboard::Left) tetromino.moveLeft();
                else if(ev.key.code == sf::Keyboard::Down) delay = 0.05;
                else if(ev.key.code == sf::Keyboard::Right) tetromino.moveRight();
                else if(ev.key.code == sf::Keyboard::Escape) window.close();
            }
        }
    } catch(Block_base::OutOfBound) {
        std::cout<<"Out of Bound Error"<<std::endl;
    }

}

void Tetris::update(float& dt)
{
    timer += dt;
    player.incrementTime(dt);
    if (timer > delay)
    {
        tetromino.fallDown();

        if (!checkCollision())
        {
            tetromino.undoMovement(); /// send exception or just leave it
            world.addObject(tetromino.getColors());
            tetromino = Tetromino(rand()%7, rand()%4, this);

            checkCompletedLines();

            if(!checkCollision()) {
                std::cout<<"Game Over"<<std::endl;
                window.close();
            }
        }

        timer = 0;
        delay = 0.3;
    }



    world.addObject(tetromino.getColors());
//    scoreboard.editScore("Score", player.getScore());
//    scoreboard.editScore("Time", std::floor(player.getTime().asSeconds()));

    world.update();
    scoreboard.update();
}

void Tetris::render()
{
    window.clear();
    window.draw(world);
    window.display();
}

bool Tetris::checkCollision()
{
    for(auto p:tetromino.getPosition()){
        if(p.first<0||p.first>=world.getWidth()||p.second<0||p.second>=world.getHeight()) return false;
        if(!checkCollision(p)) return false;
    }
    return true;
}

bool Tetris::checkCollision(const std::pair<int,int>& p)
{
    if(p.first<0||p.first>=world.getWidth()||p.second<0||p.second>=world.getHeight()) return false;
    std::pair<int,int> pos = p;
    return !world.checkForObject(pos);
}

void Tetris::checkCompletedLines(){
    while(true) {
        int lineCount=0;
        for(int i = getHeight()-1; i>=0; i--) {
            bool isComplete = true;
            for(int j = 0; j < getWidth(); j++) {
                std::pair<int,int> p(j,i);
                if(checkCollision(p)) isComplete=false;
            }
            if(isComplete) {
                for(int j=i-1; j>=0; j--) {
                    std::set<std::pair<int,int>> fromPos;
                    for(int k=0; k<getWidth(); k++){
                        fromPos.insert(std::pair<int,int>(k, j));
                    }
                    std::map<std::pair<int, int>, sf::Color> fromCol = world.getObjectColors(fromPos);
                    std::set<std::pair<int,int>> toPos;
                    std::map<std::pair<int, int>, sf::Color> toCol;
                    for(int k=0; k<getWidth(); k++){
                        std::pair<int,int> p(k,j);
                        if(world.checkForObject(p)){
                            toCol[std::pair<int,int>(k, j+1)] = fromCol[p];
                        }
                        toPos.insert(std::pair<int,int>(k,j+1));
                    }
                    world.clearObject(toPos);
                    world.addObject(toCol);
                }
                std::set<std::pair<int, int>> topPos;
                for(int k=0; k<getWidth(); k++){
                    topPos.insert(std::pair<int,int>(k, 0));
                }
                world.clearObject(topPos);
                lineCount++;
                player.setScore(player.getScore()+100);
            }
        }
        if(lineCount == 0) break;
    }
}

int Tetris::getWidth() const
{
    return world.getWidth();
}

int Tetris::getHeight() const
{
    return world.getHeight();
}

std::set<std::pair<int, int>> Tetris::getPlayerPosition()
{
    return tetromino.getPosition();
}

Tetromino::Tetromino(int index, Tetris* engine) : rotation(0), undone(false)
{
    this->engine = engine;
    color = tetrominoColor[index];
    prevBase = std::pair<int, int>(4, 0);
    relBase = std::pair<int, int>(4, 0);
    for (int j = 4; j > 0; j--) {
        for (int k = 4; k > 0; k--) {
            if (tetrominoMap[index] & (1 << (4 * (j - 1) + k - 1)))
                pos.insert(std::pair<int, int>(relBase.first+k-1, relBase.second+j-1));
        }
    }
}

Tetromino::Tetromino(int index, int rotation, Tetris* engine) : rotation(rotation), undone(false)
{
    this->engine = engine;
    color = tetrominoColor[index];
    prevBase = std::pair<int, int>(4, 0);
    relBase = std::pair<int, int>(4, 0);
    for (int j = 4; j > 0; j--) {
        for (int k = 4; k > 0; k--) {
            if (tetrominoMap[index] & (1 << (4 * (j - 1) + k - 1)))
                pos.insert(std::pair<int, int>(relBase.first+k-1, relBase.second+j-1));
        }
    }
    for (int i = 0; i < rotation; i++) {
        rotate();
    }
}

std::set<std::pair<int, int>> Tetromino::getPosition() const
{
    return this->pos;
}

std::map<std::pair<int, int>, sf::Color> Tetromino::getColors()
{
    std::map<std::pair<int, int>, sf::Color> ret;
    for(auto p : pos) {
        ret.insert(std::make_pair(p, color));
    }
    return ret;
}

void Tetromino::fallDown()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : pos) {
        p.second++;
        newPos.insert(p);
    }
    prevPos = pos;
    pos = newPos;
    prevBase = relBase;
    relBase.second++;
}

void Tetromino::moveLeft()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : pos) {
        p.first--;
        if(!engine->checkCollision(p)) return;
        newPos.insert(p);
    }
    prevPos = pos;
    pos = newPos;
    prevBase = relBase;
    relBase.first--;
}

void Tetromino::moveRight()
{
    std::set<std::pair<int, int>> newPos;
    for (auto p : pos) {
        p.first++;
        if(!engine->checkCollision(p)) return;
        newPos.insert(p);
    }
    prevPos = pos;
    pos = newPos;
    prevBase = relBase;
    relBase.first++;
}

void Tetromino::rotate()
{
    bool arrMap[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arrMap[i][j] = 0;
        }
    }
    for (auto p : pos) {
        arrMap[p.second-relBase.second][p.first-relBase.first] = 1;
    }
    std::set<std::pair<int, int>> newPos;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (arrMap[i][j]) {
                int xN = 4 - i - 1;
                int yN = j;
                std::pair<int,int> p(xN + relBase.first, yN + relBase.second);
                if(!engine->checkCollision(p)) return;
                newPos.insert(p);
            }
        }
    }
    prevPos = pos;
    pos = newPos;
}

bool Tetromino::undoMovement() {
    if(undone) return false;
    undone = true;
    relBase = prevBase;
    pos = prevPos;
    return true;
}

TetrisPlayer::TetrisPlayer(std::string name) : score(0), time()
{
    this->name = name;
}

std::string TetrisPlayer::getName() const
{
    return name;
}

int TetrisPlayer::getScore() const
{
    return score;
}

sf::Time TetrisPlayer::getTime() const
{
    return time;
}

void TetrisPlayer::setScore(int score)
{
    this->score = score;
}

void TetrisPlayer::setTime(sf::Time time)
{
    this->time = time;
}

void TetrisPlayer::incrementTime(float& dtAsSeconds)
{
    time += sf::seconds(dtAsSeconds);
}
