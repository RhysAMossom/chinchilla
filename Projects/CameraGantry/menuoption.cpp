#include "menuoption.h"

MenuOption::MenuOption(int val, String title) :
  default_val(val),
  current_val(val),
  potential_val(val),
  optionTitle(title) {
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
  return "";
}

String MenuOption::previousOption() {
  return "";
}

String MenuOption::getOptionTitle() {
  return optionTitle;
}

String MenuOption::getOptionText() {
  return "";
}
