#pragma once

#ifndef _TALKINGSCENE_H_
#define _TALKINGSCENE_H_
#include<cocos2d.h>
#include"NPC.h"
class TalkingScene : public cocos2d::Layer
{
public:
	virtual bool init();

    void showNextTalking();

    void typewriterEffect(float dt);

    std::string getNextTalking();

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    std::string _talkingText = "Hello\nWorld"; // 对话内容
    std::string NPCimage = "NPC/NPC1.png";

    void ToTalking(NPC::NPCName);//初始化对话

    CREATE_FUNC(TalkingScene);
private:
    cocos2d::Label* _dialogLabel = nullptr; // 对话内容标签
    std::string _currentDialog; // 当前对话
    int _currentDialogIndex = 0; // 当前对话的索引
    int _currentCharIndex = 0; // 当前字符的索引

    static std::pair<int, int>TalkingTime;
};
#endif