#include "../s21_3d_viewer.h"

// VALIDATION RULES
bool generalInputRules(InputText *input, char ch) {
  bool updated = false;
  size_t size = strlen(input->text);
  if (size < INPUT_MAX) {
    if (ch == '.') {
      int ban = 0;
      if (size == 0) {
        ban = 1;
      }
      for (size_t i = 0; i < size; i++) {
        if (input->text[i] == '.') {
          ban = 1;
        }
      }
      if (ban == 0) {
        strncat(input->text, &ch, 1);
        updated = true;
      }
    }
    if (ch != '.') {
      if (size == 1 && input->text[0] == '0') {
        input->text[0] = '\0';
      }
      strncat(input->text, &ch, 1);
      updated = true;
    }
  }
  return updated;
}

bool doubleInputRules(InputText *input, char ch) {
  int updated = false;
  size_t size = strlen(input->text);
  if (size < INPUT_MAX) {
    if (ch == '-') {
      if (size == 0) {
        strncat(input->text, &ch, 1);
        updated = true;
      } else if (size == 1 && input->text[0] == '0') {
        input->text[0] = '\0';
        strncat(input->text, &ch, 1);
        updated = true;
      }
    }
    if (ch == '.') {
      int ban = 0;
      if (size == 0) {
        ban = 1;
      }
      for (size_t i = 0; i < size; i++) {
        if (input->text[i] == '.') {
          ban = 1;
          break;
        }
      }
      if (ban == 0) {
        strncat(input->text, &ch, 1);
        updated = true;
      }
    }
    if (ch != '.' && ch != '-') {
      int ban = 0;
      for (size_t i = 0; i < size; i++) {
        if (input->text[i] == '.') {
          if ((size - (i + 1)) >= 16) {  // 16 digits after comma
            ban = 1;
          }
          break;
        }
      }
      if (ban == 0) {
        if (size == 1 && input->text[0] == '0') {
          input->text[0] = '\0';
        }
        strncat(input->text, &ch, 1);
        updated = true;
      }
    }
  }
  return updated;
}

void UpdateInputText(int currentInputText, App *app, InputText *input, char ch) {
  (void)app;
  if (currentInputText == input->type) {
    if (input->category == DOUBLE_NUMBER_INPUT) {
      input->updated = doubleInputRules(input, ch);
    } else {
      input->updated = generalInputRules(input, ch);
    }
  }
}

void increaseInputTextValue(int currentInputText, InputText *input, double increase) {
  if (currentInputText == input->type) {
    double newValue = GetDoubleValueFromInputText(*input) + increase;
    char newValue_str[128] = "\0";
    sprintf(newValue_str, "%lf", newValue);
    input->text[0] = '\0';
    strcat(input->text, newValue_str);
    input->updated = true;
    WaitTime(0.1);
  }
}

void decreaseInputTextValue(int currentInputText, InputText *input, double decrease) {
  if (currentInputText == input->type) {
    double newValue = GetDoubleValueFromInputText(*input) - decrease;
    char newValue_str[128] = "\0";
    sprintf(newValue_str, "%lf", newValue);
    input->text[0] = '\0';
    strcat(input->text, newValue_str);
    input->updated = true;
    WaitTime(0.1);
  }
}


void HandleKeys(App *app, InputText *input, int currentInputText) {
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyPressed(KEY_COMMA) == true || IsKeyPressed(KEY_KP_DECIMAL) == true || IsKeyPressed(KEY_PERIOD) == true))
    UpdateInputText(currentInputText, app, input, '.');
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyPressed(KEY_MINUS) == true))
    UpdateInputText(currentInputText, app, input, '-');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_ZERO) == true || IsKeyPressed(KEY_KP_0) == true))
    UpdateInputText(currentInputText, app, input, '0');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_ONE) == true || IsKeyPressed(KEY_KP_1) == true))
    UpdateInputText(currentInputText, app, input, '1');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_TWO) == true || IsKeyPressed(KEY_KP_2) == true))
    UpdateInputText(currentInputText, app, input, '2');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_THREE) == true || IsKeyPressed(KEY_KP_3) == true))
    UpdateInputText(currentInputText, app, input, '3');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_FOUR) == true || IsKeyPressed(KEY_KP_4) == true))
    UpdateInputText(currentInputText, app, input, '4');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_FIVE) == true || IsKeyPressed(KEY_KP_5) == true))
    UpdateInputText(currentInputText, app, input, '5');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_SIX) == true || IsKeyPressed(KEY_KP_6) == true))
    UpdateInputText(currentInputText, app, input, '6');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_SEVEN) == true || IsKeyPressed(KEY_KP_7) == true))
    UpdateInputText(currentInputText, app, input, '7');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_EIGHT) == true || IsKeyPressed(KEY_KP_8) == true))
    UpdateInputText(currentInputText, app, input, '8');
  if ((SHIFT_NOT_PRESSED == true) &&
      (IsKeyPressed(KEY_NINE) == true || IsKeyPressed(KEY_KP_9) == true))
    UpdateInputText(currentInputText, app, input, '9');
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyPressed(KEY_BACKSPACE) == true))
    RemoveLastCharFromInputText(currentInputText, input);
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyPressed(KEY_ESCAPE) == true))
    CleanInputText(currentInputText, input);
  
  // INCREASE VALUE
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyDown(KEY_UP) == true) && (IsKeyUp(KEY_UP) == false))
    increaseInputTextValue(currentInputText, input, 0.01);
  if ((SHIFT_PRESSED == true) && (IsKeyDown(KEY_UP) == true) && (IsKeyUp(KEY_UP) == false))
    increaseInputTextValue(currentInputText, input, 0.1);
  if ((CTRL_PRESSED == true) && (SHIFT_PRESSED == true) && (IsKeyDown(KEY_UP) == true) && (IsKeyUp(KEY_UP) == false))
    increaseInputTextValue(currentInputText, input, 1.0);

  // DECREASE VALUE
  if ((SHIFT_NOT_PRESSED == true) && (IsKeyDown(KEY_DOWN) == true) && (IsKeyUp(KEY_DOWN) == false))
    decreaseInputTextValue(currentInputText, input, 0.01);
  if ((SHIFT_PRESSED == true) && (IsKeyDown(KEY_DOWN) == true) && (IsKeyUp(KEY_DOWN) == false))
    decreaseInputTextValue(currentInputText, input, 0.1);
  if ((CTRL_PRESSED == true) && (SHIFT_PRESSED == true) && (IsKeyDown(KEY_DOWN) == true) && (IsKeyUp(KEY_DOWN) == false))
    decreaseInputTextValue(currentInputText, input, 1.0);
}


void HandleIncreaseDecreaseButton(int type, SubmitButton *btn, InputTextWithButtons *transform) {
  if (CheckCollisionPointRec(GetMousePosition(), btn->area)) {
    btn->mouseOn = true;
  } else {
    btn->mouseOn = false;
  }
  if (btn->mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (type == INCREASE_VALUE) {
      increaseInputTextValue(transform->input.type, &transform->input, 0.5);
    }
    if (type == DECREASE_VALUE) {
      decreaseInputTextValue(transform->input.type, &transform->input, 0.5);
    }
  }
}

void RemoveLastCharFromInputText(int currentInputText, InputText *input) {
  if (currentInputText == input->type) {
    if (strlen(input->text) <= 1) {
      if (input->category != DATE_YEAR_INPUT &&
          input->category != DATE_MONTH_INPUT &&
          input->category != DATE_DAY_INPUT) {
        input->text[0] = '0';
        input->text[1] = '\0';
      } else {
        input->text[0] = '\0';
      }
    } else {
      input->text[strlen(input->text) - 1] = '\0';
    }
    input->updated = true;
  }
}

void CleanInputText(int currentInputText, InputText *input) {
  if (currentInputText == input->type) {
    if (input->category != DATE_YEAR_INPUT &&
        input->category != DATE_MONTH_INPUT &&
        input->category != DATE_DAY_INPUT) {
      input->text[0] = '0';
      input->text[1] = '\0';
    } else {
      input->text[0] = '\0';
    }
    input->updated = true;
  }
}

void InitInputText(InputText *inputText, int type, int category, Rectangle area, char *label, char *text) {
  inputText->type = type;
  inputText->category = category;
  inputText->area = area;
  inputText->labelPosition = (Vector2){area.x - 10, area.y + 5};
  inputText->textPosition = (Vector2){area.x + 10, area.y + 5};
  inputText->fontSize = 20;
  inputText->mouseOn = false;
  inputText->updated = false;
  inputText->label[0] = '\0';
  strcat(inputText->label, label);
  inputText->text[0] = '\0';
  strcat(inputText->text, text);
}

void DrawInputText(InputText *inputText, int *currentInputText) {
  DrawText(
    inputText->label,
    inputText->labelPosition.x,
    inputText->labelPosition.y,
    14,
    ColorAlpha(DARKGRAY, 0.7)
  );
  DrawRectangle(
    inputText->area.x, 
    inputText->area.y, 
    inputText->area.width,
    inputText->area.height,
    (*currentInputText == inputText->type) ? WHITE : ColorAlpha(LIGHTGRAY, 0.1)
  );
  DrawRectangleLines(
    inputText->area.x, 
    inputText->area.y,
    inputText->area.width, 
    inputText->area.height,
    (*currentInputText == inputText->type) ? ColorAlpha(BLUE, 0.5) : LIGHTGRAY
  );
  DrawText(
    inputText->text,
    inputText->textPosition.x,
    inputText->textPosition.y,
    14,
    DARKGRAY
  );
}

void HandleInputText(InputText *inputText, int *currentInputText) {
  if (CheckCollisionPointRec(GetMousePosition(), inputText->area))
    inputText->mouseOn = true;
  else
    inputText->mouseOn = false;
  if (inputText->mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    *currentInputText = inputText->type;
}

void DrawIconButton(IconButton *btn) {
  DrawRectangle(btn->area.x,btn->area.y,btn->area.width,btn->area.height, btn->bgColor);
  DrawTexture(btn->icon, btn->area.x+8, btn->area.y+8, WHITE);
}

void InitIconButton(Texture2D icon, IconButton *btn, Rectangle area, Color bgColor) {
  btn->mouseOn = false;
  btn->area = area;
  btn->bgColor = bgColor;
  btn->icon = icon;
}

void DrawSubmitButton(SubmitButton *btn) {
  DrawRectangleRounded(btn->area, 1.0, 8, btn->bgColor);
  DrawText(btn->text, btn->textPosition.x, btn->textPosition.y, btn->fontSize, ColorAlpha(btn->textColor, 0.8));
}

void InitSubmitButton(SubmitButton *btn, Rectangle area, const char *label, Color bgColor, Color textColor, int fontSize) {
  btn->mouseOn = false;
  btn->fontSize = fontSize;
  btn->text[0] = '\0';
  btn->area = area;
  strcat(btn->text, label);

  int textSize = MeasureText(label, fontSize);
  float halfTextSize = textSize / 2;
  float halfAreaWidthSize = area.width / 2;
  btn->textPosition = (Vector2){
    (area.x + (halfAreaWidthSize - halfTextSize)),
    area.y + ((area.height / 2) - (btn->fontSize / 2))
  };
  btn->bgColor = bgColor;
  btn->textColor = textColor;
}

double GetDoubleValueFromInputText(InputText input) {
  char *ptr;
  return strtof(input.text, &ptr);
}