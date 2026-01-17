import math

FS = 48000
TWO_POW_32 = 2**32
F_MIN = 10.0
OCTAVES = 6.0
STEPS = 4096

print("const uint32_t frequency_lut[4096] = {")
for i in range(STEPS):
    # Logarithmic frequency calculation
    freq = F_MIN * (2.0 ** (i * OCTAVES / (STEPS - 1)))
    # Convert to 32-bit phase increment
    inc = int((freq * TWO_POW_32) / FS)
    print(f"{inc},", end=" " if i % 8 != 7 else "\n")
print("};")

