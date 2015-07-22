//
//  WorldManager.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/07/02.
//
//

#ifndef __Zoo__WorldManager__
#define __Zoo__WorldManager__

#include "cocos2d.h"
#include "WorldMap.h"
#include "MainScene.h"
#include "CommonInclude.h"
#include "EnemyGenerater.h"
class Gacha;
class Animal;

enum class SceneState {
    Tutorial,
    TutorialBattle,
    TutorialGacha,
    Normal,
    Battle,
    ShowResult,
    
};

class WorldManager : cocos2d::Ref
{
public:
    static WorldManager* getInstance();
    
    // getter, setter
    WorldMap* getMap();
    WorldInfo* getWorldInfo();
    bool enableNextAction();
    void setEnableNextAction(bool enable);
    SceneState getSceneState();
    std::vector<Animal*> getAnimalList();
    std::vector<Animal*> getEnemyAnimalList();

    // game logic
    void lotteryGacha();
    void releaseAnimal(Animal* animal, bool hit);
    WorldInfo* levelup();
    void startTutorial();
    void startBattle();
    void startTutorialBattle();
    void endBattle(bool win, float showResultViewDelay);
    void endBattle(bool win);
    void endResult();
    void resetData();
    
    // util
    float getImageScale(Sprite* image, Length* width);
    float getDisplayLength(Length* length);
    Length* getLength(float displayLength);
    Vec2 getDisplayPoint(Length x, Length y);
    Vec2 getRadomPlace();
    Vec2 getOutRandomPlace();

private:
    int _level;
    bool _enableNextAction;
    int _leftTime;
    WorldInfo* _info;
    WorldMap* _map;
    Gacha* _gacha;
    SceneState _state;
    std::vector<Animal*> _animalList;
    std::vector<Animal*> _enemyAnimalList;
    EnemyGenerater* _enemyGenerater;
    
    WorldInfo* _loadWoldInfo(int level);
    MainScene* _getMainScene();
    void _leftTimeUpdate(float dt);
    void _endBattle();
    void _closeResult();
    void _setCoin(int coin);
    void _setGameActive(bool active);
    void _setLeftTime(int leftTime);
    void _repairAllAnimalHp();
    bool _checkAllEnemyDead();
    void _transitionMap(WorldInfo* preWorldInfo, WorldInfo* newWorldInfo);

    void _startTutrialBattleScene1();
    void _startTutrialBattleScene2();
    void _startTutrialBattleScene3();
    void _startTutrialGachScene1();
    void _startTutrialGachScene2();
    void _startTutrialLevelupScene1();
    void _startTutrialLevelupScene2();

    WorldManager();
    ~WorldManager();

};

#endif /* defined(__Zoo__WorldManager__) */
