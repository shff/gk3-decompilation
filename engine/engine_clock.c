#include <stdint.h>

typedef uint32_t (__thiscall *ReadClockMethod)(uint32_t *engine);
typedef uint32_t (__thiscall *GetGameTimeMethod)(uint32_t *engine);
typedef int (__thiscall *ClockPauseMethod)(uint32_t *engine);

enum {
  ENGINE_CLOCK_PAUSE_DEPTH_SLOT = 26,
  ENGINE_FATAL_ERROR_SLOT = 22,
  ENGINE_CLOCK_EPOCH_SLOT = 52,
  ENGINE_PREVIOUS_FRAME_TIME_SLOT = 264,
  ENGINE_CLOCK_OFFSET_SLOT = 265,
  ENGINE_FROZEN_TIME_SLOT = 266,
  ENGINE_TIME_SCALE_BASE_SLOT = 290,
  READ_CLOCK_METHOD_SLOT = 24 / 4,
  GET_GAME_TIME_METHOD_SLOT = 28 / 4,
  PAUSE_CLOCK_METHOD_SLOT = 48 / 4,
  RESUME_CLOCK_METHOD_SLOT = 132 / 4,
  ENGINE_TIME_SCALE_OFFSET = 1164
};

uint32_t __thiscall get_unscaled_game_time(uint32_t *engine)
{
  if ((int32_t)engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT] > 0)
    return engine[ENGINE_FROZEN_TIME_SLOT];

  uint32_t *methods = *(uint32_t **)engine;
  uint32_t clock = ((ReadClockMethod)(uintptr_t)
      methods[READ_CLOCK_METHOD_SLOT])(engine);
  return clock - engine[ENGINE_CLOCK_OFFSET_SLOT];
}

uint32_t __thiscall get_game_time(uint32_t *engine)
{
  uint32_t now = get_unscaled_game_time(engine);
  double scale = *(double *)((uint8_t *)engine + ENGINE_TIME_SCALE_OFFSET);
  if ((int32_t)engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT] <= 0 && scale != 1.0) {
    uint32_t base = engine[ENGINE_TIME_SCALE_BASE_SLOT];
    return base + (uint32_t)(int64_t)((double)(now - base) * scale);
  }
  return now;
}

double __thiscall get_game_time_scale(uint32_t *engine)
{
  return *(double *)((uint8_t *)engine + ENGINE_TIME_SCALE_OFFSET);
}

uint32_t __thiscall set_previous_frame_time(uint32_t *engine, uint32_t time)
{
  engine[ENGINE_PREVIOUS_FRAME_TIME_SLOT] = time;
  return time;
}

uint32_t __thiscall shift_game_time(uint32_t *engine, int32_t delta)
{
  uint32_t offset = engine[ENGINE_CLOCK_OFFSET_SLOT];
  uint32_t reference = (int32_t)engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT] <= 0
      ? offset : engine[ENGINE_FROZEN_TIME_SLOT];

  if (reference - (uint32_t)delta <= offset) {
    engine[ENGINE_CLOCK_OFFSET_SLOT] = offset - (uint32_t)delta;
    engine[ENGINE_FROZEN_TIME_SLOT] -= (uint32_t)delta;
    return engine[ENGINE_FROZEN_TIME_SLOT];
  }

  engine[ENGINE_CLOCK_EPOCH_SLOT] -= (uint32_t)delta;
  return engine[ENGINE_CLOCK_EPOCH_SLOT];
}

uint32_t __thiscall set_game_time_scale(uint32_t *engine, double scale)
{
  uint32_t *methods = *(uint32_t **)engine;
  uint32_t base = ((GetGameTimeMethod)(uintptr_t)
      methods[GET_GAME_TIME_METHOD_SLOT])(engine);
  engine[ENGINE_TIME_SCALE_BASE_SLOT] = base;
  uint32_t unscaled = get_unscaled_game_time(engine);
  uint32_t result = shift_game_time(engine, (int32_t)(base - unscaled));
  *(double *)((uint8_t *)engine + ENGINE_TIME_SCALE_OFFSET) = scale;
  return result;
}

int __thiscall pause_engine_clock(uint32_t *engine)
{
  if (!engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT])
    engine[ENGINE_FROZEN_TIME_SLOT] = get_unscaled_game_time(engine);

  int depth = (int)++engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT];
  if (depth == 1 && !engine[ENGINE_FATAL_ERROR_SLOT]) {
    uint32_t *methods = *(uint32_t **)engine;
    return ((ClockPauseMethod)(uintptr_t)
        methods[PAUSE_CLOCK_METHOD_SLOT])(engine);
  }
  return depth == 1 ? (int)engine[ENGINE_FATAL_ERROR_SLOT] : depth;
}

int __thiscall resume_engine_clock(uint32_t *engine)
{
  int depth = (int)--engine[ENGINE_CLOCK_PAUSE_DEPTH_SLOT];
  if (depth == 0) {
    engine[ENGINE_CLOCK_OFFSET_SLOT] =
        get_unscaled_game_time(engine) - engine[ENGINE_FROZEN_TIME_SLOT]
        + engine[ENGINE_CLOCK_OFFSET_SLOT];
    if (!engine[ENGINE_FATAL_ERROR_SLOT]) {
      uint32_t *methods = *(uint32_t **)engine;
      return ((ClockPauseMethod)(uintptr_t)
          methods[RESUME_CLOCK_METHOD_SLOT])(engine);
    }
    return (int)engine[ENGINE_FATAL_ERROR_SLOT];
  }
  return depth;
}
