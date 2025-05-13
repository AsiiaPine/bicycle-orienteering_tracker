#pragma once

int clamp(int x, int min, int max) {
if (x < min) x = min;
if (x > max) x = max;
return x;
}
