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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    this->networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->networkingWrapper->setDelegate(this);
#endif
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    networkingWrapper->stopAdvertisingAvailability();
#endif
    Director::getInstance()->replaceScene(
        TransitionFade::create(1.0f, _scene, Color3B::BLACK)
    );
}

void SceneManager::backMainScene()
{
    _isNetwork = false;
    _scene = MainScene::createScene();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    networkingWrapper->disconnect();
    networkingWrapper->stopAdvertisingAvailability();
#endif
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    networkingWrapper->showPeerList();
#endif
}

void SceneManager::receiveMultiplayerInvitations()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    networkingWrapper->startAdvertisingAvailability();
#endif
}

void SceneManager::sendData(const void* data, unsigned long length)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    networkingWrapper->sendData(data, length);
#endif
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

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state) {
        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            if (isNetwork() == false) {
                enterMultiBattleScene();
            }
            break;
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not connected");
            if (isNetwork()) {
                WorldManager::getInstance()->disconnectSession();
            }
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            networkingWrapper->disconnect();
#endif
            break;
        default:
            break;
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    auto name = networkingWrapper->getDeviceName();

    _userId = rand();
    _startTime = ZUtil::getTime();
    auto command = CommandGenerater::sendUserInfo(name, _userId);
    CommandGenerater::sendData(command);
#endif
}

std::string SceneManager::getPlayerName()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return networkingWrapper->getDeviceName();
#endif
}

std::string SceneManager::getOpponentName()
{
    return _opponentName;
}

