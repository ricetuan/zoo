//
//  UserData.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/07/14.
//
//

#ifndef __zoo__UserData__
#define __zoo__UserData__

#include <stdio.h>
#include "cocos2d.h"
#include "Constants.h"
USING_NS_CC;

class UserData {
public:
    bool init();
    bool save();
    static UserData* load();
    
    bool isEndTutorial();
    int getWorldLevel();
    int getCoin();
    ValueMap getLifeData();
    ValueVector getAnimalList();
    LanguageType getLanguage();

    void setEndTutorial(bool endTutorial);
    void setWorldLevel(int level);
    void setCoin(int coin);
    void setLifeData(ValueMap lifeData);
    void setAnimalList(ValueVector animal);
    void setLanguage(LanguageType language);

    
private:
    static std::string getFilePath();
    ValueMap _data;
};



#endif /* defined(__zoo__UserData__) */
