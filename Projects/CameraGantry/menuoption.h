#ifndef CAMERAGANTRY_MENUOPTION_H
#define CAMERAGANTRY_MENUOPTION_H

#include <Arduino.h>

class MenuOption {
  public:
    MenuOption(int default_val, String title, String unit);
    inline ~MenuOption() {};

    void save();
    void setDefault();
    void cancel();

    void nextOption();
    void previousOption(); 

    String getTitle();
    String getText();

  private:
    int default_val;
    int current_val;
    int potential_val;
    String title;
    String unit;
};
#endif
