//
//  Animal.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/06/29.
//
//

#ifndef __Zoo__Animal__
#define __Zoo__Animal__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CommonInclude.h"
#include "Species.h"

class Animal : public cocos2d::Node {
public:
    Animal();
    static Animal* CreateWithSpeceis(std::string specesName);
    bool initWithSpeceis(std::string specesName);

    void updateWorldScale();
    void jump(Vec2 target, float height);

    float getWorldScale();
    Length* getHeight();
    Length* getSpeed();
    std::string getName();

protected:
    Species* _species;
    cocos2d::Node* _rootNode;
    cocostudio::timeline::ActionTimeline* _timeline;
    std::string _name;
    cocos2d::Sprite* _image;
    Length* _height;
    
    void onEnter() override;
    void _startWalk();
    void _moveNextPoint();
    void _changeAnimalImage();
    
};

#endif /* defined(__Zoo__Animal__) */
