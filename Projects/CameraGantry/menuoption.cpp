#include "menuoption.h"

MenuOption::MenuOption(int val, const String& title, const String& unit, int min_val, int max_val, int increment) :
  default_val(val),
  current_val(val),
  potential_val(val),
  min_val(min_val),
  max_val(max_val),
  increment(increment),
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
  potential_val += increment;
  if (potential_val > max_val) 
    potential_val = min_val;
}

void MenuOption::previousOption() {
  potential_val -= increment;
  if (potential_val < min_val)
    potential_val = max_val;
}

String MenuOption::getTitle() {
  return title;
}

String MenuOption::getText() {
  String  text = (String)potential_val + unit;
  if (potential_val == default_val)
    text = text + String(" *");
  else if (potential_val == current_val)
    text = text + String(" (set)");
  return text;
}


MenuOptionText::MenuOptionText(int default_val, const String& title, const std::vector<String>& options) :
  MenuOption(default_val, title, "", 0, options.size() - 1, 1),
  options(options),
  appendOptionStates(true),
  num_options(options.size()) {
}

String MenuOptionText::getText() {
  String text = options[potential_val];
  if (appendOptionStates && potential_val == default_val)
    text = text + String(" *");
  if (appendOptionStates && potential_val == current_val)
    text = text + String(" (set)");
  return text;
}
