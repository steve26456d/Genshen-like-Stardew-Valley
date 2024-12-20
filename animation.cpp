#include "animation.h"
using namespace cocos2d;

Animate* getanimation(std::string who, std::string animationname, std::string direction,int Framenum,double frametime)
{
	std::string Plistname = who + "/" +who + "-" + animationname + "-" + direction + ".plist";
	std::string Pngname = who + "/"  + who + "-" + animationname + "-" + direction + ".png";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Plistname, Pngname);
    Vector<SpriteFrame*> animFrames;
    for (int i = 0; i < Framenum; ++i) {
        std::string frameName = who + "-" + animationname + "-" + direction+"-" + std::to_string(i) + ".png";
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

        animFrames.pushBack(spriteFrame);

    }
    auto animation = Animation::createWithSpriteFrames(animFrames, frametime);
    auto animate = Animate::create(animation);
    return animate;

}
Sprite* initframe(std::string who, std::string animationname, std::string direction)
{
    std::string Plistname = who + "/" + who + "-" + animationname + "-" + direction + ".plist";
    std::string Pngname = who + "/"+ who + "-" + animationname + "-" + direction + ".png";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Plistname, Pngname);
    std::string frameName = who + "-" + animationname + "-" + direction + "-0" + ".png";
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    return Sprite::createWithSpriteFrame(spriteFrame);
    
}