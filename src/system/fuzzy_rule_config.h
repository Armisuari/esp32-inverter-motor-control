#pragma once

// Helper to declare fuzzy ranges.
#define FUZZY_RANGE(NAME, A, B, C, D)                 \
    struct NAME                                       \
    {                                                 \
        static constexpr int a = (A);                 \
        static constexpr int b = (B);                 \
        static constexpr int c = (C);                 \
        static constexpr int d = (D);                 \
        static_assert(a <= b && b <= c && c <= d,     \
                      "Invalid ordering for " #NAME); \
    }

// Encoder fuzzy sets
FUZZY_RANGE(encoder_negatif_besar, -1350, -1350, -1350, -900);
FUZZY_RANGE(encoder_negatif_kecil, -1100, -600, -600, -200);
FUZZY_RANGE(encoder_zero, -250, 0, 0, 250);
FUZZY_RANGE(encoder_positif_kecil, 200, 600, 600, 1100);
FUZZY_RANGE(encoder_positif_besar, 900, 1350, 1350, 1350);

// Delta error fuzzy sets
FUZZY_RANGE(deltaerror_turun_cepat, -500, -500, -500, -300);
FUZZY_RANGE(deltaerror_turun_lambat, -420, -250, -250, -80);
FUZZY_RANGE(deltaerror_stabil, -100, 0, 0, 100);
FUZZY_RANGE(deltaerror_naik_lambat, 80, 250, 250, 420);
FUZZY_RANGE(deltaerror_naik_cepat, 300, 500, 500, 500);

// Frequency (output) fuzzy sets
FUZZY_RANGE(frequency_kurangi_banyak, 0, 0, 0, 15);
FUZZY_RANGE(frequency_kurangi_sedikit, 0, 15, 15, 30);
FUZZY_RANGE(frequency_tidak_berubah, 15, 30, 30, 45);
FUZZY_RANGE(frequency_tambah_sedikit, 30, 45, 45, 60);
FUZZY_RANGE(frequency_tambah_banyak, 45, 60, 60, 60);

// Undefine helper to avoid leaking macro into other translation units.
#undef FUZZY_RANGE