#include "MainGame.h"
#include "Sprite.h"
#include <iostream>
#include <string>

void fatalError(std::string errorString){
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to exit" << std::endl;
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
};

MainGame::MainGame(){
    _window = nullptr;
    _screenWidth = 640;
    _screenHeight = 480;
    _gameState = GameState::PLAY;
};
MainGame::~MainGame(){
    
};
void MainGame::run(){
    initSystems();
    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
    gameLoop();

}
void MainGame::initSystems(){
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    
    if (_window == nullptr){
        fatalError("SDL window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL glcontext could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK){
        fatalError("Could not be init GLEW!");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
};

void MainGame::gameLoop(){
    while (_gameState != GameState::EXIT){
        processInput();
        drawGame();
    }
};

void MainGame::processInput(){
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)){
        switch (evnt.type)
        {
            case  SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
            default:
                break;
        }
    }  
};

void MainGame::drawGame(){
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _sprite.draw();

    SDL_GL_SwapWindow(_window);
};