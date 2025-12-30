#include "ComputerCard.h"
#include <cmath>
#include "oscillator.h"
#include "lookup_tables.h"

class WT : public ComputerCard
{
  uint32_t phase;
  uint32_t ph_rot;

  YinYang yinyang;

public:
  WT()
  {
    phase = 0;
  }

  virtual void ProcessSample()
  {
    // oscillator phase increment
    int32_t knobMain = KnobVal(Main);
    int32_t FM = AudioIn1();
    int32_t phaseInc = (knobMain * knobMain << 3) + (FM * FM << 3);

    phase += phaseInc < 0 ? 0 : phaseInc;

    // prepare output
    int32_t out[2];

    int32_t mod1 = KnobVal(X) + CVIn1();
    int32_t mod2 = KnobVal(Y) + CVIn2();

    yinyang.compute(phase, mod1, mod2, out);

    AudioOut1(out[0]);
    AudioOut2(out[1]);
  }

protected:

};

int main()
{
  set_sys_clock_khz(192000, true);
  WT wt;
  wt.Run();
}
