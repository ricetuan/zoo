//
//  Gacha.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/06/29.
//
//

#ifndef __Zoo__Gacha__
#define __Zoo__Gacha__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CommonInclude.h"

class Gacha : public cocos2d::Node {
public:
    CREATE_FUNC(Gacha);
    bool init() override;
    std::function<void()> finishGachaCallback;

protected:
    void onEnter() override;
    cocostudio::timeline::ActionTimeline* timeline;
    void setupTouchHandling();
};

#endif /* defined(__Zoo__Gacha__) */
