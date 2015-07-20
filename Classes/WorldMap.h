//
//  WorldMap.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/07/13.
//
//

#ifndef __Zoo__WorldMap__
#define __Zoo__WorldMap__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CommonInclude.h"
#include "WorldManager.h"
class Gacha;
class Animal;

class WorldMap : public cocos2d::Node {
public:
    CREATE_FUNC(WorldMap);
    bool init() override;
    void onEnter() override;
    void update(float dt);
    void initSize(Length* maxWidth, Length* currentWidth);

    Length* getCurrentWidth();
    Length* getMaxWidth();
    void setCurrentWidth(Length* length, std::function<void ()> callback);
    void setGacha(Gacha* gacha);
    Gacha* getGacha();
    bool isMaxScale();

    void releaseAnimal(Animal* animal, std::function<void ()> callback);
    void addAnimalAtRandomPoint(Animal* animal);
    void addAnimal(Animal* animal, Vec2 targetPoint);
    void addEnemyAnimalAtOutRandomPoint(Animal* animal);
    void addEnemyAnimal(Animal* animal, Vec2 targetPoint);
    
    void hideGacha();
    void showGacha();
    
protected:
    Length* _maxWidth;
    Length* _currentWidth;
    Gacha* _gacha;
    std::vector<Animal*> _animalList;
    Vec2 _targetPoint;
    
    int _calcObjectZOrder(Node* node);
    void setupTouchHandling();
    BattleState _checkBattleEnd();

};

#endif /* defined(__Zoo__WorldMap__) */
