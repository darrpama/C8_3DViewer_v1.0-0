#include "parser.h"

int is_line_ending(const char *p, unsigned int i, unsigned int end_i) {
  if (p[i] == '\0') return 1;
  if (p[i] == '\n') return 1; /* this includes \r\n */
  if (p[i] == '\r') {
    if (((i + 1) < end_i) && (p[i + 1] != '\n')) { /* detect only \r case */
      return 1;
    }
  }
  return 0;
}

void skip_space(const char **token) {
  while ((*token)[0] == ' ' || (*token)[0] == '\t') {
    (*token)++;
  }
}

void skip_space_and_cr(const char **token) {
  while ((*token)[0] == ' ' || (*token)[0] == '\t' || (*token)[0] == '\r') {
    (*token)++;
  }
}

int until_space(const char *token) {
  const char *p = token;
  while (p[0] != '\0' && p[0] != ' ' && p[0] != '\t' && p[0] != '\r') {
    p++;
  }
  return (int)(p - token);
}

int tryParseDouble(const char *s, const char *s_end, double *result) {
  double mantissa = 0.0;
  int exponent = 0;

  char sign = '+';
  char exp_sign = '+';
  char const *curr = s;

  int read = 0;
  int end_not_reached = 0;

  if (s >= s_end) {
    return 0;
  }

  if (*curr == '+' || *curr == '-') {
    sign = *curr;
    curr++;
  } else if (IS_DIGIT(*curr)) {
  } else {
    return 0;
  }

  end_not_reached = (curr != s_end);
  while (end_not_reached && IS_DIGIT(*curr)) {
    mantissa *= 10;
    mantissa += (int)(*curr - 0x30);
    curr++;
    read++;
    end_not_reached = (curr != s_end);
  }

  if (read == 0) {
    return 0;
  }

  if (!end_not_reached) {
    {
      double a = 1.0;
      double b = 1.0;
      int i;
      for (i = 0; i < exponent; i++) {
        a = a * 5.0;
      }

      for (i = 0; i < exponent; i++) {
        b = b * 2.0;
      }

      if (exp_sign == '-') {
        a = 1.0 / a;
        b = 1.0 / b;
      }

      *result = (sign == '+' ? 1 : -1) * (mantissa * a * b);
    }
    return 1;
  }

  if (*curr == '.') {
    curr++;
    read = 1;
    end_not_reached = (curr != s_end);
    while (end_not_reached && IS_DIGIT(*curr)) {
      double frac_value = 1.0;
      int f;
      for (f = 0; f < read; f++) {
        frac_value *= 0.1;
      }
      mantissa += (int)(*curr - 0x30) * frac_value;
      read++;
      curr++;
      end_not_reached = (curr != s_end);
    }
  } else {
    {
      double a = 1.0;
      double b = 1.0;
      int i;
      for (i = 0; i < exponent; i++) {
        a = a * 5.0;
      }

      for (i = 0; i < exponent; i++) {
        b = b * 2.0;
      }

      if (exp_sign == '-') {
        a = 1.0 / a;
        b = 1.0 / b;
      }

      *result = (sign == '+' ? 1 : -1) * (mantissa * a * b);
    }
    return 1;
  }

  if (!end_not_reached) {
    {
      double a = 1.0;
      double b = 1.0;
      int i;
      for (i = 0; i < exponent; i++) {
        a = a * 5.0;
      }

      for (i = 0; i < exponent; i++) {
        b = b * 2.0;
      }

      if (exp_sign == '-') {
        a = 1.0 / a;
        b = 1.0 / b;
      }

      *result = (sign == '+' ? 1 : -1) * (mantissa * a * b);
    }
    return 1;
  }

  {
    double a = 1.0;
    double b = 1.0;
    int i;
    for (i = 0; i < exponent; i++) {
      a = a * 5.0;
    }
    for (i = 0; i < exponent; i++) {
      b = b * 2.0;
    }
    if (exp_sign == '-') {
      a = 1.0 / a;
      b = 1.0 / b;
    }
    *result = (sign == '+' ? 1 : -1) * (mantissa * a * b);
  }
  return 1;
}

float parseFloat(const char **token) {
  const char *end;
  double val = 0.0;
  float f = 0.0f;
  skip_space(token);
  end = (*token) + until_space((*token));
  val = 0.0;
  tryParseDouble((*token), end, &val);
  f = (float)(val);
  (*token) = end;
  return f;
}

void parseFloat2(float *x, float *y, const char **token) {
  (*x) = parseFloat(token);
  (*y) = parseFloat(token);
}

void parseFloat3(float *x, float *y, float *z, const char **token) {
  (*x) = parseFloat(token);
  (*y) = parseFloat(token);
  (*z) = parseFloat(token);
}

int my_atoi(const char *c) {
  int value = 0;
  int sign = 1;
  if (*c == '+' || *c == '-') {
    if (*c == '-') sign = -1;
    c++;
  }
  while (((*c) >= '0') && ((*c) <= '9')) { /* isdigit(*c) */
    value *= 10;
    value += (int)(*c - '0');
    c++;
  }
  return value * sign;
}

int fixIndex(int idx, unsigned int n) {
  if (idx > 0) return idx - 1;
  if (idx == 0) return 0;
  return (int)n + idx; /* negative value = relative */
}
