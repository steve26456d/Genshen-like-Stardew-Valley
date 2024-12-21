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

    std::string _talkingText = "Hello\nWorld"; // �Ի�����
    std::string NPCimage = "NPC/NPC1.png";

    void ToTalking(NPC::NPCName);//��ʼ���Ի�

    CREATE_FUNC(TalkingScene);
private:
    cocos2d::Label* _dialogLabel = nullptr; // �Ի����ݱ�ǩ
    std::string _currentDialog; // ��ǰ�Ի�
    int _currentDialogIndex = 0; // ��ǰ�Ի�������
    int _currentCharIndex = 0; // ��ǰ�ַ�������

    static std::pair<int, int>TalkingTime;
};
#endif