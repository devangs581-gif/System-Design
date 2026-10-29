
#include <bits/stdc++.h>
using namespace std;

class Board;
class BoardEntity;
class Dice;
class Player;
class setUpStrategy;
class Rules;
class Snake;
class Ladder;
class randomSetUp;
class basicSetup;
class customSetUp;

// ==================== BOARD ENTITY ====================

class BoardEntity {
public:
    int st, ed;

    BoardEntity(int st, int ed) {
        this->st = st;
        this->ed = ed;
    }

    virtual void display() = 0;
    virtual int getStart() = 0;
    virtual int getEnd() = 0;

    virtual ~BoardEntity() = default;
};

class Snake : public BoardEntity {
public:
    Snake(int st, int ed) : BoardEntity(st, ed) {}

    void display() override {
        cout << "Snake at - " << st << " -> " << ed << endl;
    }

    int getStart() override {
        return st;
    }

    int getEnd() override {
        return ed;
    }
};

class Ladder : public BoardEntity {
public:
    Ladder(int st, int ed) : BoardEntity(st, ed) {}

    void display() override {
        cout << "Ladder at - " << st << " -> " << ed << endl;
    }

    int getStart() override {
        return st;
    }

    int getEnd() override {
        return ed;
    }
};

// ==================== SETUP STRATEGY ====================

class setUpStrategy {
public:
    virtual void setUp(Board* b) = 0;
    virtual ~setUpStrategy() = default;
};

// ==================== BOARD ====================

class Board {
private:
    int size;
    vector<BoardEntity*> en;
    map<int, BoardEntity*> mp;

public:
    Board(int size) {
        this->size = size;
    }

    int getSize() {
        return size;
    }

    bool canAddEntity(int pos) {
        return mp.count(pos) == 0;
    }

    BoardEntity* getEntity(int pos) {
        auto it = mp.find(pos);

        if (it == mp.end()) {
            return nullptr;
        }

        return it->second;
    }

    void addEntity(BoardEntity* entity) {
        int pos = entity->getStart();

        if (!canAddEntity(pos)) {
            cout << "You can't add entity here: " << pos << endl;
            delete entity;
            return;
        }

        en.push_back(entity);
        mp[pos] = entity;
    }

    void display() {
        cout << "\nBoard entities:\n";

        for (BoardEntity* entity : en) {
            entity->display();
        }
    }

    ~Board() {
        for (BoardEntity* entity : en) {
            delete entity;
        }
    }
};

// ==================== BASIC SETUP ====================

class basicSetup : public setUpStrategy {
public:
    void setUp(Board* b) override {
        if (b->getSize() != 100) {
            cout << "Standard setup only works for a 100-cell board!"
                 << endl;
            return;
        }

        vector<pair<int, int>> snakePos = {
            {15, 5}, {20, 6}, {30, 17},
            {50, 24}, {99, 1}
        };

        vector<pair<int, int>> ladderPos = {
            {8, 28}, {13, 33}, {25, 69}, {87, 100}
        };

        for (auto [x, y] : snakePos) {
            b->addEntity(new Snake(x, y));
        }

        for (auto [x, y] : ladderPos) {
            b->addEntity(new Ladder(x, y));
        }
    }
};

// ==================== DIFFICULTY ====================

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD
};

// ==================== RANDOM SETUP ====================

class randomSetUp : public setUpStrategy {
private:
    Difficulty difficulty;

    void setupWithProbability(Board* b, double snakeProbability) {
        int boardSize = b->getSize();

        if (boardSize <= 10) {
            cout << "Board must have more than 10 cells." << endl;
            return;
        }

        int totalEntities = boardSize / 10;

        for (int i = 0; i < totalEntities; i++) {
            double prob = static_cast<double>(rand()) / RAND_MAX;
            bool added = false;

            if (prob < snakeProbability) {
                // Add a snake.
                for (int attempts = 0; attempts < 50; attempts++) {
                    int start = rand() % (boardSize - 10) + 10;
                    int end = rand() % (start - 1) + 1;

                    if (b->canAddEntity(start)) {
                        b->addEntity(new Snake(start, end));
                        added = true;
                        break;
                    }
                }
            } else {
                // Add a ladder.
                for (int attempts = 0; attempts < 50; attempts++) {
                    int start = rand() % (boardSize - 10) + 1;
                    int end = rand() % (boardSize - start) + start + 1;

                    if (end < boardSize && b->canAddEntity(start)) {
                        b->addEntity(new Ladder(start, end));
                        added = true;
                        break;
                    }
                }
            }

            if (!added) {
                cout << "Could not place an entity after 50 attempts."
                     << endl;
            }
        }
    }

public:
    randomSetUp(Difficulty d) : difficulty(d) {}

    void setUp(Board* b) override {
        switch (difficulty) {
            case Difficulty::EASY:
                setupWithProbability(b, 0.3);
                break;

            case Difficulty::MEDIUM:
                setupWithProbability(b, 0.5);
                break;

            case Difficulty::HARD:
                setupWithProbability(b, 0.7);
                break;
        }
    }
};

// ==================== CUSTOM SETUP ====================

class customSetUp : public setUpStrategy {
private:
    vector<pair<int, int>> snakes;
    vector<pair<int, int>> ladders;

public:
    customSetUp(
        vector<pair<int, int>> snakes,
        vector<pair<int, int>> ladders
    ) {
        this->snakes = snakes;
        this->ladders = ladders;
    }

    void setUp(Board* b) override {
        int size = b->getSize();
        int minDistance = static_cast<int>(sqrt(size));

        for (auto [x, y] : snakes) {
            if (x < 1 || x > size || y < 1 || y >= x ||
                x - y <= minDistance) {
                cout << "Invalid snake: " << x << " -> " << y << endl;
                continue;
            }

            if (!b->canAddEntity(x)) {
                cout << "Snake starting position already occupied: "
                     << x << endl;
                continue;
            }

            b->addEntity(new Snake(x, y));
        }

        for (auto [x, y] : ladders) {
            if (x < 1 || x >= y || y > size ||
                y - x <= minDistance) {
                cout << "Invalid ladder: " << x << " -> " << y << endl;
                continue;
            }

            if (!b->canAddEntity(x)) {
                cout << "Ladder starting position already occupied: "
                     << x << endl;
                continue;
            }

            b->addEntity(new Ladder(x, y));
        }
    }
};

// ==================== DICE ====================

class Dice {
private:
    int numberOfFaces;

public:
    Dice(int numberOfFaces) {
        this->numberOfFaces = numberOfFaces;
    }

    int roll() {
        return (rand() % numberOfFaces) + 1;
    }
};

// ==================== PLAYER ====================

class Player {
private:
    int id;
    string name;
    int pos;

public:
    Player(int id, string name) {
        this->id = id;
        this->name = name;
        this->pos = 0;
    }

    int getPosition() {
        return pos;
    }

    void setPosition(int pos) {
        this->pos = pos;
    }

    string getName() {
        return name;
    }
};

// ==================== RULES ====================

class Rules {
public:
    virtual bool isPlayerWin(int currentPos, int size) = 0;

    virtual int finalPosition(
        int currentPos,
        int diceVal,
        int size,
        Board* board
    ) = 0;

    virtual bool isValidMove(
        int currentPos,
        int diceVal,
        int size
    ) = 0;

    virtual ~Rules() = default;
};

class basicRules : public Rules {
public:
    bool isPlayerWin(int currentPos, int size) override {
        return currentPos == size;
    }

    bool isValidMove(
        int currentPos,
        int diceVal,
        int size
    ) override {
        return currentPos + diceVal <= size;
    }

    int finalPosition(
        int currentPos,
        int diceVal,
        int size,
        Board* board
    ) override {
        if (!isValidMove(currentPos, diceVal, size)) {
            return -1;
        }

        int finalPos = currentPos + diceVal;

        BoardEntity* entity = board->getEntity(finalPos);

        if (entity != nullptr) {
            finalPos = entity->getEnd();
        }

        return finalPos;
    }
};

// ==================== GAME ====================

class Game {
private:
    Board* board;
    Dice* dice;
    Rules* rule;
    deque<Player*> pl;
    bool isGameOver;

public:
    Game(
        int size,
        setUpStrategy* setup,
        int numberOfFaces = 6
    ) {
        isGameOver = false;

        board = new Board(size);
        dice = new Dice(numberOfFaces);
        rule = new basicRules();

        setup->setUp(board);
        delete setup;
    }

    void addPlayer(Player* player) {
        pl.push_back(player);
    }

    void play() {
        if (pl.empty()) {
            cout << "No players added to the game." << endl;
            return;
        }

        while (!isGameOver) {
            cout << "\nPlease press Enter for your turn." << endl;
            cin.get();

            Player* player = pl.front();
            pl.pop_front();
            pl.push_back(player);

            int faceVal = dice->roll();

            cout << player->getName()
                 << " rolled: " << faceVal << endl;

            int finalPos = rule->finalPosition(
                player->getPosition(),
                faceVal,
                board->getSize(),
                board
            );

            if (finalPos != -1) {
                player->setPosition(finalPos);

                cout << player->getName()
                     << " played the move. Final position: "
                     << player->getPosition() << endl;
            } else {
                cout << "Move exceeds the board. Better luck next time!"
                     << endl;
            }

            if (rule->isPlayerWin(
                    player->getPosition(),
                    board->getSize())) {
                cout << player->getName() << " wins!" << endl;
                isGameOver = true;
            }
        }
    }

    ~Game() {
        for (Player* player : pl) {
            delete player;
        }

        delete board;
        delete dice;
        delete rule;
    }
};

// ==================== MAIN ====================

int main() {
    int size = 100;
    int numberOfFaces = 6;

    cout << "Enter board size: ";
    cin >> size;

    int choice;

    cout << "\nSelect board setup:\n";
    cout << "1. Basic setup\n";
    cout << "2. Random setup\n";
    cout << "3. Custom setup\n";
    cout << "Enter choice: ";
    cin >> choice;

    setUpStrategy* setup = nullptr;

    if (choice == 1) {
        setup = new basicSetup();
    }
    else if (choice == 2) {
        int difficulty;

        cout << "\nSelect difficulty:\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "Enter choice: ";
        cin >> difficulty;

        Difficulty d = Difficulty::MEDIUM;

        if (difficulty == 1) {
            d = Difficulty::EASY;
        }
        else if (difficulty == 3) {
            d = Difficulty::HARD;
        }
        else if (difficulty != 2) {
            cout << "Invalid difficulty. Using Medium.\n";
        }

        setup = new randomSetUp(d);
    }
    else if (choice == 3) {
        int snakeCount, ladderCount;

        cout << "Enter number of snakes and ladders: ";
        cin >> snakeCount >> ladderCount;

        if (snakeCount < 0 || ladderCount < 0) {
            cout << "Counts cannot be negative." << endl;
            return 1;
        }

        vector<pair<int, int>> snakes(snakeCount);
        vector<pair<int, int>> ladders(ladderCount);

        cout << "Enter snake start and end positions:\n";
        for (auto& [x, y] : snakes) {
            cin >> x >> y;
        }

        cout << "Enter ladder start and end positions:\n";
        for (auto& [x, y] : ladders) {
            cin >> x >> y;
        }

        setup = new customSetUp(snakes, ladders);
    }
    else {
        cout << "Invalid choice. Using basic setup.\n";
        setup = new basicSetup();
    }

    Game game(size, setup, numberOfFaces);

    game.addPlayer(new Player(1, "Player 1"));
    game.addPlayer(new Player(2, "Player 2"));

    game.play();

    return 0;
}
