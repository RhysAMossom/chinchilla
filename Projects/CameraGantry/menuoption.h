#ifndef CAMERAGANTRY_MENUOPTION_HH
#define CAMERAGANTRY_MENUOPTION_HH

#include <Arduino.h>

class MenuOption {
  public:
    MenuOption(int default_val, String title);
    inline ~MenuOption() {};

    void save();
    void setDefault();
    void cancel();

    String nextOption();
    String previousOption(); 

    String getOptionTitle();
    String getOptionText();

  private:
    int default_val;
    int current_val;
    int potential_val;
    String optionTitle;
};
#endif
