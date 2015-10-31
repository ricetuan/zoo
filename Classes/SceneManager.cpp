//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Ken Watanabe on 2015/07/01.
//
//

#include "SceneManager.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "MultiBattleScene.h"
#include "SoundManager.h"
#include "CommandGenerater.h"
#include "WorldManager.h"
using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

static SceneManager* _instance = nullptr;
SceneManager* SceneManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new (std::nothrow)SceneManager();
    }
    return _instance;
}

SceneManager::SceneManager()
{
    _scene = NULL;
    _isNetwork = false;
    _userId = 0;
    _opponentUserId = 0;
}

SceneManager::~SceneManager()
{
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterMainScene()
{
    _scene = MainScene::createScene();
    Director::getInstance()->replaceScene(
        TransitionPageTurn::create(0.6f, _scene, false)
    );
}

void SceneManager::resetMainScene()
{
    _scene = MainScene::createScene();
    Director::getInstance()->replaceScene(
        TransitionFade::create(1.0f, _scene, Color3B::BLACK)
    );
}

MainScene* SceneManager::getMainScene()
{
    if (_scene) {
        return dynamic_cast<MainScene*>(_scene->getChildByName("world scene"));
    } else {
        return NULL;
    }
}

MultiBattleScene* SceneManager::getMultiBattleScene()
{
    if (_scene) {
        return dynamic_cast<MultiBattleScene*>(_scene->getChildByName("world scene"));
    } else {
        return NULL;
    }
}

WorldSceneInterface* SceneManager::getWorldScene()
{
    if (_scene) {
        return dynamic_cast<WorldSceneInterface*>(_scene->getChildByName("world scene"));
    } else {
        return NULL;
    }
}

void SceneManager::enterMultiBattleScene()
{
    _isNetwork = true;
    _scene = MultiBattleScene::createScene();
    sendUserInfo();
    Director::getInstance()->replaceScene(
        TransitionFade::create(1.0f, _scene, Color3B::BLACK)
    );
}

void SceneManager::backMainScene()
{
    _isNetwork = false;
    _scene = MainScene::createScene();
    Director::getInstance()->replaceScene(
        TransitionFade::create(1.0f, _scene, Color3B::BLACK)
    );
}

#pragma - network

bool SceneManager::isNetwork()
{
    return _isNetwork;
}

bool SceneManager::isHost()
{
    if (_userId > _opponentUserId) {
        return true;
    } else {
        return false;
    }
}

void SceneManager::showPeerList()
{
   
}

void SceneManager::receiveMultiplayerInvitations()
{
  
}

void SceneManager::sendData(const void* data, unsigned long length)
{

    // FOR DEBUG
//    receivedData(data, length);
}

void SceneManager::receivedData(const void* data, unsigned long length)
{
    auto multiplayScene = getMultiBattleScene();
    if (multiplayScene) {
        const char* cstr = reinterpret_cast<const char*>(data);
        std::string json = std::string(cstr, length);
        CommandGenerater::excCommand(json);
    }
}

void SceneManager::setOpponentUserInfo(std::string name, int userId, double time)
{
    _opponentName = name;
    _opponentUserId = userId;
    _opponentStartTime = time;
    
    CCLOG("player time = %f, opponent time = %f", _startTime, _opponentStartTime);
    CCLOG("diff time = %f", _startTime - _opponentStartTime);
}

void SceneManager::sendUserInfo()
{

}

std::string SceneManager::getPlayerName()
{

}

std::string SceneManager::getOpponentName()
{
    return _opponentName;
}

