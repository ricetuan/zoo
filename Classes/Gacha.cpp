//
//  Gacha.cpp
//  Zoo
//
//  Created by Ken Watanabe on 2015/06/29.
//
//

#include "Gacha.h"
#include "WorldManager.h"
#include "Animal.h"


bool Gacha::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    _timeline = CSLoader::createTimeline("Gacha.csb");
    // retain the character animation timeline so it doesn't get deallocated
    _timeline->retain();
    
    std::srand((int)time(NULL));
    
    return true;
}

void Gacha::onEnter()
{
    Node::onEnter();
    this->setupTouchHandling();
}

float Gacha::getGachaHeight()
{
    auto image = this->getChildByName<Sprite*>("image");
    return image->getContentSize().height * getScale();
}

void Gacha::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto image = this->getChildByName<Sprite*>("image");
        Rect targetBox = image->getBoundingBox();
        targetBox.origin = image->convertToWorldSpaceAR(targetBox.origin);
     
        Point location = touch->getLocationInView();
        auto touchLocation = Director::getInstance()->convertToGL(location);
        
     
        //touchPointがtargetBoxの中に含まれているか判定
        if (targetBox.containsPoint(touchLocation))
        {
            this->lotteryGacha();
        }
        return true;
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Gacha::lotteryGacha()
{
    if (WorldManager::getInstance()->enableNextAction() == false) {
        return;
    }
    WorldManager::getInstance()->setEnableNextAction(false);
    
    int gachaId = WorldManager::getInstance()->getGachaId();
    std::vector<float> probabilityList;
    std::vector<std::string> rewardList;
    std::vector<bool> hitList;

    auto jsonStr = FileUtils::getInstance()->getStringFromFile("data/gacha.json");
    rapidjson::Document document;
    document.Parse<0>(jsonStr.c_str());
    rapidjson::Value& gachaDoc = document[std::to_string(gachaId).c_str()];
    float total = 0;
    for (int i = 0; i < gachaDoc.Size(); i++) {
        rapidjson::Value& v = gachaDoc[i];
        float p = v["probability"].GetDouble();
        total += p;
        probabilityList.push_back(p);
        rewardList.push_back(v["reward"].GetString());
        if (v["hit"].IsNull()) {
            hitList.push_back(false);
        } else {
            hitList.push_back(v["hit"].GetBool());
        }
    }
    
    float rnd = total * rand_0_1();
    float lot = 0;
    bool isHit = false;
    std::string animalStr;
    for (int i = 0; i < probabilityList.size(); i++) {
        lot += probabilityList[i];
        if (rnd < lot) {
            animalStr = rewardList[i];
            isHit = hitList[i];
            break;
        }
    }
    
    std::string animationName = (isHit) ? "gacha1" : "gacha2";

    this->stopAllActions();
    this->runAction(_timeline);
    _timeline->play(animationName, false);
    auto animationInfo = _timeline->getAnimationInfo(animationName);
    float durationTime = (animationInfo.endIndex - animationInfo.startIndex) / (_timeline->getTimeSpeed() * GAME_FPS);
    this->runAction(Sequence::create(
        DelayTime::create(durationTime - 0.1f),
        CallFunc::create([this, animalStr, isHit](){
            auto animal = Animal::CreateWithSpeceis(animalStr);
            animal->setTag((int)MainSceneTag::Animal);
            WorldManager::getInstance()->releaseAnimal(animal);
            if (isHit) {
                WorldManager::getInstance()->levelup();
            } else {
                WorldManager::getInstance()->setEnableNextAction(true);
            }
        }),
        NULL
    ));
}