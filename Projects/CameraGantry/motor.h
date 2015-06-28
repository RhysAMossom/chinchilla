#include <Arduino.h>

class Motor {
  public:
    Motor(int channelABreak, int channelADir, int channelAMove,
          int channelBBreak, int channelBDir, int channelBMove);
    inline ~Motor() {};
    void move(uint16_t steps, uint16_t steps_per_mm, bool direction);
    bool isRunnig();

  private:
    bool running;
    int channelABreak;
    int channelADir;
    int channelAMove;
    int channelBBreak;
    int channelBDir;
    int channelBMove;
};
