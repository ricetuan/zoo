//
//  NoticeLayer.cpp
//  Zoo
//
//  Created by Ken Watanabe on 2015/07/18.
//
//

#include "NoticeLayer.h"
#include "SoundManager.h"
#include "WorldManager.h"

NoticeLayer::NoticeLayer()
{
    
}

NoticeLayer::~NoticeLayer()
{
    
}

NoticeLayer* NoticeLayer::createWithMessage(std::string message)
{
    NoticeLayer* noticeLayer = new(std::nothrow) NoticeLayer();
    if (noticeLayer && noticeLayer->initWithMessage(message))
    {
        noticeLayer->autorelease();
        return noticeLayer;
    }
    
    CC_SAFE_DELETE(noticeLayer);
    return nullptr;
}

bool NoticeLayer::initWithMessage(std::string message)
{
    int height = 400;

    if (!ModalLayer::initWithHeight(height)) {
        return false;
    }
    
    this->setCascadeOpacityEnabled(true);
    
    auto displaySize = Director::getInstance()->getVisibleSize();
    auto node = CSLoader::createNode("Notice.csb");
    node->setAnchorPoint(Vec2(0.5f, 0.5f));
    node->setPosition(Vec2::ZERO);
    node->setPosition(Vec2(displaySize.width / 2, displaySize.height / 2));
    node->setCascadeOpacityEnabled(true);
    node->setOpacity(255);
    addChild(node, 10);
    
    auto messageLabel = dynamic_cast<ui::Text*>(node->getChildByName("noticeMessage"));
    messageLabel->setString(message);

    auto button = node->getChildByName<ui::Button*>("okButton");
    button->addTouchEventListener(CC_CALLBACK_2(NoticeLayer::_pushButton, this));

    return true;
}

void NoticeLayer::onEnter()
{
    Layer::onEnter();
}

void NoticeLayer::_pushButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    this->runAction(Sequence::create(
        FadeOut::create(0.3f),
        CallFunc::create([this]{
            if (closeNoticeCallback) {
                closeNoticeCallback();
            }
        }),
        RemoveSelf::create(),
        NULL
    ));
}