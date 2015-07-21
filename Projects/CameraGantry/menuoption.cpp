#include "menuoption.h"

MenuOption::MenuOption(int val, String title, String unit) :
  default_val(val),
  current_val(val),
  potential_val(val),
  title(title),
  unit(unit) {
}

void MenuOption::save() {
  current_val = potential_val;
}

void MenuOption::setDefault() {
  current_val = default_val;
  potential_val = default_val;
}

void MenuOption::cancel() {
  potential_val = current_val;
}

String MenuOption::nextOption() {
  potential_val =  (potential_val + 1) % 100; 
  return (String)potential_val + unit;
}

String MenuOption::previousOption() {
  potential_val =  (potential_val - 1) % 100; 
  return (String)potential_val + unit;
}

String MenuOption::getTitle() {
  return title;
}

String MenuOption::getText() {
  if (potential_val == default_val)
    return (String)potential_val + unit + '*';
  else
    return (String)potential_val + unit;
}
