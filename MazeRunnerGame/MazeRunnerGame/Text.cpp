#include "Text.hpp"

MyText::MyText() {
    // update text
    setContent("");
    updateContent();

    // setText type
    setCharacterSize(12);
    setTextColor(sf::Color::Black);

    // set bound
    updateBound();
}

MyText::~MyText(){

}

MyText::MyText(std::string text, std::string font, float size, sf::Uint32 style, sf::Color color) {            // constructor -> chuỗi + tên m_Font + vị trí in trên màn hình
    setText(text, font, size, style, color);
}

void MyText::setText(std::string text, std::string font, float size, sf::Uint32 style, sf::Color color) {
    // update m_Font
    setFont(font);

    // update text
    setContent(text);

    // setText type
    setCharacterSize(size);
    setStyleFont(style);
    setTextColor(color);

    // set bound
    updateBound();
}

void MyText::setTextPosition(float posX, float posY) {         // hàm setter cài đặt vị trí của text
    m_sfText.setPosition(posX, posY);
}

void MyText::setContent(std::string m_strText) {                  // hàm setter text
    this->m_strText = m_strText;

    this->updateContent();

    // update bound
    updateBound();
}
void MyText::setFont(std::string font) {                   // hàm setter m_Font
    if (!this->m_Font.loadFromFile(font))
    {
        std::cout << "Load m_Font failed" << std::endl;
    }
    else
        std::cout << "Load m_Font successfully" << std::endl;

    m_sfText.setFont(this->m_Font);
}
void MyText::setStyleFont(sf::Uint32 style) {                     // hàm settter style
    this->m_sfText.setStyle(style);
}

void MyText::setTextColor(sf::Color color) { // hàm setter cài đặt màu theo mã (RGB)
    this->m_sfText.setFillColor(color);
}

void MyText::updateContent() {                                // cập nhật text đã cài
    this->m_sfText.setString(sf::String(this->m_strText));
}

void MyText::scaleText(float scaleSize) {                      // thay đổi kích thước chữ theo độ co giãn
    this->m_sfText.setScale(sf::Vector2f(scaleSize, scaleSize));
}

void MyText::setCharacterSize(float size) {                         // thay đổi kích thước chữ theo kích thước
    this->m_sfText.setCharacterSize(size);
}

void MyText::setCharacterSpacing(float space) {
    this->m_sfText.setLetterSpacing(space);
}

float MyText::getTextSize() {                              // trả về độ dài của text
    return this->m_sfText.getCharacterSize() * this->m_strText.length();
}

float MyText::getCharacterSize() {                         // trả về kích thước của 1 ký tự
    return this->m_sfText.getCharacterSize();
}

float MyText::getTextHeight() {
    return this->m_sfText.getGlobalBounds().height;
}

float MyText::getTextBottom() {
    sf::FloatRect textRect(this->m_sfText.getGlobalBounds());
    return textRect.top + textRect.height;
}

short MyText::getTextLength() {                               // trả về độ dài chuỗi
    return this->m_strText.length();
}

float MyText::getTextPositionX() {                             // trả về vị trí của text theo X
    return this->m_sfText.getPosition().x;
}

float MyText::getTextPositionY() {                             // trả về vị trí của text theo Y
    return this->m_sfText.getPosition().y;
}

void MyText::setTextOriginToLeft() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(textRect.left, m_sfText.getOrigin().y);
}

void MyText::setTextOriginToCenter() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(textRect.left + textRect.width / 2, m_sfText.getOrigin().y);
}

void MyText::setTextOriginToRight() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(textRect.left + textRect.width, m_sfText.getOrigin().y);
}

void MyText::setTextOriginToTop() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(m_sfText.getOrigin().x, textRect.top);
}

void MyText::setTextOriginToMiddle() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(m_sfText.getOrigin().x, textRect.top + textRect.height / 2);
}

void MyText::setTextOriginToBottom() {
    sf::FloatRect textRect(this->m_sfText.getLocalBounds());

    this->m_sfText.setOrigin(m_sfText.getOrigin().x, textRect.top + textRect.height);
}

void MyText::setBox(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor) {
    setBoxSize(size);
    setBoxFillColor(fillColor);
    setBoxOutlineColor(outlineColor);
    
    setBoxOriginToCenter();
    setBoxOriginToMiddle();
    setBoxPosition(position);

}

void MyText::setBoxPosition(sf::Vector2f position) {
    m_Box.setPosition(position);
}

void MyText::setBoxSize(sf::Vector2f size) {
    m_Box.setSize(size);

    // update bound
    updateBound();
}

void MyText::setBoxFillColor(sf::Color color) {
    m_Box.setFillColor(color);
}

void MyText::setBoxOutlineColor(sf::Color color) {
    m_Box.setOutlineColor(color);
}

void MyText::setBoxOutlineThickness(float thickness) {
    m_Box.setOutlineThickness(thickness);
}

void MyText::scaleBox(float scaleSize)
{
    m_Box.setScale(scaleSize, scaleSize);   
}

void MyText::setBoxOriginToLeft() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());
  
    this->m_Box.setOrigin(boxRect.left, m_Box.getOrigin().y);
}

void MyText::setBoxOriginToCenter() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());

    this->m_Box.setOrigin(boxRect.left + boxRect.width / 2, m_Box.getOrigin().y);
}

void MyText::setBoxOriginToRight() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());

    this->m_Box.setOrigin(boxRect.left + boxRect.width, m_Box.getOrigin().y);
}

void MyText::setBoxOriginToTop() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());

    this->m_Box.setOrigin(m_Box.getOrigin().x, boxRect.top);
}

void MyText::setBoxOriginToMiddle() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());

    this->m_Box.setOrigin(m_Box.getOrigin().x, boxRect.top + boxRect.height / 2);
}

void MyText::setBoxOriginToBottom() {
    sf::FloatRect boxRect(this->m_Box.getLocalBounds());

    this->m_Box.setOrigin(m_Box.getOrigin().x, boxRect.top + boxRect.height);
}

void MyText::alignTextLeft(){
    setTextOriginToLeft();
    setTextPosition(m_Box.getGlobalBounds().left, getTextPositionY());
}

void MyText::alignTextCenter(){
    setTextOriginToCenter();
    setTextPosition(m_Box.getGlobalBounds().left + m_Box.getSize().x / 2, getTextPositionY());
}

void MyText::alignTextRight(){
    setTextOriginToRight();
    setTextPosition(m_Box.getGlobalBounds().left + m_Box.getSize().x, getTextPositionY());
}

void MyText::alignTextTop(){
    setTextOriginToTop();
    setTextPosition(getTextPositionX(), m_Box.getGlobalBounds().top);
}

void MyText::alignTextMiddle(){
    setTextOriginToMiddle();
    setTextPosition(getTextPositionX(), m_Box.getGlobalBounds().top + m_Box.getSize().y / 2);
}

void MyText::alignTextBottom(){
    setTextOriginToBottom();
    setTextPosition(getTextPositionX(), m_Box.getGlobalBounds().top + m_Box.getSize().y);
}

void MyText::alignBoxLeft() {
    setBoxOriginToLeft();
    setBoxPosition(sf::Vector2f(0, m_Box.getPosition().y));
}

void MyText::alignBoxCenter() {
    setBoxOriginToCenter();
    setBoxPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, m_Box.getPosition().y));
}

void MyText::alignBoxRight() {
    setBoxOriginToRight();
    setBoxPosition(sf::Vector2f(SCREEN_WIDTH, m_Box.getPosition().y));
}

void MyText::alignBoxTop() {
    setBoxOriginToTop();
    setBoxPosition(sf::Vector2f(m_Box.getPosition().x, 0));
}

void MyText::alignBoxMiddle() {
    setBoxOriginToMiddle();
    setBoxPosition(sf::Vector2f(m_Box.getPosition().x, SCREEN_HEIGHT / 2.f));
}

void MyText::alignBoxBottom() {
    setBoxOriginToBottom();
    setBoxPosition(sf::Vector2f(m_Box.getPosition().x, SCREEN_HEIGHT));
}
void MyText::updateBound()
{
    sf::FloatRect textBound(m_sfText.getGlobalBounds());
    sf::FloatRect rectBound(m_Box.getGlobalBounds());

    if (rectBound.height <= textBound.height && rectBound.width <= rectBound.height)
        m_Bound = textBound;
    else
        m_Bound = rectBound;
}

void MyText::rotate(float angle) {
    m_sfText.setRotation(angle);
    m_Box.setRotation(angle);
}

void MyText::scale(float scaleSize)
{
    scaleText(scaleSize);
    scaleBox(scaleSize);
    updateBound();
}

void MyText::drawMyText(sf::RenderTarget& window) {         // vẽ text lên window
    // Draw it
    window.draw(m_Box);
    window.draw(m_sfText);

}