#ifndef CAMERAGANTRY_MENUOPTION_H
#define CAMERAGANTRY_MENUOPTION_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>

class MenuOption {
  public:
    MenuOption(int default_val, const String& title, const String& unit, int min_val, int max_val);
    inline ~MenuOption() {};

    void save();
    void setDefault();
    void cancel();

    void nextOption();
    void previousOption(); 

    inline int getCurrentValue() { return current_val; };
    String getTitle();
    virtual String getText();

  protected:
    int default_val;
    int current_val;
    int potential_val;
    int min_val;
    int max_val;
    String title;
    String unit;
};

class MenuOptionText : public MenuOption {
 public:
  MenuOptionText(int default_val, const String& title, const std::vector<String>& options);
  inline ~MenuOptionText();
  
  bool appendOptionStates;
  
  String getText();
  
 private:
   std::vector<String> options;
   int num_options;
};
  
#endif
