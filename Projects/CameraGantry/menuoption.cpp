#include "menuoption.h"

MenuOption::MenuOption(int val, const String& title, const String& unit, int min_val, int max_val) :
  default_val(val),
  current_val(val),
  potential_val(val),
  min_val(min_val),
  max_val(max_val),
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

void MenuOption::nextOption() {
  if (++potential_val > max_val) 
    potential_val = min_val;
}

void MenuOption::previousOption() {
  if (--potential_val < min_val)
    potential_val = max_val;
}

String MenuOption::getTitle() {
  return title;
}

String MenuOption::getText() {
  if (potential_val == default_val)
    return (String)potential_val + unit + String(" *");
  else if (potential_val == current_val)
    return (String)potential_val + unit + String(" (saved)");
  else
    return (String)potential_val + unit;
}


MenuOptionText::MenuOptionText(int default_val, const String& title, const std::vector<String>& options) :
  MenuOption(default_val, title, "", 0, options.size() - 1),
  options(options),
  appendOptionStates(true),
  num_options(options.size()) {
}

String MenuOptionText::getText() {
  if (appendOptionStates && potential_val == default_val)
    return options[potential_val] + String(" *");
  else if (appendOptionStates && potential_val == current_val)
    return options[potential_val] + String(" (saved)");
  else
    return options[potential_val];
}
