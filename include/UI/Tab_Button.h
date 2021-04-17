#ifndef TAB_BUTTON_H
#define TAB_BUTTON_H


#include <UI\Button.h>
#include <vector>
#include <memory>

class Tab_Button : public Button, public std::enable_shared_from_this<Tab_Button>
{
private:
    /* data */
public:
    Tab_Button();
    ~Tab_Button();
    bool addButton(std::shared_ptr<Button> new_button);
    bool sortButtons();
    virtual bool onclick();
    virtual bool draw_tab();
    virtual bool update();
    virtual bool click_tab(int px,int py);
protected:
    std::vector<std::shared_ptr<Button>> submenu;
};

#endif // BUTTON_H