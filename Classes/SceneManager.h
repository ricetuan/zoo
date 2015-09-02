//
//  SceneManager.h
//  Tetrominos
//
//  Created by Ken Watanabe on 2015/07/01.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__

#include "CommonInclude.h"
#include "WorldSceneInterface.h"
#include "Constants.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "NetworkManagerDelegate.h"
#include "NetworkingWrapper.h"
#endif

class MainScene;
class MultiBattleScene;
class TitleScene;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
class SceneManager : NetworkingDelegate {
#else
class SceneManager {
#endif
public:
    static SceneManager* getInstance();
    void enterMainScene();
    void resetMainScene();
    MainScene* getMainScene();
    MultiBattleScene* getMultiBattleScene();
    WorldSceneInterface* getWorldScene();
    void enterMultiBattleScene();
    void backMainScene();
    
    bool isNetwork();
    bool isHost();
    void showPeerList();
    void receiveMultiplayerInvitations();
    void sendData(const void* data, unsigned long length);
    
    void setOpponentUserInfo(std::string name, int userId, double time);
    void sendUserInfo();
    
    std::string getPlayerName();
    std::string getOpponentName();

private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    std::unique_ptr<NetworkingWrapper> networkingWrapper;
#endif
    Scene* _scene;
    bool _isNetwork;
    int _userId;
    double _startTime;
    int _opponentUserId;
    double _opponentStartTime;
    std::string _opponentName;
    void receivedData(const void* data, unsigned long length);
    void stateChanged(ConnectionState state);
    
    
    SceneManager();
    ~SceneManager();
};

#endif /* defined(__Tetrominos__SceneManager__) */
