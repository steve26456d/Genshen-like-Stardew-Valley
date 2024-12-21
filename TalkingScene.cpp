#include"TalkingScene.h"
USING_NS_CC;

std::pair<int, int> TalkingScene::TalkingTime = {0 , 0};
bool TalkingScene::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto dialogBackground = Sprite::create("Talking/Talking_Background.png");
    dialogBackground->setContentSize(Size(visibleSize.width, visibleSize.height / 3));
    dialogBackground->setPosition(Vec2(visibleSize.width / 2,origin.y + dialogBackground->getContentSize().height / 2));
    this->addChild(dialogBackground);

    auto characterAvatar = Sprite::create(NPCimage);
    characterAvatar->setScale(2.0f);
    characterAvatar->setPosition(Vec2(origin.x + characterAvatar->getContentSize().width, dialogBackground->getContentSize().height + characterAvatar->getContentSize().height + origin.y));
    this->addChild(characterAvatar);

    _dialogLabel = Label::createWithTTF("", "fonts/arial.ttf", 100);
    _dialogLabel->setTextColor(Color4B::BLACK);
    _dialogLabel->setPosition(dialogBackground->getPosition());
    _dialogLabel->setWidth(500); // ���ñ�ǩ��������
    _dialogLabel->setAlignment(TextHAlignment::LEFT); // �����ı������
    this->addChild(_dialogLabel);

    // ��ʾ��һ��Ի�
    showNextTalking();

    // ���Ӽ����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(TalkingScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void TalkingScene::showNextTalking()
{
    // ����Ƿ��жԻ�����
    if (_currentDialogIndex < _talkingText.length()) {
        // ��ȡ��ǰ�Ի�����
        std::string currentDialog = getNextTalking();

        // ��ʾ�Ի����ݣ�������ʾЧ����
        _dialogLabel->setString(""); // ��ձ�ǩ
        _currentCharIndex = 0;
        this->schedule(SEL_SCHEDULE(&TalkingScene::typewriterEffect), 0.05f);
    }
    else {
        // �Ի�����
        CCLOG("�Ի�������");
        this->removeFromParent(); // �Ƴ��Ի���
    }
}

void TalkingScene::typewriterEffect(float dt)
{
    // ������ʾ�Ի�����
    if (_currentCharIndex < _currentDialog.length()) {
        _dialogLabel->setString(_currentDialog.substr(0, _currentCharIndex + 1));
        _currentCharIndex++;
    }
    else {
        // ֹͣ������ʾ
        this->unschedule(SEL_SCHEDULE(&TalkingScene::typewriterEffect));
    }
}

std::string TalkingScene::getNextTalking()
{
    // ��ȡ��һ��Ի�
    std::string currentDialog = "";
    while (_currentDialogIndex < _talkingText.length()) {
        char c = _talkingText[_currentDialogIndex];
        currentDialog += c;
        _currentDialogIndex++;
        if (c == '\n') {
            break; // �������з���������ǰ�Ի�
        }
    }
    _currentDialog = currentDialog;
    return currentDialog;
}

void TalkingScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // �����������ʾ��һ��Ի�
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) 
    {
        showNextTalking();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        this->removeFromParent();
    }
}

void TalkingScene::ToTalking(NPC::NPCName name)
{
    switch (name)
    {
        case NPC::NPCName::L:
        {
            switch (TalkingScene::TalkingTime.first)
            {
                case 0:
                {
                    _talkingText = "Hello\nNice to meet you\nMy Name Is L\n";
                }
                break;
            }
        }
        break;
        case NPC::NPCName::M:
        {
            switch (TalkingScene::TalkingTime.second)
            {
                case 0:
                {
                    _talkingText = "Hello\nNice to meet you\nMy Name Is M\n";
                }
                break;
            }
        }
        break;
    }
}