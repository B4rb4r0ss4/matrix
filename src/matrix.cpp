#include "matrix.h"

#define HEIGHT 1200
#define WIDTH 1800
#define FONT "./mtc.ttf"

// Priv functions

void Matrix::initializer() {
    //Init values window
    srand(time(NULL));
    this->vidMode.height = HEIGHT;
    this->vidMode.width = WIDTH;
    this->window = new sf::RenderWindow(this->vidMode, "Matrix", sf::Style::Titlebar | sf::Style::Close); 
    
    //Init values font
    this->font.loadFromFile(FONT);    
    this->fontSize = 24u;

    //Init dropping code
    this->movTime = 0.2f;
    this->newsGen = 18u;
    for(int i=0; i<100; i+=20) {
        this->genText(i);
    }
    
    //Init timer
    this->timerMax = 100.0f;
    this->timer = 0.0f;
}

int Matrix::Text::randi(const int &a, const int &b) {
    return a + rand() % (b - a + 1);
}

void Matrix::Text::setRandX() {
    this->te.setPosition( this->randi(-10, 1810), -1*this->randi(500, 700));
}

void Matrix::Text::setStr(const int& j) {
    // Generate random code line
    int n = this->randi(this->minStrLen, this->maxStrLen);
    std::string textStr = "";   
    for(int i=0; i<n; i++) {
        textStr+=randi(this->beginner, this->ender);
        textStr+='\n';

    }
    this->te.setString(textStr);
    
    // Set green color and calculated opacity
    this->te.setFillColor(sf::Color(0, 255, 0, 150 - (250/n)*j));        
}

void Matrix::genText(const int& j) {
    /* 
        Generate position of text
        Set Font
        Set Font Size
        Add Code Line to vector
        Draw Code Line
    */

    this->textes.push_back({});
    Text* text = &textes.back();
    text->setRandX();
    text->te.setFont(this->font);
    text->te.setCharacterSize(this->fontSize);
    text->setStr(j);
   
    this->window->draw(text->te);
}


// Constructor & destructor
Matrix::Matrix() {
    this->initializer();
}

Matrix::~Matrix() {
    delete this->window;
}

// Accessors
const bool Matrix::running() const { return this->window->isOpen(); }

// Functions

void Matrix::initEvents() {
    while(this->window->pollEvent(this->eve)) {
            switch (this->eve.type) {
                // close window 
                case sf::Event::Closed:
                    this->window->close();
                    break;

                // handling + & - to change speed or Esc to quit
                case sf::Event::KeyPressed:
                    // Esc
                    if(this->eve.key.code == sf::Keyboard::Escape) {
                        this->window->close();
                    } 
                    // + Add
                    else if(this->eve.key.code == sf::Keyboard::A) {
                        if(this->movTime <= 2) {
                            this->movTime+=0.02f;
                            this->newsGen++;
                        }
                        else std::cout<<"You reached max speed!"<<std::endl;
                    } 
                    // - Subtract
                    else if(this->eve.key.code == sf::Keyboard::Z) {
                        if(this->movTime >= 0.04) {
                            this->movTime-=0.02f;
                            this->newsGen--;
                        }
                        else std::cout<<"You reached min speed!"<<std::endl;
                    }
                    break;
                default:
                    break;
            } 
    }
}

void Matrix::updateMov() {
    for(auto i = this->textes.begin(); i!=this->textes.end();) {
        i->te.move(0, this->movTime);
        if(i->te.getPosition().y > HEIGHT) 
            i = textes.erase(i);
        else {
            window->draw(i->te);
            i++;
        }
    }
}


void Matrix::update() {
    // Init events & prepare window
    this->initEvents();
    this->window->clear(sf::Color(0, 0, 0, 255));
    
    // Update current Code Lines (move them or remove them)
    this->updateMov();
   
    // Update timer
    this->timer+=0.3;
    

    // Add new code lines after reaching time
    if(this->timer > this->timerMax) { 
        for(unsigned int i=2; i<this->newsGen; i++) this->genText(i);
        timer = 0.0f;
    }

    // Display
    this->window->display();
}


