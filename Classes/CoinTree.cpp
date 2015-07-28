//
//  CoinTree.cpp
//  Zoo
//
//  Created by Ken Watanabe on 2015/07/27.
//
//

#include "CoinTree.h"
#include "WorldManager.h"

bool CoinTree::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    _timeline = CSLoader::createTimeline("CoinTree.csb");
    // retain the character animation timeline so it doesn't get deallocated
    _timeline->retain();
    _preDropPos = -1;
    _dropCount = 5;
    _isSwaying = false;

    return true;
}

void CoinTree::onEnter()
{
    Node::onEnter();
    _image = getChildByName("image")->getChildByName<Sprite*>("top");

    _dropListNode = getChildByName("dropList");
    _dropPointList = std::vector<cocos2d::Node*>();
    for (auto point : _dropListNode->getChildren()) {
        _dropPointList.push_back(point);
    }

    if (_length) {
        float scale = WorldManager::getInstance()->getImageScale(_image, _length);
        setScale(scale);
    }
}

void CoinTree::setLength(Length* length)
{
    _length = length;
    _dropCoin = MAX(1, (int)length->getLength(UnitOfLength::cm));
    _maxHp = length->getMmLength() * 3;
    _hp = _maxHp;
    if (_image) {
        float scale = WorldManager::getInstance()->getImageScale(_image, _length);
        setScale(scale);
    }
}

void CoinTree::sprout()
{
    stopAllActions();
    runAction(_timeline);
    _timeline->play("sprout", false);
}

void CoinTree::sway()
{
    _isSwaying = true;
    stopAllActions();
    runAction(_timeline);
    _timeline->play("sway", false);
    _timeline->setLastFrameCallFunc([this]{
        _isSwaying = false;
    });
}

void CoinTree::dropCoin()
{
    WorldManager::getInstance()->addCoin(_dropCoin);

    auto dropCoin = CSLoader::createNode("DropCoin.csb");
    int rnd;
    do {
        rnd = rand() % _dropPointList.size();
    } while (_preDropPos == rnd);
    
    _preDropPos = rnd;
    auto dropPoint = _dropPointList[rnd];
    auto position = dropPoint->getPosition() + _dropListNode->getPosition();
    position *= getScale();
    position += getPosition();
    dropCoin->setScale(getScale() * 0.6f);
    dropCoin->setPosition(position);
    getParent()->addChild(dropCoin, 10000);
    dropCoin->getChildByName<ui::TextBMFont*>("text")->setString(StringUtils::format("+%d", _dropCoin));
    
    auto timeline = CSLoader::createTimeline("DropCoin.csb");
    dropCoin->runAction(timeline);
    timeline->play("drop", false);
}

void CoinTree::fellDown()
{
    stopAllActions();
    runAction(_timeline);
    _timeline->play("fall", false);
    
    for (int i = 0; i < 5; i++) {
        runAction(Sequence::create(
            DelayTime::create(0.1 * i),
            CallFunc::create([this]{
                dropCoin();
            }),
            NULL
        ));
    }
}

Rect CoinTree::getBodyRect()
{
    auto imageRect = _image->getBoundingBox();
    imageRect.origin *= getScale();
    imageRect.origin += getPosition();
    imageRect.size = imageRect.size * getScale();
    return imageRect;
}

bool CoinTree::addDamage(float damage)
{
    if (_hp == 0) {
        return false;
    }
    
    for (int i = 1; i < _dropCount; i++) {
        int threshold = int(i * _maxHp / _dropCount);
        if (threshold < _hp && _hp <= threshold + damage) {
            dropCoin();
        }
    }
    
    if (0 < _hp && _hp <= damage) {
        _hp = 0;
        fellDown();
        return true;
    }
    if (_isSwaying == false) {
        sway();
    }
    _hp -= damage;
    return false;
}

void CoinTree::disappear()
{
    if (_hp > 0) {
        stopAllActions();
        runAction(_timeline);
        _timeline->play("disappear", false);
        _timeline->setLastFrameCallFunc([this]{
            removeFromParent();
        });
    } else {
        removeFromParent();
    }
}

bool CoinTree::isDead()
{
    return _hp <= 0;
}

