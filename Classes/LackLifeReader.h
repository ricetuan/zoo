//
//  LackLifeReader.h
//  Zoo
//
//  Created by Ken Watanabe on 2015/08/11.
//
//

#ifndef __Zoo__LackLifeReader__
#define __Zoo__LackLifeReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class LackLifeReader : public cocostudio::NodeReader {
public:
    static LackLifeReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Zoo__LackLife__) */