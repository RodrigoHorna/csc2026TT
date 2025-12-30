# TT-E1: Debugging with Sanitizers (ASan/UBSan)

**Timetable slot:** Tools and Techniques **E1** (60 minutes)

This exercise is a hands-on workflow for finding and fixing memory bugs using sanitizers, then preventing regressions with unit tests.

## Learning objectives

By the end you can:

- Build with AddressSanitizer and UndefinedBehaviorSanitizer
- Read a sanitizer report and locate the root cause in code
- Fix the bug and validate the fix with unit tests (`ctest`)
- Make a minimal, reviewable commit that would pass CI

## Timebox plan (60 min)

- 0–10: configure + build sanitizer build
- 10–25: reproduce the sanitizer finding and identify the root cause
- 25–45: implement the fix
- 45–55: add or extend a unit test to lock the fix
- 55–60: final run (`ctest` + executable) and commit message

## Success criteria

- `./analyze` runs with **no sanitizer findings**
- `ctest` passes in the sanitizer build directory
- At least one test covers the bug you fixed

## Where to work

Start in:

- `starter/` (contains the buggy implementation)

## Commands

```bash
cd exercises/TT-E1-debugging-sanitizers/starter

cmake -B build-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build-asan -j"$(nproc)"
ctest --test-dir build-asan --output-on-failure

./build-asan/analyze
```

## Stretch (only if you finish early)
* Add one more test covering an edge case
* Try a TSan build if the code uses concurrency
