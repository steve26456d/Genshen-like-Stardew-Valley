#include"TalkingScene.h"
USING_NS_CC;

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
    _dialogLabel->setWidth(500); // 设置标签的最大宽度
    _dialogLabel->setAlignment(TextHAlignment::LEFT); // 设置文本左对齐
    this->addChild(_dialogLabel);

    // 显示第一句对话
    showNextTalking();

    // 添加键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(TalkingScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void TalkingScene::showNextTalking()
{
    // 检查是否还有对话内容
    if (_currentDialogIndex < _talkingText.length()) {
        // 获取当前对话内容
        std::string currentDialog = getNextTalking();

        // 显示对话内容（逐字显示效果）
        _dialogLabel->setString(""); // 清空标签
        _currentCharIndex = 0;
        this->schedule(SEL_SCHEDULE(&TalkingScene::typewriterEffect), 0.05f);
    }
    else {
        // 对话结束
        CCLOG("对话结束！");
        this->removeFromParent(); // 移除对话层
    }
}

void TalkingScene::typewriterEffect(float dt)
{
    // 逐字显示对话内容
    if (_currentCharIndex < _currentDialog.length()) {
        _dialogLabel->setString(_currentDialog.substr(0, _currentCharIndex + 1));
        _currentCharIndex++;
    }
    else {
        // 停止逐字显示
        this->unschedule(SEL_SCHEDULE(&TalkingScene::typewriterEffect));
    }
}

std::string TalkingScene::getNextTalking()
{
    // 获取下一句对话
    std::string currentDialog = "";
    while (_currentDialogIndex < _talkingText.length()) {
        char c = _talkingText[_currentDialogIndex];
        currentDialog += c;
        _currentDialogIndex++;
        if (c == '\n') {
            break; // 遇到换行符，结束当前对话
        }
    }
    _currentDialog = currentDialog;
    return currentDialog;
}

void TalkingScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 按下任意键显示下一句对话
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) 
    {
        showNextTalking();
    }
}