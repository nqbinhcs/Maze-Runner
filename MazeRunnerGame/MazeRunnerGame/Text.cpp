#include "Text.hpp"

TextShow::TextShow() {

}
TextShow::~TextShow()
{

}
TextShow::TextShow(std::string textS, std::string font, float posX, float posY) {            // constructor -> chuỗi + tên font + vị trí in trên màn hình
    // update text
    setText(textS);
    updateText();

    // update font
    setFont(font);

    // set type
    textT.setCharacterSize(CHRACTER_SIZE);
    setStyleFont(sf::Text::Bold);
    setColor(221, 0, 255);

    // set position
    sf::FloatRect textRect(textT.getLocalBounds());
    textT.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2);
    setPosition(posX, posY);

}
void TextShow::set(std::string textS, std::string font, float posX, float posY) {
    // update text
    setText(textS);
    updateText();

    // update font
    setFont(font);

    // set type
    textT.setCharacterSize(CHRACTER_SIZE);
    setStyleFont(sf::Text::Bold);
    setColor(221, 0, 255);

    // set position
    sf::FloatRect textRect(textT.getLocalBounds());
    textT.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2);
    setPosition(posX, posY);
}
void TextShow::setPosition(float posX, float posY) {         // hàm setter cài đặt vị trí của text
    this->posX = posX;
    this->posY = posY;

    textT.setPosition(this->posX, this->posY);
}
void TextShow::setText(std::string textS) {                  // hàm setter text
    this->textS = textS;

    this->updateText();
}
void TextShow::setFont(std::string font) {                   // hàm setter font
    if (!this->font.loadFromFile(std::string("res/fnt/") + font))
    {
        std::cout << "Load font failed" << std::endl;
    }

    textT.setFont(this->font);
}
void TextShow::setStyleFont(int style) {                     // hàm settter style
    this->textT.setStyle(style);
}
void TextShow::setColor(unsigned short red, unsigned short green, unsigned short blue) { // hàm setter cài đặt màu theo mã (RGB)
    sf::Color color(red, green, blue);
    this->textT.setFillColor(color);
}
void TextShow::updateText() {                                // cập nhật text đã cài
    this->textT.setString(this->textS);
}
void TextShow::drawText(sf::RenderWindow& window) {         // vẽ text lên window
    // Draw it
    window.draw(textT);
}
void TextShow::scale(float scaleSize) {                      // thay đổi kích thước chữ theo độ co giãn
    this->textT.setCharacterSize(scaleSize * CHRACTER_SIZE);
}
void TextShow::setSize(float size) {                         // thay đổi kích thước chữ theo kích thước
    this->textT.setCharacterSize(size);
}

float TextShow::getSizeText() {                              // trả về độ dài của text
    return this->textT.getCharacterSize() * this->textS.length();
}
float TextShow::getSizeCharacter() {                         // trả về kích thước của 1 ký tự
    return this->textT.getCharacterSize();
}
float TextShow::getheight() {
    return this->textT.getGlobalBounds().height;
}
float TextShow::getBottom() {
    sf::FloatRect textRect(this->textT.getGlobalBounds());
    return textRect.top + textRect.height;
}

short TextShow::lengthText() {                               // trả về độ dài chuỗi
    return this->textS.length();
}
float TextShow::getPositionX() {                             // trả về vị trí của text theo X
    return this->posX;
}
float TextShow::getPositionY() {                             // trả về vị trí của text theo Y
    return this->posY;
}

void TextShow::setOriginToMidHead() {
    sf::FloatRect textRect(this->textT.getLocalBounds());

    this->textT.setOrigin(textRect.left, textRect.top + textRect.height / 2);
}
void TextShow::setOriginToTopHead() {
    sf::FloatRect textRect(this->textT.getLocalBounds());

    this->textT.setOrigin(textRect.left, textRect.top);
}
void TextShow::setOriginToMidle() {
    sf::FloatRect textRect(this->textT.getLocalBounds());

    this->textT.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}
void TextShow::setOriginToMidTop() {
    sf::FloatRect textRect(this->textT.getLocalBounds());

    this->textT.setOrigin(textRect.left + textRect.width / 2, textRect.top);
}